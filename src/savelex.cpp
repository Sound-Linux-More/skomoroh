#include "savelex.h"
#include "ui_savelex.h"
#include <QFileDialog>
#include "menestrel.h"

SaveLex::SaveLex(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveLex)
{
    ui->setupUi(this);
    connect (&pw, SIGNAL(finished(int)),this, SLOT(on_lame(int)));
    pp=parent;
    FnumberLexem=1;
    ui->pb->setHidden(true);
    ui->pbl->setHidden(true);
}

SaveLex::~SaveLex()
{
    delete ui;
}

void SaveLex::on_toolButton_clicked()
{
    //
    if (Ffilename == "") {
        //Ffilename = QFileDialog::getExistingDirectory(0, tr("Открыть для сохранения лексемы"),
        //                                                   "/home",
        //                                                   QFileDialog::ShowDirsOnly
        //                                                   | QFileDialog::DontResolveSymlinks);


       Ffilename = QFileDialog::
                   getSaveFileName(0, QString::fromUtf8("сохранить лексему в каталог с именем:"),
                                               QDir::currentPath(),
                                               ("lexema (*.m3u)"));
    }
    //если имя файла указанно к нему прибавляется индекс
    else {
        //надо отрезть .wav а потом прибавить
        if (FnumberLexem != 1) {
        Ffilename.remove(Ffilename.length()-(5+QString().setNum(FnumberLexem-1).length()),
                         QString().setNum(FnumberLexem-1).length()+1);
        }
        Ffilename.insert(Ffilename.length()-4, "_"+QString().setNum(FnumberLexem).toUtf8());
        FnumberLexem += 1;
        //qDebug(Ffilename.toUtf8());
    }
    ui->fname->setText(Ffilename);
}

void SaveLex::on_lame(int cp)
{
   QString s;
   Menestrel *ppp=(Menestrel *)pp;
   s=s.setNum(cur);
   ui->pb->setValue(cur);
   if(cur<mx){
      if(ui->wav->isChecked()){
          pw.start("sox  -t raw -s -b 8 -r 11000 -c 1 -v 1  "+Path+"/"+s+".raw "+ncat+s+".wav  tempo "+ppp->Temp+" pitch "+ppp->Pitch);
          cur++;
      }else{
          QProcess ptm;
          ptm.start("sox  -t raw -s -b 8 -r 11000 -c 1 -v 1  "+Path+"/"+s+".raw /tmp/t.wav  tempo "+ppp->Temp+" pitch "+ppp->Pitch);
          ptm.waitForFinished();
          pw.start("lame /tmp/t.wav "+ncat+s+".mp3");
          cur++;
      }
   }else {
       emit rest();
       this->close();
   }
}

void SaveLex::on_ok_clicked()
{
    QDir td;
    Path=td.homePath()+"/.skomoroh";
    ncat=Ffilename;
    int ii;
    ii=ncat.size()-1;
    QChar *nd=ncat.data();

    while(ii>0){
        char c=(nd[ii]).toLatin1();
        if(c==char('/')){
            break;
        }
        ii--;
    }
    if(ii==0){
        ncat=Path;
    }
    ncat=ncat.left(ii+1);
    QFile pl(Ffilename);
    Menestrel *ppp=(Menestrel *)pp;
    mx=ppp->stn->size();
    QTextStream plst(&pl);
    QString si;
    if(pl.open(QIODevice::WriteOnly | QIODevice::Text)){
        for(int i=0;i<mx;i++){
               si=si.setNum(i);
               plst<<ncat+si;
               if(ui->wav->isChecked()){
                      plst<<".wav"<<endl;
                }else {
                      plst<<".mp3"<<endl;
                }
        }
        cur=0;
        ui->pb->setHidden(false);
        ui->pbl->setHidden(false);
        ui->pb->setMaximum(mx);
        ui->pb->setValue(cur);
        on_lame(0);
    }else {
        emit rest();
        this->close();
    }

}

void SaveLex::on_cancel_clicked()
{
    emit rest();
    this->close();
}
