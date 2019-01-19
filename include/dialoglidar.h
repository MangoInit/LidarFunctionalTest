#ifndef DIALOGLIDAR_H
#define DIALOGLIDAR_H

#include <QDialog>
#include <QTime>
#include "include/uart.h"
#include "include/flashgo.h"
#include "include/flashgodriver.h"
#define DELAY_SECONDS 26

namespace Ui {
class DialogLidar;
}

class DialogLidar : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLidar(QWidget *parent = nullptr);
    ~DialogLidar();
    int Lidar_numver;
    QString lidar_dev;
    QString mcu_dev;
    FlashgoDriver *m_flashgoDriver;

    Ui::DialogLidar *ui;
    QThread *m_thread;

signals:
    void grab_ScanData();

    void loop();

public slots:

    void Ass_num_dev(int num, QString lidar_port, QString mcu_port);

    void on_pushButton_open_clicked();

    void on_pushButton_getInfo_clicked();

    void on_pushButton_getHealth_clicked();

    void on_pushButton_stopScan_clicked();

    void on_pushButton_MoterEn_clicked(bool checked);

    void on_pushButton_IntensityON_clicked();

    void on_pushButton_IntensityOFF_clicked();


    void on_pushButton_loopTest_clicked();

    void on_pushButton_loopStop_clicked();

    void on_pushButton_clicked();

private slots:
    void sl_loop_end();

    void sl_uart_dis(bool);

    void sl_result_dis(LidarResultDisplay);

//    void on_pushButton_loopTest_clicked();

//    void on_pushButton_loopStop_clicked();

//    void on_pushButton_clicked();

private:
//    Ui::DialogLidar *ui;
//    QThread *m_thread;

    void Delay_MSec(int msec);
};

#endif // DIALOGLIDAR_H
