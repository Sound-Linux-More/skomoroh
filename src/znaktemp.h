#ifndef ZNAKTEMP_H
#define ZNAKTEMP_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
    class ZnakTemp;
}

class ZnakTemp : public QDialog
{
    Q_OBJECT

public:
    explicit ZnakTemp(QWidget *parent = 0);
    ~ZnakTemp();

private:
    Ui::ZnakTemp *ui_z;
    bool FZzvezd; //звездочка
    bool FZpodch; //подчеркивание
    bool FZravn; //равно
    bool FZplus;  //плюс
    bool FZnom;   //номер доллар процент
    bool FZznk;   //озвучить !?
    bool FZskob;  //скобки
    // Файл и поток знаков и темпа
    // Темп воспроизведения- 1-нормальный, 1.1 ... 2- ускоренный, 0.9 ... 0.5 -замедленный
    QString Temp;
    QString Pitch;
    QString PitchS;
    QString Daudio;
    QString Kode;
    QString PMin;
    QString PNrm;
    QString PMax;
    QObject *ppp;
    void setPitch2(QString val);
    QString getPitch2();
    void rzrd(QString com);
    QStringList drv;
    QStringList kdr;
    QStringList mnm;
    QStringList nrmn;
    QStringList mxm;
    bool bdl;
    QString papp;

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_toolButton_clicked();
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
    void on_nomer_toggled(bool checked);
    void on_znaks_toggled(bool checked);
    void on_skob_toggled(bool checked);
    void on_plus_toggled(bool checked);
    void on_ravno_toggled(bool checked);
    void on_podch_toggled(bool checked);
    void on_zvezd_toggled(bool checked);
    void on_pitchsl_valueChanged(int value);
    void on_driv_currentIndexChanged(int index);
    void on_pitchss_valueChanged(int value);
    void on_gener_editingFinished();
    void on_kode_currentIndexChanged(int index);
    void on_kak_clicked();
};

#endif // ZNAKTEMP_H
