#include "markf.h"
#include "ui_markf.h"
#include <menestrel.h>

MarkF::MarkF( bool go, int m,QString ct, QWidget *parent) :
    QDialog(parent),
    ui_m(new Ui::MarkF)
{
    ui_m->setupUi(this);
    ppp=parent;
    Menestrel *pp=(Menestrel *)ppp;
    if(go){
        ui_m->EndEdit->setHidden(true);
        ui_m->GoMark->setHidden(false);
        ui_m->exitMark->setHidden(false);
        //fff=fGp;
    }else{
        ui_m->EndEdit->setHidden(false);
        ui_m->GoMark->setHidden(true);
        ui_m->exitMark->setHidden(true);
        QString sss=sct.mid(pp->stn->at(m).bn,pp->stn->at(m).be-pp->stn->at(m).bn);
        ui_m->curMark->setPlainText(sss);
    }
    sct=ct;
    model=new QStringListModel();
    ui_m->listMark->setModel(model);
    selectionModel=new QItemSelectionModel(model);
    QStringList tsl;
    li.clear();
    tsl.clear();
    foreach(int i,pp->Mark){
            int fd;
            if((fd=pp->stn->at(i).be-pp->stn->at(i).bn)>45){
                fd=45;
            }

            QString tm= sct.mid(pp->stn->at(i).bn,fd);
            tsl.append(tm);
            li.append(i);

    }
    if(!go){
        int fd;
        if((fd=pp->stn->at(m).be-pp->stn->at(m).bn)>45){
            fd=45;
        }
        int f=m;
        fd=pp->stn->at(f).be-pp->stn->at(f).bn;
        ui_m->curMark->setPlainText(sct.mid(pp->stn->at(f).bn,fd));

        QString tm= sct.mid(pp->stn->at(m).bn,fd);

        tsl.append(tm);
        li.append(m);
    }else{
        if(!li.isEmpty()){
            int f=li.at(li.size()-1);
            int fd=pp->stn->at(f).be-pp->stn->at(f).bn;
            ui_m->curMark->setPlainText(sct.mid(pp->stn->at(f).bn,fd));
        }else{
            ui_m->curMark->clear();
        }
    }
    model->setStringList(tsl);

}

MarkF::~MarkF()
{
    delete ui_m;
}

void MarkF::on_delMark_clicked()
{
    //
    int ii=selectionModel->currentIndex().row();
    model->removeRow(ii);
    li.removeAt(ii);
}

void MarkF::on_GoMark_clicked()
{
    //
    int ii=ui_m->listMark->currentIndex().row();
    int f;
    if(ii>=0){
        f=li.at(ii);
    }else{
        if(!li.isEmpty()){
            f=li.at(li.size()-1);
        }else{
            f=-1;
        }
    }
    emit gomark(f);
    this->close();
}

void MarkF::on_exitMark_clicked()
{
    //
    int f=-1;
    emit gomark(f);
    this->close();
}

void MarkF::on_EndEdit_accepted()
{
    //
    Menestrel *pp=(Menestrel *)ppp;
    pp->Mark.clear();
    foreach(int j,li){
        pp->Mark.append(j);
    }
    pp->writeMark();
    this->close();
}

void MarkF::on_EndEdit_rejected()
{
    //
    this->close();
}

void MarkF::on_listMark_activated(QModelIndex index)
{
    Menestrel *pp=(Menestrel *)ppp;
    int ii=index.row();
    int f=li.at(ii);
    int fd=pp->stn->at(f).be-pp->stn->at(f).bn;
    ui_m->curMark->setPlainText(sct.mid(pp->stn->at(f).bn,fd));

}
