#include "menestrel.h"
#include "ui_menestrel.h"
//библиотека для запуска процесса
//Вывод сообщений приложения
#include <QMessageBox>
#include <QInputDialog>
//Патч Фестивал
#include "QFileDialog"
#include "QDesktopServices"
#include "QUrl"
#include "QTimer"

//#include <festival.h>

//формируем новое окно с установками программы по умолчанию
Menestrel::Menestrel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menestrel)
{
    ui->setupUi(this);
    QCoreApplication::setOrganizationName("AlexPrivate");
    QCoreApplication::setApplicationName("Menestrel");
    //глобальная таблица звуковых файлов абзацев
    stn=new QVector<blok>;
    //промежуточный вектор генерации
    ECPl=0;
    // счетчик генерированных WAV-файлов
    GCi=0;
    // счетчик произносимых WAV-файлов
    GPi=0;
    // счетчик проверяемых WAV-файлов
    GTi=0;
    // текущая позиция в окне
    Gpos=0;
    Faltlang = false;
    papp=QApplication::applicationDirPath()+"/";
    //Объявление переменной языка. Выбор русского языка по умолчанию
    //QString Flang  = "(language_russian)";
    Flang  = "(voice_msu_ru_nsh_clunits)";

    //формирование путя к программе в зависимости от ОС
    Fp = "";
    //числовой суфикс к сохраняемому имни файла если фаил с таким именем существует
    //FnumberLexem = 1;

    //Первый проход
    Futt1 = true;
    // Разрешить читать
    FPlay=true;

    Ffilename="";
    TextFileName="";
    // Темп воспроизведения- 1-нормальный, 1.1 ... 3- ускоренный, 0.9 ... 0.1 -замедленный
    Temp="1.0";
    TempS="1.0";
    Pitch="0";
    PitchS="1.00";
    Kode="UTF-8";
    PMin="0.50";
    PNrm="1.00";
    PMax="2.00";
    Daudio="RHVoice-test -p elena -i $1/$2.txt -o $1/$2.wav";
    FZzvezd=true; //звездочка
    FZpodch=true; //подчеркивание
    FZravn=true; //равно
    FZplus=true;  //плюс
    FZnom=true;   //номер доллар процент
    FZznk=true;   //озвучить !?
    FZskob=true;  //скобки

    //Файлы и потоки
    // Читаемый и сохраненный текст и его поток

    ftextst.setDevice(&ftext);
    // Файл и поток разбора текста
    fblokst.setDevice(&fblok);
    // Файл и поток текущей генерации звука
    fcurwst.setDevice(&fcurw);
    // Файл и поток текущего произнесенного абзаца
    fplyst.setDevice(&fply);
    // Файл и поток текущего словаря ударений
    fdictst.setDevice(&fdict);
    fznkst.setDevice(&fznk);
    fG=-1;

        Fp = "";
        //формируем строку запуска Festival
        //QString Zapusk = Fp.trimmed()+"festival ";

//_____________________________________________________________________________
    //      готовим текстовой фаил

    //Проверим, есть ли рабочий каталог программы в домашнем каталоге
    PathW=tmd.homePath();
    PathW=PathW.trimmed()+"/.skomoroh";
    tmd.setPath(PathW);
    // Если нет- то он создается
    if(!(tmd.exists(PathW))){
            tmd.mkpath(PathW);
    };
    if(!(tmd.exists(PathW+"/setprog"))){
        tmd.mkpath(PathW+"/setprog");
    }
    if(!(tmd.exists(PathW+"/setprog/fc"))){
        QByteArray buf;
        QFile fwr(QString::fromUtf8(":/scripts/fc"));
        if(fwr.open(QIODevice::ReadOnly)){
            buf=fwr.readAll();
            QFile fwd(PathW+"/setprog/fc");
            fwd.open(QIODevice::WriteOnly);
            fwd.write(buf);
            fwd.flush();
            fwd.close();
            fwr.close();
        }
    }
    if(!(tmd.exists(PathW+"/setprog/fp"))){
        QByteArray buf;
        QFile fwr(QString::fromUtf8(":/scripts/fp"));
        if(fwr.open(QIODevice::ReadOnly)){
            buf=fwr.readAll();
            QFile fwd(PathW+"/setprog/fp");
            fwd.open(QIODevice::WriteOnly);
            fwd.write(buf);
            fwd.flush();
            fwd.close();
            fwr.close();
        }
    }

    connect (&Ozvuchit, SIGNAL(finished(int)),this, SLOT(LoopGen(int)));
    connect (&playw, SIGNAL(finished(int)),this, SLOT(LoopPlayF(int)));
    //нажатие кнопки по CTRL + Enter
    ui->ButtonMenestrel->setShortcut(Qt::CTRL + Qt::Key_Return);
    //hot key for Open and slot
    ui->Open_act->setShortcut(tr("Ctrl+O"));
    connect(ui->Open_act, SIGNAL(triggered()), this, SLOT(open_file()));
    connect(ui->openButton,SIGNAL(clicked()), this,SLOT(open_file()));
     ui->Save_act->setShortcut(tr("Ctrl+S"));
    connect(ui->Save_act, SIGNAL(triggered()), this, SLOT(save_file()));
    connect(ui->saveButton,SIGNAL(clicked()), this, SLOT(save_file()));
    ui->Creat_act->setShortcut(tr("Ctrl+N"));
    connect(ui->Creat_act, SIGNAL(triggered()), this, SLOT(creat_file()));
    connect(ui->CreatButton,SIGNAL(clicked()), this, SLOT(creat_file()));
    //ui->Save_fonem_act->setShortcut(tr("Ctrl+N"));
    connect(ui->Save_fonem_act, SIGNAL(triggered()), this, SLOT(on_pushButton_2_clicked()));

    //Поиск Menestrel::find_file()
    ui->Find_act->setShortcut(tr("Cntr+F"));
    connect(ui->Find_act, SIGNAL(triggered()), this, SLOT(find_file()));
    connect(ui->endCr,SIGNAL(triggered()), this, SLOT(on_endCrButton_clicked()));
    ui->about_act->setShortcut(tr("F1"));
    connect(ui->about_act, SIGNAL(triggered()), this, SLOT(about_file()));

    //connect(ui->lang, SIGNAL(triggered()), this, SLOT(langin()));

    connect(ui->Dict, SIGNAL(triggered()), this, SLOT(dictin()));

    ui->pbwav->setDisabled(true);


    // Проверяется-если конфигурационный каталог в рабочем, если нет, то создается
    ftext.setFileName(PathW+"/conf/src.txt");
    if(!(tmd.exists(PathW+"/conf"))){
            tmd.mkpath(PathW+"/conf");
    };

    //Подготовка текста
    QString tx=ui->RechText->toPlainText();
    tx=tx+"\n";
    ui->RechText->setPlainText(tx);
    // Если продолжение сеанса, то загрузка сохраненного файла
    if(ftext.open(QIODevice::ReadOnly | QIODevice::Text)){
        tx=ftextst.readAll();
        ui->RechText->setPlainText(tx);
        ftext.close();
    }
    TextWind=ui->RechText->toPlainText();
    // Если продолжение- загрузка таблицы разметки
    blok tb;
    stn->clear();
    PbMax=0;
    PbVal=0;
    fblok.setFileName(PathW+"/conf/trc.cfg");
    if(fblok.open(QIODevice::ReadOnly | QIODevice::Text)){
      do{
        tx=fblokst.readLine();
        if(!tx.isNull()){
            QStringList txl=tx.split("#");
            tb.bn=txl.at(0).toInt();
            tb.be=txl.at(1).toInt();
            tb.Sw=txl.at(2).trimmed();
            tb.filwav=txl.at(3).trimmed();
            *stn<<tb;
        }
      }while(!tx.isNull());
      PbMax=stn->size();
      fblok.close();
    }else{
       if(!ui->RechText->toPlainText().isEmpty()){
           //Формирование таблицы разметки
           int ib=0;
           int ie=0;
           blok tb;
           stn->clear();
           while(ie>=0){
       //        ie=tx.indexOf("\n",ib);
               ie=tx.indexOf(QRegExp(QString::fromUtf8("[.!?][^A-Za-zА-Яа-я.,+!?*№%$]{0,}[A-ZА-Я]")),ib);
               if(ie>0){
                   tb.bn=ib;
                   tb.be=ie;
                   //QString sx=tx.mid(ib,ie-ib+1);
                   //sx=reggo(sx);
                   tb.Sw="";
                   tb.filwav="";
                   *stn<<tb;
                   //ie++;
                   //tx.insert(ie,"~");
               }
               ib=ie+1;
           }
           ib=0;
           foreach(tb,*stn){
               ib++;
               tx.insert(tb.be+ib,"~");
           }

           tx=reggo(tx);
           QStringList tl=tx.split("~");
           ib=0;
           blok *twn=stn->data();
           foreach(QString ttx,tl){
               if(ib>=stn->size()){
                   break;
               }
               twn[ib].Sw=ttx.trimmed();
               ib++;
           }

           //Запись таблицы разметки в файл
           QString txx;
           QString ttxx;
           fblok.open(QIODevice::WriteOnly | QIODevice::Text);
           for(ib=0;ib<stn->size();ib++){
               fblokst<<ttxx.setNum(stn->at(ib).bn)<<"#"<<txx.setNum(stn->at(ib).be)<<"#"<<stn->at(ib).Sw<<"#"<<stn->at(ib).filwav<<"\n";
           }
           fblok.flush();
           fblok.close();
       }
           PbMax=stn->size();
    }
    // Если продолжение- загрузка вектора генерированных абзацев
    curwav tw;
    twv.clear();
    fcurw.setFileName(PathW+"/conf/trw.cfg");
    if(fcurw.open(QIODevice::ReadOnly | QIODevice::Text)){
        do{
          tx=fcurwst.readLine();
          if(!tx.isNull()){
              QStringList txl=tx.split("#");
              tw.n=txl.at(0).toInt();
              tw.filwav=txl.at(1).trimmed();
              twv<<tw;
          }
        }while(!tx.isNull());
        fcurw.close();
        fcurw.remove();
        // объединение таблицы разметки и вектора генерированных абзацев
        blok *twn=stn->data();
        foreach(tw,twv){
            twn[tw.n].filwav=tw.filwav;
        }
        twv.clear();
        if(fblok.isOpen()){
            fblok.close();
        }
        if(fblok.exists()){
            fblok.remove();
        }
        //Запись таблицы разметки в файл
        QString txx;
        QString ttxx;
        fblok.open(QIODevice::WriteOnly | QIODevice::Text);
        for(int ib=0;ib<stn->size();ib++){
            fblokst<<ttxx.setNum(stn->at(ib).bn)<<"#"<<txx.setNum(stn->at(ib).be)<<"#"<<stn->at(ib).Sw<<"#"<<stn->at(ib).filwav<<"\n";
        }
        fblok.close();

    }
    if(fcurw.isOpen()){
        fcurw.close();
    }
    if(fcurw.exists()){
        fcurw.remove();
    }

    fcurw.open(QIODevice::WriteOnly | QIODevice::Text);

    // загрузка последнего прочитанного абзаца
    GPi=0;
    fply.setFileName(PathW+"/conf/ply.cfg");
    if(fply.open(QIODevice::ReadOnly | QIODevice::Text)){
        do{
            tx=fplyst.readLine();
            if(!tx.isNull()){
                GPi=tx.toInt();
            }
        }while(!tx.isNull());
    }
    if(!stn->isEmpty()){
        SelAb();
        GCi=GPi;
        fply.remove();
        ui->RechText->setReadOnly(true);
        Futt1=false;
    }
    if(fply.isOpen()){
        fply.close();
    }
    if(fply.exists()){
        fply.remove();
    }
    fply.open(QIODevice::WriteOnly | QIODevice::Text);

    //Загруска словаря ударений
    dict tdi;
    diction.clear();
    fdict.setFileName(PathW+"/setprog/diction.spr");
    if(fdict.open(QIODevice::ReadOnly | QIODevice::Text)){
        do{
          tx=fdictst.readLine();
          if(!tx.isNull()){
              QStringList txl=tx.split("=");
              tdi.sr=txl.at(0).trimmed();
              tdi.tr=txl.at(1).trimmed();
              diction<<tdi;
          }
        }while(!tx.isNull());
        fdict.close();
    }


    //Очистка закладок

        Mark.clear();


    // загрузка знаков , темпа
    fznk.setFileName(PathW+"/setprog/znak.cfg");
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
                if(((QString)(txl[0])).trimmed()=="Daudio"){
                   Daudio=((QString)(txl[1])).trimmed();
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
    //Загрузка закладок
    QFile fmrk(PathW+"/conf/mark.cfg");
    QTextStream fmrkst(&fmrk);
    if(fmrk.open(QIODevice::ReadOnly|QIODevice::Text)){
        do{
            tx=fmrkst.readLine();
            if(!tx.isNull()){
               QStringList txl=tx.split("=");
               if(((QString)(txl[0])).trimmed()=="Mark"){
                   QStringList tml=((QString)(txl[1])).trimmed().split(";");
                   foreach(QString ttx,tml){
                     if(!ttx.trimmed().isEmpty()){
                       Mark.append(ttx.toInt());
                     }
                   }
               }
            }
        }while(!tx.isNull());
        fmrk.close();

    }
   // Selang();
    GGen=true;
    PbVal=0;
    foreach(blok tstn,*stn){
        if(!tstn.filwav.isEmpty()){
            PbVal++;
        }
    }


        ui->pbwav->setEnabled(true);
        ui->pbwav->setMaximum(PbMax);
        ui->pbwav->setValue(PbVal);

    if(GGen){
        ui->pushButton_2->setDisabled(true);
        ui->Save_fonem_act->setDisabled(true);
        //CrWavAb();
        //QTimer::singleShot(200, this, SLOT(LoopGen()));
        if(!stn->isEmpty()){
            LoopGen();
        }
    }

}

//удаление формы и закрытие канала связи
Menestrel::~Menestrel()
{
    fply.flush();
    fply.close();
    fcurw.flush();
    fcurw.close();
    FPlay=false;
    if(playw.state() == QProcess::Running){
        playw.kill();
    }
    delete ui;
}

/*
void Menestrel::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
*/

//произнести
void Menestrel::on_ButtonMenestrel_clicked()
{   // если текстовое поле не пустое создаем команды для Festival
    int ib=0;
    int ie=0;
    if (ui->RechText->toPlainText() != "") {
        FPlay=true;
            //новый текст-генерация конфигурационных файлов
            if(Futt1){
                //определяем, с какой точки будем продолжать генерить и проигрывать абзацы
                QTextCursor cur=ui->RechText->textCursor();
                ib=cur.position();
                //Если курсор в начале или его не трогали после загрузки текста, тогда либо с сохраненного положения, либо с начала
                if((ib>=ui->RechText->toPlainText().size()-1)|(ib==0)){
                    cur.setPosition(0);
                    ib=0;
                    GCi=GPi;
                }else{
                    // определяем номер абзаца, по его концу
                    ie=ui->RechText->toPlainText().indexOf("\n",ib);
                    if(ie>0){
                        //Если конец абзаца обнаружен
                        int ibb=0;
                        // пробегаем по таблице разметки
                        foreach(blok tb,*stn){
                            //если курсор в границах очередного абзаца
                            if((ib<=tb.be)&(ib>=tb.bn)){
                                // и этот абзац не первый, то от него начинаем генерировать звук и с него читаем
                                if(ibb>0){
                                    GCi=ibb;
                                    GPi=GCi;
                                }else{
                                  //если 1-й, то с сохраненного или первого все делаем
                                   GCi=GPi;
                                }
                                break;
                            }
                            ibb++;
                        }
                    }else{
                        //Если конца абзаца нет, т.е. курсор за текстом, то с сохраненного или первого все делаем
                        GCi=GPi;
                    }
                }
               //CrWavAb();
            }


                ui->ButtonMenestrel->setDisabled(true);

                FPlay=true;
                if(!stn->isEmpty()){
                    LoopGen();
                }
                QTimer::singleShot(200, this, SLOT(LoopPlay()));
                ui->RechText->setReadOnly(true);

    }
    //формируем   сообщение о невведенном тексте
    else
    {
        QString title = QString::fromUtf8("Скоморох");
        QString msg = QString::fromUtf8("Введите сообщение");
        //вывод сообщения о не заполненной форме msg.trimmed()
        QMessageBox msgBox;
        msgBox.setWindowTitle(title);
        msgBox.setText(msg);
        msgBox.exec();
    }

}

//сохранить фонему
void Menestrel::on_pushButton_2_clicked()
{
    //on_ButtonStop_clicked();
    slex=new SaveLex(this);
    connect(slex, SIGNAL(rest()), this, SLOT(WinRest()));
    slex->show();
}

//Обработка меню
void Menestrel::open_file()
{
    op=new OpenF(false,this);
    connect(op,SIGNAL(openFfn(QString)),this,SLOT(Sopenfn(QString)));
    op->show();

}

void Menestrel::save_file()
{

    on_ButtonPausa_clicked();
     QString tms= ui->RechText->toPlainText();

        TextFileName = QFileDialog::getSaveFileName(this,
                                                    QString::fromUtf8("Сохранить фаил"), QDir::currentPath(),
                                                    "Text files (*.txt)");

      ui->RechText->setPlainText(tms);
      QFile file(TextFileName);
      if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, QString::fromUtf8("Menestrel"),
                             QString::fromUtf8("Запись в фаил %1 не возможна.").arg(TextFileName));
      }else{
           tms.trimmed();
            file.write(tms.toUtf8());
      }
      if(file.isOpen()){
            file.close();
      }

}

void Menestrel::creat_file()
{
    op=new OpenF(true,this);
    connect(op,SIGNAL(creatFcl()),this,SLOT(ScreatCl()));
    connect(op,SIGNAL(creatFfn(QString)),this,SLOT(Screatfn(QString)));
    op->show();

}

void Menestrel::about_file()
{

  if(!QDesktopServices::openUrl(QUrl(QString::fromUtf8("http://menestrel.sourceforge.net/"))))
    {
       QMessageBox::information(
          QApplication::activeWindow(),
          QApplication::applicationName(),
          QString::fromUtf8("Невозможно открыть сведения о программе. Перейдите на сайт http://menestrel.sourceforge.net/"));
   }
}

void Menestrel::find_file()
{
    bool ok;
   QString text = QInputDialog::getText(this, QString::fromUtf8("Найти"),
                                               QString::fromUtf8("Найти:"),
                                               QLineEdit::Normal,
                                               QString::fromUtf8(""), &ok);
   if (!(text.isEmpty() or text.isNull())){
       if (!ui->RechText->find(text, QTextDocument::FindWholeWords)) {
           QMessageBox::information(this, QString::fromUtf8("Menestrel"),
                                QString::fromUtf8(" \"%1\" не найдено.").arg(text));

       }
   }


}

QString Menestrel::reggo(QString txt)
{
 //   QString txt;
 //   txt=QString(s.data());
    txt=txt.trimmed();

    txt.replace(QRegExp("www\\."),QString::fromUtf8("вэвэвэ точка "));
    txt.replace(QRegExp("\\.com"),QString::fromUtf8(" точка ком"));
    txt.replace(QRegExp("\\.ru"),QString::fromUtf8(" точка ру"));
    txt.replace(QRegExp(QString::fromUtf8("т\\.д\\.")),QString::fromUtf8("так далее "));
    txt.replace(QRegExp(QString::fromUtf8("т\\.п\\.")),QString::fromUtf8("том+у под+обное "));
    txt.replace(QRegExp(QString::fromUtf8("т\\.е\\.")),QString::fromUtf8("то есть "));
    txt.replace(QRegExp(QString::fromUtf8("н\\.э\\.")),QString::fromUtf8("нашей эры"));
    txt.replace(QRegExp(QString::fromUtf8("х\\.ф\\.")),QString::fromUtf8("художественный фильм"));
    txt.replace(QRegExp("\\.([^ ])"), "\. \\1");
    if(FZskob){
        txt.replace(QRegExp("[[{(]"),QString::fromUtf8(" скобку открыть, "));
        txt.replace(QRegExp("[]})]"),QString::fromUtf8(" скобку закрыть, "));
    }else{
        txt.replace(QRegExp("[][{}();:]"),", ");
    }
    if(FZzvezd){
        txt.replace(QRegExp("*"),QString::fromUtf8(" звёздочка, "));
    };
    if(FZpodch){
        txt.replace(QRegExp("_"),QString::fromUtf8(" подчеркивание, "));
    };
    if(FZnom){
        txt.replace(QRegExp("\\$"),QString::fromUtf8(" доллар "));
        txt.replace(QRegExp(QString::fromUtf8("№")),QString::fromUtf8(" номер "));
        txt.replace(QRegExp("%"),QString::fromUtf8(" процентов "));
    };
    if(FZravn){
        txt.replace(QRegExp("="),QString::fromUtf8(" равно "));
    }
    if(FZplus){
        txt.replace(QRegExp(QString::fromUtf8("\\+[^АаЯяЭэЕеЁёОоЫыИиУуЮю]")),QString::fromUtf8(" плюс "));
    }else{
        txt.replace(QRegExp(QString::fromUtf8("\\+[^АаЯяЭэЕеЁёОоЫыИиУуЮю]")),QString::fromUtf8(" "));
    }
    txt.replace(QRegExp(",{2,}"),", ");
    txt.replace(QRegExp("\\.{2,}"),"\. ");
    if(FZznk){
        txt.replace(QRegExp("\\?{1,}"),QString::fromUtf8(" в+опр знак. "));
        txt.replace(QRegExp("!{1,}"),QString::fromUtf8(" в+оскл знак. "));
    }else{
        txt.replace(QRegExp("\\?{1,}"),QString::fromUtf8(". "));
        txt.replace(QRegExp("!{1,}"),QString::fromUtf8(". "));
    }
//    txt.replace(QRegExp(QString::fromUtf8("[^A-Za-z0-9А-Яа-яЁё., +\\n]"))," ");
    txt.replace(QRegExp(QString::fromUtf8("[^A-Za-z0-9А-Яа-яЁё., +~]"))," ");
    txt.replace(QRegExp(" {2,}")," ");
    txt.replace(QRegExp(" ,"),",");
    txt.replace(QRegExp(" \\."),".");
    txt.replace(QRegExp(" \\+"),"+");
    //txt=txt.toLower();
    txt.replace(QRegExp(QString::fromUtf8("ё")),QString::fromUtf8("+ё"));
    txt.replace(QRegExp(QString::fromUtf8("Ё")),QString::fromUtf8("+ё"));

    if(!diction.isEmpty()){
        foreach(dict d,diction){
            txt.replace(QRegExp(d.sr.toUtf8()),d.tr.toUtf8());
        }
    }
    //txt.replace(QRegExp(QString::fromUtf8("ь")),QString::fromUtf8("й"));
    return txt;

}

int Menestrel::succes(int hi)
{
    int i=hi;
    while(!stn->at(i).filwav.isEmpty()){
        i++;
        if(i>=stn->size()){
            break;
        }
    };
    if(i>=stn->size()){
        i=0;
        while(!stn->at(i).filwav.isEmpty()){
            i++;
            if(i>=stn->size()){
                break;
            }
        };
        if(i>=stn->size()){
            i=-1;
            return i;
        }else{
            return i;
        }
    }else{
        return i;
    }
}

void Menestrel::CrWavAb()
{
    QString Si;
    int ii;
    Si=Si.number(GCi);
    QDir tdst;
    tdst.setPath(PathW);
    if(tdst.exists(PathW+"/"+Si+".wav")){
        blok *tstn=stn->data();
        tstn[GCi].filwav=PathW+"/"+Si+".wav";
        fcurwst<<Si<<"#"<<stn->at(GCi).filwav<<"\n";
        fcurw.flush();
        PbVal++;
    }
    if(GGen){
        ii=succes(GCi);
        if(ii<0){
                GGen=false;
                //break;
        }else{
            GCi=ii;
            Si=Si.number(ii);
            QFile tmtxt;
            tmtxt.setFileName(PathW+"/"+Si+".txt");
            tmtxt.open(QIODevice::WriteOnly | QIODevice::Text);
            if(Kode=="UTF-8"){
                QTextStream tmtxtst(&tmtxt);
                tmtxtst<<stn->at(GCi).Sw<<"\n";
            }else{
                QTextCodec *codec = QTextCodec::codecForName(Kode.toLocal8Bit());
                QByteArray encodedString = codec->fromUnicode(stn->at(GCi).Sw);
                tmtxt.write(encodedString);
                encodedString = "\n";
                tmtxt.write(encodedString);
            }
            tmtxt.flush();
            tmtxt.close();
            QString text = "/bin/bash "+PathW+"/setprog/fc "+PathW+" "+Si+" "+PitchS;
            Ozvuchit.start(text);
            Ozvuchit.waitForStarted();
         }
        ui->pbwav->setValue(PbVal);
    }
}

void Menestrel::SelAb()
{
    int selb=stn->at(GPi).bn;
    int sele=stn->at(GPi).be;
    QTextCursor cur=ui->RechText->textCursor();
    cur.setPosition(selb);
    cur.setVisualNavigation(true);
    cur.beginEditBlock();
    bool ie=cur.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor,sele-selb+1);
    cur.endEditBlock();
    ui->RechText->setTextCursor(cur);
}

void Menestrel::LoopGen(int vvv)
{
    if(GGen){
            CrWavAb();
    }else {
                ui->Save_fonem_act->setEnabled(true);
                ui->pushButton_2->setEnabled(true);
    }
}

void Menestrel::LoopPlay()
{
  if(FPlay){
    if(GPi<stn->size())
    {
      if(!stn->at(GPi).filwav.isNull()){
        if(tmd.exists(stn->at(GPi).filwav))
        {
            SelAb();
            //QString pcm= "sox -t raw -s -b 8 -r 10000 -c 1 -v 1 "+ stn->at(GPi).filwav+"-t pulseaudio -d"+" tempo "+Temp;
            QString pcm= "play -q "+stn->at(GPi).filwav+" tempo "+Temp+" pitch "+Pitch;
            //QString pcm= "/bin/bash "+PathW+"/setprog/fp "+ stn->at(GPi).filwav+" "+Temp+" "+Pitch+" "+PitchS+" "+Daudio;
            playw.start(pcm);
            playw.waitForStarted();
            QString Sp;
            Sp=Sp.number(GPi);
            fplyst<<Sp<<"\n";
            fply.flush();

        } else
        {
            QTimer::singleShot(700, this, SLOT(LoopPlay()));
        }
      }else
      {
            QTimer::singleShot(700, this, SLOT(LoopPlay()));
      }
    }
  }
}

void Menestrel::LoopPlayF(int cp)
{
    if(FPlay){
        GPi++;
    }
    LoopPlay();
}



void Menestrel::dictin()
{
    cf=new config(this);
    cf->show();
}


void Menestrel::on_ButtonPausa_clicked()
{
    // кнопка пауза
    FPlay=false;
    if(playw.state() == QProcess::Running){
        playw.kill();

        //playw.waitForFinished();
    }
    ui->ButtonMenestrel->setEnabled(true);
    ui->Save_fonem_act->setEnabled(true);
    Futt1=false;
}

void Menestrel::on_ButtonSetMark_clicked()
{
    // кнопка поставить метку
    on_ButtonPausa_clicked();
    ct=ui->RechText->toPlainText();
    mf=new MarkF(false,GPi,ct,this);
    mf->show();
    ui->ButtonMenestrel->setEnabled(true);
    //Futt1=false;
}

void Menestrel::on_ButtonGoMark_clicked()
{
    // кнопка перейти на метку
    on_ButtonPausa_clicked();
    ct=ui->RechText->toPlainText();
    mf=new MarkF(true,GPi,ct,this);
    connect(mf,SIGNAL(gomark(int)),this,SLOT(GoMRK(int)));
    mf->show();
    ui->ButtonMenestrel->setEnabled(true);
    Futt1=false;
}

void Menestrel::on_ButtonStop_clicked()
{
    // кнопка остановить чтение и разрешить редактирование
    on_ButtonPausa_clicked();
    ui->ButtonMenestrel->setEnabled(true);
    ui->RechText->setReadOnly(false);
    SelAb();
    FPlay=false;
    Futt1=true;
}

void Menestrel::on_znak_triggered()
{
    // Пункт менЮ озвучивания знаков припинания и других служебных знаков
    zn=new ZnakTemp(this);
    zn->show();
}

void Menestrel::writeConf(bool bdl)
{
    QFile fznk(PathW+"/setprog/znak.cfg");
    QTextStream fznkst(&fznk);
    QDir tdi;
    if(tdi.exists(PathW+"/setprog/znak.cfg")){
        tdi.remove(PathW+"/setprog/znak.cfg");
    }
    if(fznk.open(QIODevice::WriteOnly|QIODevice::Text)){
        fznkst<<"Temp="<<Temp<<endl;
        fznkst<<"Pitch="<<Pitch<<endl;
        fznkst<<"PitchS="<<PitchS<<endl;
        fznkst<<"Daudio="<<Daudio<<endl;
        fznkst<<"Kode="<<Kode<<endl;
        fznkst<<"PMin="<<PMin<<endl;
        fznkst<<"PNrm="<<PNrm<<endl;
        fznkst<<"PMax="<<PMax<<endl;
        QString s;
        s=(FZnom)?QString("1"):QString("0");
        fznkst<<"FZnom="<<s<<endl;
        s=(FZplus)?QString("1"):QString("0");
        fznkst<<"FZplus="<<s<<endl;
        s=(FZpodch)?QString("1"):QString("0");
        fznkst<<"FZpodch="<<s<<endl;
        s=(FZravn)?QString("1"):QString("0");
        fznkst<<"FZravn="<<s<<endl;
        s=(FZskob)?QString("1"):QString("0");
        fznkst<<"FZskob="<<s<<endl;
        s=(FZznk)?QString("1"):QString("0");
        fznkst<<"FZznk="<<s<<endl;
        s=(FZzvezd)?QString("1"):QString("0");
        fznkst<<"FZzvezd="<<s<<endl;
        fznk.flush();
        fznk.close();
        if(bdl){
            int ic=GPi;
            on_endCrButton_clicked();
            GPi=ic;
            GCi=ic;
            SelAb();
        }
    }

}

void Menestrel::writeMark()
{
    QFile fznk(PathW+"/conf/mark.cfg");
    QTextStream fznkst(&fznk);
    QDir tdi;
    if(tdi.exists(PathW+"/conf/mark.cfg")){
        tdi.remove(PathW+"/conf/mark.cfg");
    }
    if(fznk.open(QIODevice::WriteOnly|QIODevice::Text)){
        fznkst<<"Mark=";
        QString tt;
        foreach(int i,Mark){
                tt=tt.setNum(i);
                fznkst<<tt<<";";
        }
        fznkst<<endl;
        fznk.flush();
        fznk.close();
    }
}

void Menestrel::GoMRK(int fG)
{
        if(fG>=0){
            GPi=fG;
            GCi=fG;
            FPlay=true;
            Futt1=false;
            ui->ButtonMenestrel->setEnabled(true);
            SelAb();
        }else{
            FPlay=true;
            SelAb();
            ui->ButtonMenestrel->setEnabled(true);
        }
        Futt1=false;
}

void Menestrel::on_endCrButton_clicked()
{
    //
    ui->ButtonGoMark->setEnabled(true);
    ui->ButtonMenestrel->setEnabled(true);
    ui->ButtonPausa->setEnabled(true);
    ui->ButtonSetMark->setEnabled(true);
    ui->ButtonStop->setEnabled(true);
    ui->openButton->setEnabled(true);
    ui->Open_act->setEnabled(true);
    ui->saveButton->setEnabled(true);
    ui->Save_act->setEnabled(true);
    if(fcurw.isOpen()){
        fcurw.close();
    }
    if(fply.isOpen()){
        fply.close();
    }

    //очистка каталогов
    tmd.setPath(PathW+"/conf");

    QStringList confd=tmd.entryList(QDir::Files);
    foreach(QString ss,confd){
        tmd.remove(PathW+"/conf/"+ss);
    }
    tmd.setPath(PathW);
    confd=tmd.entryList(QDir::Files);
    foreach(QString ss,confd){
               tmd.remove(PathW+"/"+ss);
    }

    // Предварительная обработка текста- удаление лишних \n
    QString tx=ui->RechText->toPlainText();
    tx=tx+"\n";
//    tx.replace(QRegExp(QString::fromUtf8("\\n[^A-Za-z0-9А-Яа-я., +!?*№%$]{0,}\\n")),"\n");
    ui->RechText->setPlainText(tx);
    //сохранение текста в конфигурации
    if(ftext.open(QIODevice::WriteOnly | QIODevice::Text)){
        ftextst<<tx;
        ftext.flush();
        ftext.close();
    }
    //Формирование таблицы разметки
    int ib=0;
    int ie=0;
    blok tb;
    stn->clear();
    while(ib<tx.size()){
//        ie=tx.indexOf("\n",ib);

        ie=tx.indexOf(QRegExp(QString::fromUtf8("[.!?\\n][^A-Za-zА-Яа-я.,+!?*№%$\\n]{0,}[A-ZА-ЯЁ]")),ib);
        if((ib<tx.size())&(ie<0)){
            ie=tx.size()-1;
        }
        if(ie>0){
            tb.bn=ib;
            tb.be=ie;
            tb.Sw="";
            tb.filwav="";
            *stn<<tb;
        }
        ib=ie+1;
    }
    ib=0;
    foreach(tb,*stn){
        ib++;
        tx.insert(tb.be+ib,"~");
    }
    PbMax=stn->size();
    tx=reggo(tx);
    QStringList tl=tx.split("~");
    ib=0;
    blok *twn=stn->data();
    foreach(QString ttx,tl){
        if(ib>=stn->size()){
            break;
        }
        twn[ib].Sw=(ttx.trimmed()).replace(QRegExp("\n")," ");
        ib++;
    }

    //Запись таблицы разметки в файл
    QString txx;
    QString ttxx;
    fblok.open(QIODevice::WriteOnly | QIODevice::Text);
    for(ib=0;ib<stn->size();ib++){
        fblokst<<ttxx.setNum(stn->at(ib).bn)<<"#"<<txx.setNum(stn->at(ib).be)<<"#"<<stn->at(ib).Sw<<"#"<<stn->at(ib).filwav<<"\n";
    }
    fblok.flush();
    fblok.close();
    //открытие файла вектора сгенерированных абзацев
    fcurw.open(QIODevice::WriteOnly | QIODevice::Text);
    //удаление файла номеров прочитанных абзацев
    //открытие на запись файла номеров прочитанных абзацев
    fply.open(QIODevice::WriteOnly | QIODevice::Text);

//    QString tt=ui->RechText->toPlainText().trimmed();
//    tt.replace(QRegExp(QString::fromUtf8("[^0-9a-zA-Zа-яА-Я]")),"");
    PbVal=0;
    GCi=0;
    GPi=0;
//    stn->clear();
    twv.clear();
    Mark.clear();
    GGen=true;
    Futt1=true;
    TextWind=ui->RechText->toPlainText();
    ui->RechText->setReadOnly(true);
//    Ozvuchit.start("killall festival_client");
//    Ozvuchit.waitForFinished();
    if(PbMax>0){
        ui->pbwav->setEnabled(true);
        ui->pbwav->setMaximum(PbMax);
        ui->pbwav->setValue(PbVal);
    }
    if(GGen){
        ui->pushButton_2->setDisabled(true);
        ui->Save_fonem_act->setDisabled(true);
        //CrWavAb();
        //QTimer::singleShot(200, this, SLOT(LoopGen()));
        if(!stn->isEmpty()){
            LoopGen();
        }
    }

}

void Menestrel::ScreatCl()
{
     //создать пустой файл
    TextFileName.clear();
    ui->ButtonGoMark->setDisabled(true);
    ui->ButtonMenestrel->setDisabled(true);
    ui->ButtonPausa->setDisabled(true);
    ui->ButtonSetMark->setDisabled(true);
    ui->ButtonStop->setDisabled(true);
    ui->openButton->setDisabled(true);
    ui->Open_act->setDisabled(true);
    ui->saveButton->setDisabled(true);
    ui->Save_act->setDisabled(true);
    ui->RechText->setReadOnly(false);
    ui->RechText->clear();


}

void Menestrel::Screatfn(QString nm)
{
    //создать на основе файла с именем nm
    ui->ButtonGoMark->setDisabled(true);
    ui->ButtonMenestrel->setDisabled(true);
    ui->ButtonPausa->setDisabled(true);
    ui->ButtonSetMark->setDisabled(true);
    ui->ButtonStop->setDisabled(true);
    ui->openButton->setDisabled(true);
    ui->Open_act->setDisabled(true);
    ui->saveButton->setDisabled(true);
    ui->Save_act->setDisabled(true);
    ui->Save_fonem_act->setDisabled(true);
    ui->RechText->clear();
    QFile inputFile(nm);
    inputFile.open(QIODevice::ReadOnly);

    QTextStream in(&inputFile);
    QString line = in.readAll();
    inputFile.close();

    ui->RechText->setPlainText(line);

}

void Menestrel::Sopenfn(QString nm)
{
    //открыть при помощи файла с именем nm
    if(!nm.isEmpty()){
        ui->RechText->setReadOnly(false);
        ui->RechText->clear();
        QFile inputFile(nm);
        inputFile.open(QIODevice::ReadOnly);

        QTextStream in(&inputFile);
        QString line = in.readAll();
        inputFile.close();

        ui->RechText->setPlainText(line);
        on_endCrButton_clicked();
    }
}


void Menestrel::WinRest()
{
    ui->RechText->setPlainText(TextWind);
}
