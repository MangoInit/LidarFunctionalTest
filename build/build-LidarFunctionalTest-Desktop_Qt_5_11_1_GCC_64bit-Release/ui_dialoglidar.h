/********************************************************************************
** Form generated from reading UI file 'dialoglidar.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGLIDAR_H
#define UI_DIALOGLIDAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogLidar
{
public:
    QPushButton *pushButton_open;
    QPushButton *pushButton_getInfo;
    QPushButton *pushButton_getHealth;
    QPushButton *pushButton_stopScan;
    QPushButton *pushButton_MoterEn;
    QPushButton *pushButton_IntensityON;
    QPushButton *pushButton_IntensityOFF;
    QPushButton *pushButton_loopTest;
    QPushButton *pushButton_loopStop;
    QLabel *label_5;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_8;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_4;
    QLCDNumber *lcdNumber_switch_Y;
    QLCDNumber *lcdNumber_switch_N;
    QLabel *label_2;
    QLCDNumber *lcdNumber_Intensity_Y;
    QLCDNumber *lcdNumber_Intensity_N;
    QLabel *label_3;
    QLCDNumber *lcdNumber_Blind_Y;
    QLCDNumber *lcdNumber_Blind_N;
    QLabel *label_9;
    QLCDNumber *lcdNumber_ID;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_4;
    QFrame *line_5;
    QLCDNumber *lcdNumber_uart;
    QPushButton *pushButton;

    void setupUi(QDialog *DialogLidar)
    {
        if (DialogLidar->objectName().isEmpty())
            DialogLidar->setObjectName(QStringLiteral("DialogLidar"));
        DialogLidar->resize(235, 236);
        pushButton_open = new QPushButton(DialogLidar);
        pushButton_open->setObjectName(QStringLiteral("pushButton_open"));
        pushButton_open->setGeometry(QRect(90, 10, 41, 21));
        pushButton_getInfo = new QPushButton(DialogLidar);
        pushButton_getInfo->setObjectName(QStringLiteral("pushButton_getInfo"));
        pushButton_getInfo->setGeometry(QRect(120, 40, 41, 21));
        pushButton_getHealth = new QPushButton(DialogLidar);
        pushButton_getHealth->setObjectName(QStringLiteral("pushButton_getHealth"));
        pushButton_getHealth->setGeometry(QRect(170, 30, 51, 21));
        pushButton_stopScan = new QPushButton(DialogLidar);
        pushButton_stopScan->setObjectName(QStringLiteral("pushButton_stopScan"));
        pushButton_stopScan->setGeometry(QRect(180, 10, 41, 21));
        pushButton_MoterEn = new QPushButton(DialogLidar);
        pushButton_MoterEn->setObjectName(QStringLiteral("pushButton_MoterEn"));
        pushButton_MoterEn->setGeometry(QRect(130, 10, 51, 21));
        pushButton_MoterEn->setCheckable(true);
        pushButton_MoterEn->setChecked(false);
        pushButton_IntensityON = new QPushButton(DialogLidar);
        pushButton_IntensityON->setObjectName(QStringLiteral("pushButton_IntensityON"));
        pushButton_IntensityON->setGeometry(QRect(120, 70, 51, 21));
        pushButton_IntensityOFF = new QPushButton(DialogLidar);
        pushButton_IntensityOFF->setObjectName(QStringLiteral("pushButton_IntensityOFF"));
        pushButton_IntensityOFF->setGeometry(QRect(180, 70, 51, 21));
        pushButton_loopTest = new QPushButton(DialogLidar);
        pushButton_loopTest->setObjectName(QStringLiteral("pushButton_loopTest"));
        pushButton_loopTest->setGeometry(QRect(10, 200, 89, 25));
        pushButton_loopTest->setCheckable(false);
        pushButton_loopStop = new QPushButton(DialogLidar);
        pushButton_loopStop->setObjectName(QStringLiteral("pushButton_loopStop"));
        pushButton_loopStop->setGeometry(QRect(130, 200, 89, 25));
        label_5 = new QLabel(DialogLidar);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(11, 50, 41, 21));
        layoutWidget = new QWidget(DialogLidar);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 70, 210, 121));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 0, 0, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(label_6, 0, 1, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 0, 2, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font;
        font.setPointSize(13);
        label_4->setFont(font);

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        lcdNumber_switch_Y = new QLCDNumber(layoutWidget);
        lcdNumber_switch_Y->setObjectName(QStringLiteral("lcdNumber_switch_Y"));
        lcdNumber_switch_Y->setStyleSheet(QStringLiteral("border: 1px solid black; color:  red; background: silver;"));
        lcdNumber_switch_Y->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(lcdNumber_switch_Y, 1, 1, 1, 1);

        lcdNumber_switch_N = new QLCDNumber(layoutWidget);
        lcdNumber_switch_N->setObjectName(QStringLiteral("lcdNumber_switch_N"));
        lcdNumber_switch_N->setStyleSheet(QStringLiteral("border: 1px solid black; color:  red; background: silver;"));
        lcdNumber_switch_N->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(lcdNumber_switch_N, 1, 2, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        lcdNumber_Intensity_Y = new QLCDNumber(layoutWidget);
        lcdNumber_Intensity_Y->setObjectName(QStringLiteral("lcdNumber_Intensity_Y"));
        lcdNumber_Intensity_Y->setStyleSheet(QStringLiteral("border: 1px solid black; color:  red; background: silver;"));
        lcdNumber_Intensity_Y->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(lcdNumber_Intensity_Y, 2, 1, 1, 1);

        lcdNumber_Intensity_N = new QLCDNumber(layoutWidget);
        lcdNumber_Intensity_N->setObjectName(QStringLiteral("lcdNumber_Intensity_N"));
        lcdNumber_Intensity_N->setStyleSheet(QStringLiteral("border: 1px solid black; color:  red; background: silver;"));
        lcdNumber_Intensity_N->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(lcdNumber_Intensity_N, 2, 2, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        lcdNumber_Blind_Y = new QLCDNumber(layoutWidget);
        lcdNumber_Blind_Y->setObjectName(QStringLiteral("lcdNumber_Blind_Y"));
        lcdNumber_Blind_Y->setStyleSheet(QStringLiteral("border: 1px solid black; color:  red; background: silver;"));
        lcdNumber_Blind_Y->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(lcdNumber_Blind_Y, 3, 1, 1, 1);

        lcdNumber_Blind_N = new QLCDNumber(layoutWidget);
        lcdNumber_Blind_N->setObjectName(QStringLiteral("lcdNumber_Blind_N"));
        lcdNumber_Blind_N->setStyleSheet(QStringLiteral("border: 1px solid black; color:  red; background: silver;"));
        lcdNumber_Blind_N->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(lcdNumber_Blind_N, 3, 2, 1, 1);

        label_9 = new QLabel(DialogLidar);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 10, 61, 21));
        label_9->setFont(font);
        lcdNumber_ID = new QLCDNumber(DialogLidar);
        lcdNumber_ID->setObjectName(QStringLiteral("lcdNumber_ID"));
        lcdNumber_ID->setGeometry(QRect(50, 10, 31, 31));
        lcdNumber_ID->setStyleSheet(QLatin1String("border: 1px solid black; \n"
"color: rgb(0, 0, 0);\n"
"background-color: rgb(186, 189, 182);"));
        lcdNumber_ID->setDigitCount(2);
        lcdNumber_ID->setSegmentStyle(QLCDNumber::Flat);
        line = new QFrame(DialogLidar);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(-20, 220, 261, 21));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(DialogLidar);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(-30, -9, 271, 31));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(DialogLidar);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(-10, -10, 31, 251));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(DialogLidar);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(220, -10, 20, 251));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        lcdNumber_uart = new QLCDNumber(DialogLidar);
        lcdNumber_uart->setObjectName(QStringLiteral("lcdNumber_uart"));
        lcdNumber_uart->setGeometry(QRect(50, 50, 20, 20));
        lcdNumber_uart->setStyleSheet(QLatin1String("color: rgb(211, 215, 207);\n"
"background-color: rgb(211, 215, 207);"));
        pushButton = new QPushButton(DialogLidar);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(100, 30, 61, 31));
        label_5->raise();
        pushButton_stopScan->raise();
        layoutWidget->raise();
        pushButton_open->raise();
        pushButton_getInfo->raise();
        pushButton_getHealth->raise();
        pushButton_MoterEn->raise();
        pushButton_IntensityON->raise();
        pushButton_IntensityOFF->raise();
        pushButton_loopTest->raise();
        pushButton_loopStop->raise();
        label_9->raise();
        lcdNumber_ID->raise();
        line->raise();
        line_2->raise();
        line_4->raise();
        line_5->raise();
        lcdNumber_uart->raise();
        pushButton->raise();

        retranslateUi(DialogLidar);

        QMetaObject::connectSlotsByName(DialogLidar);
    } // setupUi

    void retranslateUi(QDialog *DialogLidar)
    {
        DialogLidar->setWindowTitle(QApplication::translate("DialogLidar", "Dialog", nullptr));
        pushButton_open->setText(QApplication::translate("DialogLidar", "UART", nullptr));
        pushButton_getInfo->setText(QApplication::translate("DialogLidar", "Info", nullptr));
        pushButton_getHealth->setText(QApplication::translate("DialogLidar", "Health", nullptr));
        pushButton_stopScan->setText(QApplication::translate("DialogLidar", "Stop", nullptr));
        pushButton_MoterEn->setText(QApplication::translate("DialogLidar", "Moter", nullptr));
        pushButton_IntensityON->setText(QApplication::translate("DialogLidar", "Inten", nullptr));
        pushButton_IntensityOFF->setText(QApplication::translate("DialogLidar", "Blind", nullptr));
        pushButton_loopTest->setText(QApplication::translate("DialogLidar", "\346\265\213\350\257\225\345\274\200\345\247\213", nullptr));
        pushButton_loopStop->setText(QApplication::translate("DialogLidar", "\346\232\202\345\201\234", nullptr));
        label_5->setText(QApplication::translate("DialogLidar", "\344\270\262\345\217\243", nullptr));
        label_8->setText(QApplication::translate("DialogLidar", "Narwel", nullptr));
        label_6->setText(QApplication::translate("DialogLidar", "  \351\200\232\350\277\207", nullptr));
        label_7->setText(QApplication::translate("DialogLidar", "  \344\270\215\351\200\232\350\277\207", nullptr));
        label_4->setText(QApplication::translate("DialogLidar", "\345\274\200\345\205\263\345\210\207\346\215\242", nullptr));
        label_2->setText(QApplication::translate("DialogLidar", "\345\205\211\345\274\272\346\243\200\346\265\213", nullptr));
        label_3->setText(QApplication::translate("DialogLidar", "\347\202\271\346\225\260\347\233\262\345\214\272", nullptr));
        label_9->setText(QApplication::translate("DialogLidar", "\345\267\245\344\275\215", nullptr));
        pushButton->setText(QApplication::translate("DialogLidar", "\346\270\205\351\233\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogLidar: public Ui_DialogLidar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLIDAR_H
