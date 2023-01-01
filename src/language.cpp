#include "language.h"
#include "ui_language.h"
#include <QAbstractButton>
#include <QFile>
#include <QTextStream>
#include <menestrel.h>

Language::Language( QWidget *parent) :
    QDialog(parent),
    ui_l(new Ui::Language)
{
    ui_l->setupUi(this);
    ppp=parent;
    Menestrel *pp=(Menestrel *)ppp;
    QFile flng;
    QTextStream flngst;
    lg.clear();
    lgn.clear();
    flng.setFileName(pp->PathW+"/setprog/lang.cfg");
    flngst.setDevice(&flng);
    if(flng.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString tx;
        tx=tx=flngst.readLine();
        int i=tx.toInt();
        QStringList txl;
        do{
          tx=flngst.readLine();
          if(!tx.isNull()){
              txl=tx.split("=");
              ui_l->comboBox->addItem((QString)(txl.at(1)).trimmed(),QVariant((QString)(txl.at(0)).trimmed()));
              lg.append((QString)(txl.at(0)).trimmed());
              lgn.append((QString)(txl.at(1)).trimmed());
          }
        }while(!tx.isNull());
        ui_l->comboBox->setCurrentIndex(i);
        flng.close();
    }else {
        QString t1="msu_ru_nsh_clunits";
        QString t2="Русский Муж.";
        ui_l->comboBox->addItem(t2,QVariant(t1));
        lg.append(t1);
        lgn.append(t2);
    }

}

Language::~Language()
{
    delete ui_l;
}

void Language::on_buttonBox_accepted()
{
     QDir ddr;
     Menestrel *mm=(Menestrel *)ppp;
     int i=ui_l->comboBox->currentIndex();
     QString si;
     si=si.setNum(i);
     si.trimmed();
     mm->Flang="(voice_"+(QString)(lg.at(i)).trimmed()+")";
     QFile flng;
     QTextStream flngst;
     flng.setFileName(mm->PathW+"/setprog/lang.cfg");
     flngst.setDevice(&flng);
     if(ddr.exists(mm->PathW+"/setprog/lang.cfg")){
         ddr.remove(mm->PathW+"/setprog/lang.cfg");
     }
     if(flng.open(QIODevice::WriteOnly | QIODevice::Text)){
         flngst<<si<<endl;
         for(int row=0;row<lg.size();row++){
             flngst<<(QString)(lg.at(row)).trimmed()<<"="<<(QString)(lgn.at(row)).trimmed()<<"\n";
         }
         flng.close();
     }
     emit elang();
     this->close();

}

void Language::on_buttonBox_rejected()
{
    this->close();
}
