#ifndef MARKF_H
#define MARKF_H

#include <QDialog>
#include <QtGui>
//#include <mn.h>

namespace Ui {
    class MarkF;
}

class MarkF : public QDialog
{
    Q_OBJECT

public:
    explicit MarkF(bool go, int m, QString ct, QWidget *parent = 0);
    ~MarkF();

signals:
    void gomark(int);

private:
    Ui::MarkF *ui_m;
    QStringListModel *model;
    QItemSelectionModel *selectionModel;
    QList<int> li;
 //   int * fff;
    QString sct;
    QObject *ppp;

private slots:
    void on_EndEdit_rejected();
    void on_EndEdit_accepted();
    void on_exitMark_clicked();
    void on_GoMark_clicked();
    void on_delMark_clicked();
    void on_listMark_activated(QModelIndex index);
};

#endif // MARKF_H
