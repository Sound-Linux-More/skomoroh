#ifndef OPENF_H
#define OPENF_H

#include <QDialog>
#include <QFileDialog>
#include <QDir>
namespace Ui {
    class OpenF;
}

class OpenF : public QDialog
{
    Q_OBJECT

public:
    explicit OpenF(bool Creat,QWidget *parent = 0);
    ~OpenF();

signals:
    void creatFcl();
    void creatFfn(QString);
    void openFfn(QString);

private slots:
    void on_clearCreat_toggled(bool checked);

    void on_fileCreat_clicked(bool checked);

    void on_fileDial_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::OpenF *ui_o;
    bool FEmpty;
    bool Fcreat;
    QString TextFileName;
    QString papp;
};

#endif // OPENF_H
