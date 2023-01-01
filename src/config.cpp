#include "config.h"
#include "ui_config.h"
#include <QStandardItemModel>
#include <QSplitter>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <menestrel.h>

config::config(QWidget *parent) :
    QDialog(parent),
    ui_c(new Ui::config)
{
    ui_c->setupUi(this);
    model = new QStandardItemModel(0, 2, this);
    selectionModel = new QItemSelectionModel(model);
    model->setHeaderData(0, Qt::Horizontal, QVariant(QString::fromUtf8("              Оригинал            ")));
    model->setHeaderData(1, Qt::Horizontal, QVariant(QString::fromUtf8("              Ударение            ")));
    ui_c->slovar->setModel(model);
    ui_c->slovar->setColumnWidth(0,242);
    ui_c->slovar->setColumnWidth(1,280);
    ui_c->slovar->setSelectionModel(selectionModel);
    pp=parent;
    Menestrel *ppp=(Menestrel *)pp;
    if(ppp->diction.size()>0){
        int row=0;
        foreach(dict d,ppp->diction){
            model->insertRows(row, 1, QModelIndex());
            model->setData(model->index(row, 0, QModelIndex()),
                                                d.sr);
            model->setData(model->index(row, 1, QModelIndex()),
                                                d.tr);
            row++;
        }
    }
}

config::~config()
{
    delete ui_c;
}

void config::on_insdic_clicked()
{
    if((!ui_c->orig->text().trimmed().isEmpty())&(!ui_c->udar->text().trimmed().isEmpty())){
        int row=model->rowCount();
        model->insertRows(row,1);
        model->setData(model->index(row,0),QVariant(ui_c->orig->text().trimmed()));
        model->setData(model->index(row,1),QVariant(ui_c->udar->text().trimmed()));
        ui_c->udar->clear();
        ui_c->orig->clear();
    }
    //
}

void config::on_buttonBox_accepted()
{
    if(model->rowCount()>0){
       Menestrel *ppp=(Menestrel *)pp;
       ppp->diction.clear();
       dict dd;
       for(int row=0;row<model->rowCount();row++){
           dd.sr=model->data(model->index(row,0)).toString().trimmed();
           dd.tr=model->data(model->index(row,1)).toString().trimmed();
           ppp->diction.append(dd);
       }
       QFile fdict;
       QTextStream fdictst;
       fdict.setFileName(ppp->PathW+"/setprog/diction.spr");
       fdictst.setDevice(&fdict);
       QDir ddr;
       if(ddr.exists(ppp->PathW+"/setprog/diction.spr")){
           ddr.remove(ppp->PathW+"/setprog/diction.spr");
       }
       if(fdict.open(QIODevice::WriteOnly | QIODevice::Text)){
           foreach(dict dd,ppp->diction){
               fdictst<<dd.sr<<"="<<dd.tr<<"\n";
           }
           fdict.close();
       }
    }
    this->close();
    //
}

void config::on_buttonBox_rejected()
{
    this->close();
    //
}

void config::on_deldic_clicked()
{
    //удалить из словаря
    //int row=selectionModel->currentIndex().row();
    int row=ui_c->slovar->currentIndex().row();
    model->removeRow(row,QModelIndex());
}
