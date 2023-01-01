#ifndef MENESTREL_H
#define MENESTREL_H

#include <QMainWindow>
#include <QProcess>
#include <QDir>
#include <QTextStream>
//#include "language.h"
#include "config.h"
#include "openf.h"
#include "markf.h"
#include "znaktemp.h"
#include "savelex.h"

// Глобальные типы

// Сегмент генерации stn
typedef struct{
    int bn;
    int be;
    QString Sw;
    QString filwav;
} blok;
// Промежуточный вектор генерации
typedef struct{
    int n;
    QString filwav;
} curwav;
// Строка словаря ударений
typedef struct{
    QString sr;
    QString tr;
}dict;

namespace Ui {
    class Menestrel;
}

class Menestrel : public QMainWindow {
    Q_OBJECT
public:
    Menestrel(QWidget *parent = 0);
    ~Menestrel();
    void writeConf(bool bdl);
    void writeMark();


    //QString Lang;
    //QString Fpath;
    //Объявление переменной языка. Выбор русского языка по умолчанию

    //QString Flang  = "(language_russian)";
    QString Flang;
    // Словарь ударений
    QVector<dict> diction;
    //флаги замены
    bool FZzvezd; //звездочка
    bool FZpodch; //подчеркивание
    bool FZravn; //равно
    bool FZplus;  //плюс
    bool FZnom;   //номер доллар процент
    bool FZznk;   //озвучить !?
    bool FZskob;  //скобки
    // Файл и поток знаков и темпа
    QFile fznk;
    QTextStream fznkst;
    // Темп воспроизведения- 1-нормальный, 1.1 ... 2- ускоренный, 0.9 ... 0.5 -замедленный
    QString Temp;
    // Высота голоса воспроизведения
    QString Pitch;
    // Темп воспроизведения- 1-нормальный, 1.1 ... 2- ускоренный, 0.9 ... 0.5 -замедленный
    QString TempS;
    // Высота голоса воспроизведения
    QString PitchS;
    // Аудиодрайвер pulseaudio,alsa,ao,oss, ossdsp,sunau
    QString Daudio;
    QString Kode;
    QString PMin;
    QString PNrm;
    QString PMax;
    // Отметки текста, но не более 50
    QList<int> Mark;
    // Переменная с путем до звуковых файлов
    QString PathW;
    //текущий каталог программы
    QString papp;
    //глобальная таблица звуковых файлов абзацев
    QVector<blok> *stn;
    //Сохранение текста
    QString TextWind;


protected:
    //void changeEvent(QEvent *e);

private:
    Ui::Menestrel *ui;
    QString reggo(QString txt);
    void CrWavAb();
    void SelAb();
    int succes(int hi);
    //промежуточный вектор генерации
    QVector<curwav> twv;
    //глобальные переменные
    //переменная-процесс для запуска Festival
    QProcess Ozvuchit;
    //переменная-процесс для запуска проигрывателя play c эффектом tempo(темр произнесения)
    QProcess playw;
    QProcess Serv;
    // Код возврата процесса playw
    int ECPl;
    // счетчик генерированных WAV-файлов
    int GCi;
    // счетчик произносимых WAV-файлов
    int GPi;
    // счетчик проверяемых WAV-файлов
    int GTi;
    // текущая позиция в окне
    int Gpos;
    QDir tmd;
    // Переменная -признак генерации звукового трека по предложениям
    bool GGen;
    //Переменная для альтернативной комадны выбора языка
    bool Faltlang;


    //формирование путя к программе в зависимости от ОС
    QString  Fp;

    //имя файла для синтезированного wav файла
    QString  Ffilename;

    //числовой суфикс к сохраняемому имни файла если фаил с таким именем существует
    //int FnumberLexem;

    //созданна ли переменная произношения utt1 введенному тексту
    bool Futt1;

    //Переменная хранящая имя открытого текстового файла
    QString TextFileName;


    //Файлы и потоки
    // Читаемый и сохраненный текст и его поток
    QFile ftext;
    QTextStream ftextst;
    // Файл и поток разбора текста
    QFile fblok;
    QTextStream fblokst;
    // Файл и поток текущей генерации звука
    QFile fcurw;
    QTextStream fcurwst;
    // Файл и поток текущего произнесенного абзаца
    QFile fply;
    QTextStream fplyst;
    // Файл и поток текущего словаря ударений
    QFile fdict;
    QTextStream fdictst;
    //QFile flng;
    //QTextStream flngst;

    //Режим чтения
    bool FPlay;
    //Абзац, на который перейти
    int fG;
    //количество абзацев
    int PbMax;
    // количество сгенерированных абзацев
    int PbVal;
    //окно выбора языка
    //Language *lg;
    //окно конфигурации
    config *cf;
    //окно работы с закладками
    MarkF *mf;
    //окно настройки озвучки знаков и темпа чтения
    ZnakTemp *zn;
    //окно открытия исходного файла
    OpenF *op;
    //окно сохранения лексемы
    SaveLex *slex;

    QString ct;

private slots:
    void on_znak_triggered();
    void on_ButtonStop_clicked();
    void on_ButtonGoMark_clicked();
    void on_ButtonSetMark_clicked();
    void on_ButtonPausa_clicked();
    void on_pushButton_2_clicked();
    void on_ButtonMenestrel_clicked();
    //искусственные слоты для меню и прочих
    void open_file();
    void save_file();
    void creat_file();
    void about_file();
    void find_file();
    //for festival
    void LoopGen(int vvv = 0 );
    void LoopPlay();
    void LoopPlayF(int ECPl);
    //void langin();
    void dictin();
    void GoMRK( int );
    void on_endCrButton_clicked();
    void ScreatCl();
    void Screatfn(QString);
    void Sopenfn(QString);
    //void Selang();
    void WinRest();
};

#endif // MENESTREL_H
