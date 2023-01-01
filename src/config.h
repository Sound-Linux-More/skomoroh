#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include <QAbstractItemModel>
#include <QItemSelectionModel>

namespace Ui {
    class config;
}
// Строка словаря ударений

class config : public QDialog
{
    Q_OBJECT

public:
    explicit config(QWidget *parent = 0);
    ~config();

private:
    Ui::config *ui_c;
    QAbstractItemModel *model;
    QAbstractItemModel *model1;
    QItemSelectionModel *selectionModel;
    QItemSelectionModel *selectionModel1;
    QObject *pp;

private slots:
    void on_deldic_clicked();
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
    void on_insdic_clicked();
};

#endif // CONFIG_H
