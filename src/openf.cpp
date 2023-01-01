#include "openf.h"
#include "ui_openf.h"
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QTextCodec>

OpenF::OpenF(bool Creat,QWidget *parent) :
    QDialog(parent),
    ui_o(new Ui::OpenF)
{
    ui_o->setupUi(this);
    Fcreat=Creat;
    papp=QApplication::applicationDirPath()+"/";
    if(Fcreat){
        ui_o->creatFr->setHidden(false);
        ui_o->clearCreat->setHidden(false);
        ui_o->fileCreat->setHidden(false);
       on_clearCreat_toggled(true);
       FEmpty=true;
    }else{
        ui_o->creatFr->setHidden(true);
        ui_o->clearCreat->setHidden(true);
        ui_o->fileCreat->setHidden(true);
        on_fileCreat_clicked(true);
        FEmpty=false;
    }

}

OpenF::~OpenF()
{
    delete ui_o;
}

void OpenF::on_clearCreat_toggled(bool checked)
{
    //выбрана пустая форма
    if(checked){
       ui_o->fileCreat->setChecked(false);
       ui_o->cp1251->setDisabled(true);
       ui_o->dos866->setDisabled(true);
       ui_o->docf->setDisabled(true);
       ui_o->dos866->setDisabled(true);
       ui_o->fb2f->setDisabled(true);
       ui_o->fileName->setDisabled(true);
       ui_o->htmlf->setDisabled(true);
       ui_o->koi8r->setDisabled(true);
       ui_o->odtf->setDisabled(true);
       ui_o->textf->setDisabled(true);
       ui_o->utf8->setDisabled(true);
       ui_o->zipf->setDisabled(true);
       ui_o->fileDial->setDisabled(true);
       FEmpty=true;
    }
}

void OpenF::on_fileCreat_clicked(bool checked)
{
    //Выбрана на основе файла
    if(checked){
       ui_o->clearCreat->setChecked(false);
       ui_o->cp1251->setEnabled(true);
       ui_o->dos866->setEnabled(true);
       ui_o->docf->setEnabled(true);
       ui_o->dos866->setEnabled(true);
       ui_o->fb2f->setEnabled(true);
       ui_o->fileName->setEnabled(true);
       ui_o->htmlf->setEnabled(true);
       ui_o->koi8r->setEnabled(true);
       ui_o->odtf->setEnabled(true);
       ui_o->textf->setEnabled(true);
       ui_o->utf8->setEnabled(true);
       ui_o->zipf->setEnabled(true);
       ui_o->fileDial->setEnabled(true);
       FEmpty=false;
    }

}

void OpenF::on_fileDial_clicked()
{
    //диалог по выбору файла
    TextFileName.clear();
    TextFileName = QFileDialog::getOpenFileName(this,
                  QString::fromUtf8("Открыть фаил"), QDir::currentPath());
    if(!TextFileName.isEmpty()){
        ui_o->fileName->setText(TextFileName);
        QStringList pfn=TextFileName.split(".");
        ui_o->textf->setChecked(true);
        ui_o->zipf->setChecked(false);
        ui_o->utf8->setChecked(true);
        foreach(QString s,pfn){
            s=s.trimmed();
            s=s.toLower();
            if((s=="html")|(s=="htm")){
                ui_o->htmlf->setChecked(true);
            }else if (s=="doc") {
                ui_o->docf->setChecked(true);
            }else if (s=="odt") {
                ui_o->odtf->setChecked(true);
            }else if (s=="fb2") {
                ui_o->fb2f->setChecked(true);
            }else if (s=="zip") {
                ui_o->zipf->setChecked(true);
            }
        }
    }
}

void OpenF::on_buttonBox_accepted()
{
    //
    if (Fcreat&FEmpty){
        emit creatFcl();
    }else{
        QDir tmd;
        QString PathW=tmd.homePath();
        PathW=PathW.trimmed()+"/.skomoroh";
        tmd.setPath(PathW);
        // Если нет- то он создается
        if(!(tmd.exists(PathW))){
                tmd.mkpath(PathW);
        };
        if(tmd.exists(PathW+"/tmp.sh")){
            tmd.remove(PathW+"/tmp.sh");
        }
        if((!ui_o->zipf->isChecked())&ui_o->textf->isChecked()&ui_o->utf8->isChecked()){
            if(Fcreat){
                emit creatFfn(TextFileName);
            }else{
                emit openFfn(TextFileName);
            }
        }else{
            QFile fcmd;
            fcmd.setFileName(PathW+"/tmp.sh");
            QTextStream fcmdst;
            fcmdst.setDevice(&fcmd);
            if(fcmd.open(QIODevice::WriteOnly | QIODevice::Text)){
                if(ui_o->zipf->isChecked()){
                    fcmdst<<"unzip -p \"$1\">\"/tmp/tmp.src\""<<endl;
                }else{
                    if(ui_o->textf->isChecked()&ui_o->utf8->isChecked()){
                        if(Fcreat){
                            emit creatFfn(TextFileName);
                        }else{
                            emit openFfn(TextFileName);
                        }
                    } else{
                        if(ui_o->htmlf->isChecked()){
                            fcmdst<<"cat \"$1\">\"/tmp/tmp.html\""<<endl;
                        }else{
                            fcmdst<<"cat \"$1\">\"/tmp/tmp.src\""<<endl;
                        }
                    }
                }
                QString scod;
                if(ui_o->htmlf->isChecked()){
                    scod="";
                    if(ui_o->cp1251->isChecked()){
                        scod="windows-1251";
                    }
                    if(ui_o->koi8r->isChecked()){
                        scod="csKOI8R";
                    }
                    if(ui_o->dos866->isChecked()){
                        scod="csIBM866";
                    }
                    fcmdst<<"lynx -assume_charset="+scod+" -dump \"/tmp/tmp.html\"> \""+PathW+"/tmp.txt\""<<endl;
                }
                if(ui_o->docf->isChecked()){
                    fcmdst<<papp+"antiword -t \"/tmp/tmp.src\"> \""+PathW+"/tmp.txt\""<<endl;
                }
                if(ui_o->odtf->isChecked()){
                    fcmdst<<"/bin/bash "+papp+"antiodt \"/tmp/tmp.src\"> \""+PathW+"/tmp.txt\""<<endl;
                }
                if(ui_o->fb2f->isChecked()){
                     fcmdst<<"xsltproc "+papp+"FB2_2_txt.xsl \"/tmp/tmp.src\" > \""+PathW+"/tmp.txt\""<<endl;
                }
                if(ui_o->textf->isChecked()){
                    scod="";
                    if(ui_o->cp1251->isChecked()){
                        scod="windows-1251";
                    }
                    if(ui_o->koi8r->isChecked()){
                        scod="KOI8-R";
                    }
                    if(ui_o->dos866->isChecked()){
                        scod="IBM 866";
                    }
                    fcmdst<<"cp \"/tmp/tmp.src\" \""+PathW+"/tmp.txt\""<<endl;
                }
                if(ui_o->htmlf->isChecked()){
                    fcmdst<<"rm -f \"/tmp/tmp.html\""<<endl;
                }else{
                    fcmdst<<"rm -f \"/tmp/tmp.src\""<<endl;
                }
                fcmd.close();
                QProcess opr;
                opr.start("/bin/bash "+PathW+"/tmp.sh \""+TextFileName+"\"");
                opr.waitForFinished();
                if(ui_o->textf->isChecked()){
                    QFile ftm(PathW+"/tmp.txt");
                    QByteArray encodedString;
                    QTextCodec *codec = QTextCodec::codecForName(scod.toLatin1());
                    QString string;
                    if(ftm.open(QIODevice::ReadOnly)){
                        encodedString=ftm.readAll();
                        string = codec->toUnicode(encodedString);
                        ftm.close();
                        ftm.remove();
                        ftm.open(QIODevice::WriteOnly|QIODevice::Text);
                        QTextStream ftmst(&ftm);
                        ftmst<<string;
                        ftm.close();
                    }
                }
                if(Fcreat){
                    emit creatFfn(PathW+"/tmp.txt");
                }else{
                    emit openFfn(PathW+"/tmp.txt");
                }
            }

        }
    }
}

void OpenF::on_buttonBox_rejected()
{
      this->close();
}
