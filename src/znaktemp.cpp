#include "znaktemp.h"
#include "ui_znaktemp.h"
#include <QtGlobal>
#include <QProcess>
#include <menestrel.h>

ZnakTemp::ZnakTemp(QWidget *parent) :
    QDialog(parent),
    ui_z(new Ui::ZnakTemp)
{
    ui_z->setupUi(this);
    // загрузка знаков и темпа
    ppp=parent;
    Menestrel *pp=(Menestrel *)ppp;
    papp=QApplication::applicationDirPath()+"/";
    QFile fznk(pp->PathW+"/setprog/znak.cfg");
    QTextStream fznkst(&fznk);
    QString tx;
    Temp="1.5";
    Pitch="0";
    PitchS="50";
    //Daudio="espeak";
    FZzvezd=true;
    FZpodch=true;
    FZravn=true;
    FZplus=true;
    FZnom=true;
    FZznk=true;
    FZskob=true;
    Daudio="RHVoice-test -p elena -i $1/$2.txt -o $1/$2.wav";
    Kode="UTF-8";
    PMin="0.00";
    PNrm="1.00";
    PMax="2.00";
    drv<<"RHVoice-test -p elena -i $1/$2.txt -o $1/$2.wav"<<"\""+papp+"ru_tts\" -s \""+papp+"lexicon\" -p $3 < $1/$2.txt | sox -t raw -s -b 8 -r 10000 -c 1 -v 0.8 - -t wav -c 2 $1/$2.wav";
    drv<<"espeak -vru+m1 -p $3 -f $1/$2.txt -w $1/$2.wav"<<"espeak -vru+f1 -p $3 -f $1/$2.txt -w $1/$2.wav"<<"espeak -ven+m1 -p $3 -f $1/$2.txt -w $1/$2.wav"<<"espeak -ven+f1 -p $3 -f $1/$2.txt -w $1/$2.wav";
    drv<<"espeak -vru+m2 -p $3 -f $1/$2.txt -w $1/$2.wav"<<"espeak -vru+f2 -p $3 -f $1/$2.txt -w $1/$2.wav"<<"espeak -ven+m2 -p $3 -f $1/$2.txt -w $1/$2.wav"<<"espeak -ven+f2 -p $3 -f $1/$2.txt -w $1/$2.wav";
    drv<<"#";
    kdr<<"UTF-8"<<"KOI8-R"<<"UTF-8"<<"UTF-8"<<"UTF-8"<<"UTF-8"<<"UTF-8"<<"UTF-8"<<"UTF-8"<<"UTF-8"<<"#";
    mnm<<"0.50"<<"0"<<"0"<<"0"<<"0"<<"0"<<"0"<<"0"<<"0"<<"0"<<"0";
    nrmn<<"1.00"<<"0.01"<<"50"<<"50"<<"50"<<"50"<<"50"<<"50"<<"50"<<"50"<<"0";
    mxm<<"2.00"<<"1.00"<<"100"<<"100"<<"100"<<"100"<<"100"<<"100"<<"100"<<"100"<<"0";

    bdl=false;
    if(fznk.open(QIODevice::ReadOnly | QIODevice::Text)){
        do{
            tx=fznkst.readLine();
            if(!tx.isNull()){
                QStringList txl=tx.split("=");
                if(((QString)(txl[0])).trimmed()=="Temp"){
                   Temp=((QString)(txl[1])).trimmed();
                }
                if(((QString)(txl[0])).trimmed()=="Pitch"){
                   Pitch=((QString)(txl[1])).trimmed();
                }
                if(((QString)(txl[0])).trimmed()=="PitchS"){
                   PitchS=((QString)(txl[1])).trimmed();
                }
                if(((QString)(txl[0])).trimmed()=="Daudio"){
                   Daudio=((QString)(txl[1])).trimmed();
                }
                if(((QString)(txl[0])).trimmed()=="Kode"){
                   Kode=((QString)(txl[1])).trimmed();
                }
                if(((QString)(txl[0])).trimmed()=="PMin"){
                   PMin=((QString)(txl[1])).trimmed();
                }
                if(((QString)(txl[0])).trimmed()=="PNrm"){
                   PNrm=((QString)(txl[1])).trimmed();
                }
                if(((QString)(txl[0])).trimmed()=="PMax"){
                   PMax=((QString)(txl[1])).trimmed();
                }
                if(((QString)(txl[0])).trimmed()=="FZzvezd"){
                    if(((QString)(txl[1])).trimmed()=="0"){
                       FZzvezd=false;
                    }else{
                       FZzvezd=true;
                    }
                }
                if(((QString)(txl[0])).trimmed()=="FZpodch"){
                    if(((QString)(txl[1])).trimmed()=="0"){
                       FZpodch=false;
                    }else{
                       FZpodch=true;
                    }
                }
                if(((QString)(txl[0])).trimmed()=="FZravn"){
                    if(((QString)(txl[1])).trimmed()=="0"){
                       FZravn=false;
                    }else{
                       FZravn=true;
                    }
                }
                if(((QString)(txl[0])).trimmed()==" FZplus"){
                    if(((QString)(txl[1])).trimmed()=="0"){
                        FZplus=false;
                    }else{
                        FZplus=true;
                    }
                }
                if(((QString)(txl[0])).trimmed()=="FZnom"){
                    if(((QString)(txl[1])).trimmed()=="0"){
                       FZnom=false;
                    }else{
                       FZnom=true;
                    }
                }
                if(((QString)(txl[0])).trimmed()=="FZznk"){
                    if(((QString)(txl[1])).trimmed()=="0"){
                       FZznk=false;
                    }else{
                       FZznk=true;
                    }
                }
                if(((QString)(txl[0])).trimmed()=="FZskob"){
                    if(((QString)(txl[1])).trimmed()=="0"){
                       FZskob=false;
                    }else{
                       FZskob=true;
                    }
                }
            }
        }while(!tx.isNull());
        fznk.close();
    }
    ui_z->zvezd->setChecked(FZzvezd);
    ui_z->ravno->setChecked(FZravn);
    ui_z->podch->setChecked(FZpodch);
    ui_z->plus->setChecked(FZplus);
    ui_z->nomer->setChecked(FZnom);
    ui_z->znaks->setChecked(FZznk);
    ui_z->skob->setChecked(FZskob);
    qreal t=1.0 ;
    t=qreal(Temp.toFloat());
    if(t<qreal(1.0)){
        t=(t-qreal(0.5))*qreal(20.0);
    }else{
        t=t*qreal(10);
    }
    int ti=qRound(t);
    ui_z->horizontalSlider->setSliderPosition(ti);
    ui_z->gener->setEnabled(true);
    ui_z->gener->setText(Daudio);
    ui_z->gener->setEnabled(false);
    ui_z->kode->setEnabled(true);
    ui_z->kode->setCurrentIndex(ui_z->kode->findText(Kode));
    ui_z->kode->setEnabled(false);
    ui_z->mn->setEnabled(true);
    ui_z->mn->setText(PMin);
    ui_z->mn->setEnabled(false);
    ui_z->nrm->setEnabled(true);
    ui_z->nrm->setText(PNrm);
    ui_z->nrm->setEnabled(false);
    ui_z->mx->setEnabled(true);
    ui_z->mx->setText(PMax);
    ui_z->mx->setEnabled(false);
//    ti=PitchS.toInt();
//    t=1.0 ;
//    t=qreal(PitchS.toFloat());
//    if(t<qreal(1.0)){
//        t=(t-qreal(0.5))*qreal(20.0);
//    }else{
//        t=t*qreal(10);
//    }
//    ti=qRound(t);
//    ui_z->pitchss->setSliderPosition(ti);
    setPitch2(PitchS);
    int tt;
    tt=Pitch.toInt();
    ui_z->pitchsl->setSliderPosition(tt);
    int ind=0;
    foreach (QString sda,drv){
        if(sda==Daudio) break;
        ind++;
    }
//    int ind=drv.indexOf(Daudio);
//    if(ind>=0){
    if(ind<(drv.size()-1)){
        ui_z->driv->setCurrentIndex(ind);
    }else{
        ui_z->gener->setEnabled(true);
        ui_z->gener->setText(Daudio);
        ui_z->kode->setEnabled(true);
        ui_z->mn->setEnabled(true);
        ui_z->nrm->setEnabled(true);
        ui_z->mx->setEnabled(true);
        ui_z->driv->setCurrentIndex(10);
        ui_z->gener->setReadOnly(false);
       // ui_z->kode->setReadOnly(false);
        ui_z->mn->setReadOnly(false);
        ui_z->nrm->setReadOnly(false);
        ui_z->mx->setReadOnly(false);
    }
}

ZnakTemp::~ZnakTemp()
{
    delete ui_z;
}

void ZnakTemp::on_zvezd_toggled(bool checked)
{
    //
    FZzvezd=checked;
}

void ZnakTemp::on_podch_toggled(bool checked)
{
    //
    FZpodch=checked;
}

void ZnakTemp::on_ravno_toggled(bool checked)
{
    //
     FZravn= checked;
}

void ZnakTemp::on_plus_toggled(bool checked)
{
    //
    FZplus= checked;
}

void ZnakTemp::on_skob_toggled(bool checked)
{
    //
    FZskob= checked;
}

void ZnakTemp::on_znaks_toggled(bool checked)
{
    //
    FZznk= checked;
}

void ZnakTemp::on_nomer_toggled(bool checked)
{
    //
    FZnom= checked;
}

void ZnakTemp::on_buttonBox_accepted()
{
    //
    Menestrel *pp=(Menestrel *)ppp;
    bdl=false;
    pp->Temp=Temp;
    pp->Pitch=Pitch;
    if(pp->PitchS!=PitchS){
        bdl=true;
    }
    pp->PitchS=PitchS;
    if(pp->Daudio!=Daudio){
        bdl=true;
    }
    pp->Daudio=Daudio;
    pp->Kode=Kode;
    pp->PMin=PMin;
    pp->PNrm=PNrm;
    pp->PMin=PMin;
    pp->FZnom=FZnom;
    pp->FZplus=FZplus;
    pp->FZpodch=FZpodch;
    pp->FZravn=FZravn;
    pp->FZskob=FZskob;
    pp->FZznk=FZznk;
    pp->FZzvezd=FZzvezd;
    pp->writeConf(bdl);
    this->close();
}

void ZnakTemp::on_buttonBox_rejected()
{
    //
    this->close();

}

void ZnakTemp::on_toolButton_clicked()
{
    //
    Menestrel *pp=(Menestrel *)ppp;
    QDir tdi;
    QByteArray buf;
    if(tdi.exists(pp->PathW+"/testtemp.txt")){
        tdi.remove(pp->PathW+"/testtemp.txt");
    }
    QFile fwr(QString::fromUtf8(":/ico/testtemp.txt"));
    QTextStream fwrst(&fwr);
    if(fwr.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString srt=fwrst.readAll();
        QFile fwd(pp->PathW+"/testtemp.txt");
        QTextStream fwdst(&fwd);
        fwd.open(QIODevice::WriteOnly);
        if(Kode=="UTF-8"){
            fwdst<<srt;
        }else{
            QTextCodec *codec = QTextCodec::codecForName(Kode.toLocal8Bit());
            buf=codec->fromUnicode(srt);
            fwd.write(buf);
            fwd.flush();
        }
        fwd.close();
        fwr.close();
    }

    QString pcm= "play -q "+pp->PathW+"/testtemp.wav tempo "+Temp+" pitch "+Pitch;
    QString text = "/bin/bash "+pp->PathW+"/setprog/fc "+pp->PathW+" testtemp"+" "+PitchS;
    QProcess play;
    play.start(text);
    play.waitForFinished();
    play.start(pcm);
    play.waitForFinished();
}

void ZnakTemp::on_horizontalSlider_valueChanged(int value)
{
    qreal t;
    t=qreal(value);
    if(value<10){
        t=(t/qreal(20.0))+qreal(0.5);
    }else{
        t=(t/qreal(10.0));
    }
    Temp=Temp.setNum(t,'f',2);
}

void ZnakTemp::on_pitchsl_valueChanged(int value)
{
    Pitch.setNum(value);

}

void ZnakTemp::on_driv_currentIndexChanged(int index)
{
    //теперь будет новый выбор

    Daudio=drv[index];
    if(Daudio!="#"){
        QString ss=Daudio;
        rzrd(ss);
        ui_z->gener->setEnabled(true);
        ui_z->gener->setText(Daudio);
        ui_z->gener->setEnabled(false);
        Kode=kdr[index];
        ui_z->kode->setEnabled(true);
        ui_z->kode->setCurrentIndex(ui_z->kode->findText(Kode));
        ui_z->kode->setEnabled(false);
        PMin=mnm[index];
        ui_z->mn->setEnabled(true);
        ui_z->mn->setText(PMin);
        ui_z->mn->setEnabled(false);
        PNrm=nrmn[index];
        ui_z->nrm->setEnabled(true);
        ui_z->nrm->setText(PNrm);
        ui_z->nrm->setEnabled(false);
        PMax=mxm[index];
        ui_z->mx->setEnabled(true);
        ui_z->mx->setText(PMax);
        ui_z->mx->setEnabled(false);
        //
    }else{
        ui_z->gener->setEnabled(true);
        ui_z->gener->clear();
        ui_z->kak->setEnabled(true);
        ui_z->kode->setEnabled(true);
        ui_z->mn->setEnabled(true);
        ui_z->nrm->setEnabled(true);
        ui_z->mx->setEnabled(true);
        ui_z->gener->setReadOnly(false);
        // ui_z->kode->setReadOnly(false);
        ui_z->mn->setReadOnly(false);
        ui_z->nrm->setReadOnly(false);
        ui_z->mx->setReadOnly(false);
        //
    }
    PitchS=PNrm;
    QString snrm=PNrm;
    setPitch2(snrm);
}

void ZnakTemp::on_pitchss_valueChanged(int value)
{
    PitchS=getPitch2();
//    rzrd();
}

void ZnakTemp::setPitch2(QString val)
{
    qreal t=qreal(val.toFloat());
    qreal tmn=qreal(ui_z->mn->text().trimmed().toFloat());
    qreal tmx=qreal(ui_z->mx->text().trimmed().toFloat());
    qreal tnr=qreal(ui_z->nrm->text().trimmed().toFloat());
    qreal tt;
    if(t<=tnr){
        tt=(t-tmn)/((tnr-tmn)/qreal(1000.0));
    }else{
        tt=(t-tnr)/((tmx-tnr)/qreal(1000.0))+qreal(1000.0);
    }
    int i=qRound(tt);
    ui_z->pitchss->setSliderPosition(i);
}

QString ZnakTemp::getPitch2()
{
    int ii;
    QString s=ui_z->nrm->text().trimmed();
    QStringList sl=s.split(".");
    if(sl.size()<2) {
        ii=0;
    }else{
        QString ss=sl[1];
        ii=ss.size();
    }

    int i= ui_z->pitchss->sliderPosition();
    qreal tmn=qreal(ui_z->mn->text().trimmed().toFloat());
    qreal tmx=qreal(ui_z->mx->text().trimmed().toFloat());
    qreal tnr=qreal(ui_z->nrm->text().trimmed().toFloat());
    qreal t1=(tnr-tmn)/qreal(1000.0);
    qreal t2=(tmx-tnr)/qreal(1000.0);
    qreal t=qreal(i);
    if(t<=qreal(1000.0)){
        t=t*t1+tmn;
    }else{
        t=(t-qreal(1000.0))*t2+tnr;
    }
    QString sr;
    sr=sr.setNum(t,'f',ii);
    sr=sr.trimmed();
    return sr;
}

void ZnakTemp::rzrd(QString com)
{
    QString s=com;
//    ui_z->gener->setText(s);
    Menestrel *pp=(Menestrel *)ppp;
    QFile fc(pp->PathW+"/setprog/fc");
    QTextStream fcst(&fc);
    if(fc.exists()){
        fc.remove();
    }
    if(fc.open(QIODevice::WriteOnly | QIODevice::Text)){
        fcst<<"#!/bin/bash"<<endl;
        fcst<<s<<endl;
    }
}

void ZnakTemp::on_gener_editingFinished()
{
    QString ss=ui_z->gener->text().trimmed();
    rzrd(ss);
    //
}

void ZnakTemp::on_kode_currentIndexChanged(int index)
{
    Kode=ui_z->kode->currentText();
    //
}

void ZnakTemp::on_kak_clicked()
{
    QString title = QString::fromUtf8("Как писать коммандную строку");
    QString msg = QString::fromUtf8("/opt/ru_tts/ru_tts -s /opt/ru_tts/lexicon -p $3 < $1/$2.txt | sox sox -t raw -s -b 8 -r 10000 -c 1 -v 0.8 - -t wav -c 2 $1/$2.wav\n")+
                  QString::fromUtf8("пример обращения к движку ru_tts, где $1 передается путь, $2- имя файла, но без расширения, тогда комбинация\n")+
                  QString::fromUtf8("$1/$2.txt указывает на входной текстовый файл для движка, а $1/$2.wav указывает на выходной звуковой файл.\n")+
                  QString::fromUtf8("$3 указывает высоту тона при генерации wav файла, величина которого определяется 3-м движком. Если это не нужно,\n")+
                  QString::fromUtf8(" можно $3 не использовать, тогда и положение 3-го движка никак не скажится на тон генерации wav");
    //вывод сообщения о не заполненной форме msg.trimmed()
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(msg);
    msgBox.exec();
    //
}
