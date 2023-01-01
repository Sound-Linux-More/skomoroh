/********************************************************************************
** Form generated from reading UI file 'menestrel.ui'
**
** Created: Mon Jul 5 21:34:55 2010
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENESTREL_H
#define UI_MENESTREL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Menestrel
{
public:
    QWidget *centralWidget;
    QPlainTextEdit *RechText;
    QPushButton *ButtonMenestrel;
    QComboBox *comboBox;
    QLabel *label_path;
    QPushButton *pushButton;
    QLabel *label;
    QPushButton *pushButton_2;

    void setupUi(QMainWindow *Menestrel)
    {
        if (Menestrel->objectName().isEmpty())
            Menestrel->setObjectName(QString::fromUtf8("Menestrel"));
        Menestrel->resize(600, 331);
        centralWidget = new QWidget(Menestrel);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        RechText = new QPlainTextEdit(centralWidget);
        RechText->setObjectName(QString::fromUtf8("RechText"));
        RechText->setGeometry(QRect(13, 12, 401, 311));
        ButtonMenestrel = new QPushButton(centralWidget);
        ButtonMenestrel->setObjectName(QString::fromUtf8("ButtonMenestrel"));
        ButtonMenestrel->setGeometry(QRect(440, 290, 101, 31));
        ButtonMenestrel->setCheckable(false);
        ButtonMenestrel->setChecked(false);
        ButtonMenestrel->setAutoDefault(true);
        comboBox = new QComboBox(centralWidget);
        comboBox->addItem(QString::fromUtf8("(language_russian)"));
        comboBox->addItem(QString::fromUtf8("(language_british_english)"));
        comboBox->addItem(QString::fromUtf8("(language_italian)"));
        comboBox->addItem(QString::fromUtf8("(language_american_english)"));
        comboBox->addItem(QString::fromUtf8("(language_finnish)"));
        comboBox->addItem(QString::fromUtf8("(language_czech)"));
        comboBox->addItem(QString::fromUtf8("(language_scots_gaelic)"));
        comboBox->addItem(QString::fromUtf8("(language_welsh)"));
        comboBox->addItem(QString::fromUtf8("(language_castillian_spanish)"));
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setEnabled(true);
        comboBox->setGeometry(QRect(428, 50, 161, 31));
        label_path = new QLabel(centralWidget);
        label_path->setObjectName(QString::fromUtf8("label_path"));
        label_path->setGeometry(QRect(430, 100, 161, 21));
        label_path->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(440, 130, 93, 27));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(430, 20, 151, 17));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(440, 180, 141, 27));
        Menestrel->setCentralWidget(centralWidget);

        retranslateUi(Menestrel);

        QMetaObject::connectSlotsByName(Menestrel);
    } // setupUi

    void retranslateUi(QMainWindow *Menestrel)
    {
        Menestrel->setWindowTitle(QApplication::translate("Menestrel", "Menestrel", 0, QApplication::UnicodeUTF8));
        RechText->setPlainText(QApplication::translate("Menestrel", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\200\320\265\321\207\321\214 \320\264\320\273\321\217 \321\207\321\202\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        ButtonMenestrel->setText(QApplication::translate("Menestrel", "\320\223\320\276\320\273\320\276\321\201", 0, QApplication::UnicodeUTF8));
        comboBox->setItemText(9, QApplication::translate("Menestrel", "(language_klingon)", 0, QApplication::UnicodeUTF8));
        comboBox->setItemText(10, QApplication::translate("Menestrel", "default", 0, QApplication::UnicodeUTF8));

        label_path->setText(QApplication::translate("Menestrel", "\320\243\320\272\320\260\320\267\320\260\321\202\321\214 \320\277\321\203\321\202\321\214 \320\272 Festival", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Menestrel", "\320\236\320\261\320\267\320\276\321\200", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Menestrel", "\320\257\320\267\321\213\320\272 \320\264\320\273\321\217 \321\201\320\270\320\275\321\202\320\265\320\267\320\260", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("Menestrel", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\262 \321\204\320\260\320\270\320\273", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Menestrel: public Ui_Menestrel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENESTREL_H
