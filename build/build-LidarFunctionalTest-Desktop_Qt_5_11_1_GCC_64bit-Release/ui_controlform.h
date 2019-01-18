/********************************************************************************
** Form generated from reading UI file 'controlform.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLFORM_H
#define UI_CONTROLFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlForm
{
public:
    QPushButton *OpenChoseUART;
    QLineEdit *lineEdit;
    QPushButton *pushButton_MoterEn;
    QPushButton *pushButton_ModeON;
    QPushButton *pushButton_ModeOFF;
    QPushButton *pushButton_StopScan;

    void setupUi(QWidget *ControlForm)
    {
        if (ControlForm->objectName().isEmpty())
            ControlForm->setObjectName(QStringLiteral("ControlForm"));
        ControlForm->resize(221, 217);
        ControlForm->setTabletTracking(false);
        OpenChoseUART = new QPushButton(ControlForm);
        OpenChoseUART->setObjectName(QStringLiteral("OpenChoseUART"));
        OpenChoseUART->setGeometry(QRect(30, 30, 91, 31));
        lineEdit = new QLineEdit(ControlForm);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(130, 30, 51, 31));
        lineEdit->setTabletTracking(true);
        lineEdit->setEchoMode(QLineEdit::Normal);
        pushButton_MoterEn = new QPushButton(ControlForm);
        pushButton_MoterEn->setObjectName(QStringLiteral("pushButton_MoterEn"));
        pushButton_MoterEn->setGeometry(QRect(30, 70, 89, 25));
        pushButton_MoterEn->setCheckable(true);
        pushButton_ModeON = new QPushButton(ControlForm);
        pushButton_ModeON->setObjectName(QStringLiteral("pushButton_ModeON"));
        pushButton_ModeON->setGeometry(QRect(30, 130, 89, 25));
        pushButton_ModeOFF = new QPushButton(ControlForm);
        pushButton_ModeOFF->setObjectName(QStringLiteral("pushButton_ModeOFF"));
        pushButton_ModeOFF->setGeometry(QRect(30, 100, 89, 25));
        pushButton_StopScan = new QPushButton(ControlForm);
        pushButton_StopScan->setObjectName(QStringLiteral("pushButton_StopScan"));
        pushButton_StopScan->setGeometry(QRect(30, 160, 89, 25));

        retranslateUi(ControlForm);

        QMetaObject::connectSlotsByName(ControlForm);
    } // setupUi

    void retranslateUi(QWidget *ControlForm)
    {
        ControlForm->setWindowTitle(QApplication::translate("ControlForm", "Form", nullptr));
        OpenChoseUART->setText(QApplication::translate("ControlForm", "Open", nullptr));
        lineEdit->setInputMask(QString());
        pushButton_MoterEn->setText(QApplication::translate("ControlForm", "MoterEn", nullptr));
        pushButton_ModeON->setText(QApplication::translate("ControlForm", "ModeON", nullptr));
        pushButton_ModeOFF->setText(QApplication::translate("ControlForm", "ModeOFF", nullptr));
        pushButton_StopScan->setText(QApplication::translate("ControlForm", "StopScan", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlForm: public Ui_ControlForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLFORM_H
