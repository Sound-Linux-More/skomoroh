#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QDialog>

namespace Ui {
    class Language;
}

class Language : public QDialog
{
    Q_OBJECT

public:
    explicit Language( QWidget *parent = 0);
    ~Language();

signals:
    void elang();

private:
    Ui::Language *ui_l;
    QStringList lg;
    QStringList lgn;
    QObject *ppp;

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
};

#endif // LANGUAGE_H
