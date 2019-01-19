/********************************************************************************
** Form generated from reading UI file 'controlform.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLFORM_H
#define UI_CONTROLFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlForm
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *pushButton_loopStart;
    QPushButton *pushButton_loopStop;
    QPushButton *pushButton_reset;
    QLineEdit *lineEdit;
    QLabel *label_2;

    void setupUi(QWidget *ControlForm)
    {
        if (ControlForm->objectName().isEmpty())
            ControlForm->setObjectName(QStringLiteral("ControlForm"));
        ControlForm->resize(214, 192);
//        ControlForm->setTabletTracking(false);
        layoutWidget = new QWidget(ControlForm);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 189, 144));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        gridLayout->addWidget(label, 1, 0, 1, 2);

        pushButton_loopStart = new QPushButton(layoutWidget);
        pushButton_loopStart->setObjectName(QStringLiteral("pushButton_loopStart"));

        gridLayout->addWidget(pushButton_loopStart, 3, 0, 1, 1);

        pushButton_loopStop = new QPushButton(layoutWidget);
        pushButton_loopStop->setObjectName(QStringLiteral("pushButton_loopStop"));

        gridLayout->addWidget(pushButton_loopStop, 3, 1, 1, 1);

        pushButton_reset = new QPushButton(layoutWidget);
        pushButton_reset->setObjectName(QStringLiteral("pushButton_reset"));

        gridLayout->addWidget(pushButton_reset, 2, 0, 1, 1);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 2, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font1;
        font1.setPointSize(19);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 0, 0, 1, 2);


        retranslateUi(ControlForm);

        QMetaObject::connectSlotsByName(ControlForm);
    } // setupUi

    void retranslateUi(QWidget *ControlForm)
    {
        ControlForm->setWindowTitle(QApplication::translate("ControlForm", "Form", 0));
        label->setText(QApplication::translate("ControlForm", "\343\200\200\350\257\267\351\200\211\346\213\251\346\216\247\345\210\266\345\267\245\344\275\215\346\225\260\351\207\217", 0));
        pushButton_loopStart->setText(QApplication::translate("ControlForm", "\345\274\200\345\247\213", 0));
        pushButton_loopStop->setText(QApplication::translate("ControlForm", "\346\232\202\345\201\234", 0));
        pushButton_reset->setText(QApplication::translate("ControlForm", "\346\270\205\351\233\266", 0));
        label_2->setText(QApplication::translate("ControlForm", "       \346\200\273\346\216\247\345\210\266\345\217\260\343\200\200", 0));
    } // retranslateUi

};

namespace Ui {
    class ControlForm: public Ui_ControlForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLFORM_H
