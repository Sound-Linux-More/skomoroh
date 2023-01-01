#ifndef MN_H
#define MN_H
#include <QMainWindow>
//#include <QProcess>
#include <QDir>
#include <QTextStream>

// Глобальные типы

// Сегмент генерации stn
typedef struct{
    int bn;
    int be;
    QString Sw;
    QString filwav;
} blok;
// Промежуточный вектор генерации
//typedef struct{
//    int n;
//    QString filwav;
//} curwav;
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
    void writeConf();
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
    // Отметки текста, но не более 50
    QList<int> Mark;
    // Переменная с путем до звуковых файлов
    QString PathW;
    //глобальная таблица звуковых файлов абзацев
    QVector<blok> *stn;

};

#endif // MN_H
