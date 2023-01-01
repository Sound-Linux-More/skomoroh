#ifndef SAVELEX_H
#define SAVELEX_H

#include <QDialog>
#include <QString>
#include <QProcess>

namespace Ui {
    class SaveLex;
}

class SaveLex : public QDialog
{
    Q_OBJECT

public:
    explicit SaveLex(QWidget *parent = 0);
    ~SaveLex();

signals:
    void rest();

private slots:
    void on_toolButton_clicked();

    void on_lame(int cp);

    void on_ok_clicked();

    void on_cancel_clicked();

private:
    Ui::SaveLex *ui;
    QString Ffilename;
    QString ncat;
    QString Path;
    QProcess pw;
    QObject *pp;
    int cur;
    int mx;
    int FnumberLexem;
};

#endif // SAVELEX_H
