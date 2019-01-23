#include "include/dialoglidar.h"
#include "ui_dialoglidar.h"

DialogLidar::DialogLidar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLidar)
{
    ui->setupUi(this);
    qRegisterMetaType< LidarResultDisplay >("LidarResultDisplay");

    m_thread = new QThread;
    m_flashgoDriver = new FlashgoDriver;
    m_flashgoDriver->moveToThread(m_thread);
    connect(m_flashgoDriver, SIGNAL(sg_result_dis(LidarResultDisplay)), this, SLOT(sl_result_dis(LidarResultDisplay)));
    connect(m_flashgoDriver, SIGNAL(sg_uart_dis(bool)), this, SLOT(sl_uart_dis(bool)));
    connect(m_flashgoDriver, SIGNAL(sg_loop_end()), this, SLOT(sl_loop_end()));
    connect(m_thread, SIGNAL(finished()), m_thread, SLOT(deleteLater()));
    m_thread->start();

    //hide debug pushButtons
//    ui->pushButton_IntensityOFF->hide();
//    ui->pushButton_IntensityON->hide();
//    ui->pushButton_MoterEn->hide();
//    ui->pushButton_getHealth->hide();
//    ui->pushButton_getInfo->hide();
//    ui->pushButton_open->hide();
//    ui->pushButton_stopScan->hide();
}

DialogLidar::~DialogLidar()
{
    delete m_flashgoDriver;
    delete ui;
}


void DialogLidar::Ass_num_dev(int num, QString lidar_port, QString mcu_port)
{
    Lidar_numver = num;
    lidar_dev = lidar_port;
    mcu_dev = mcu_port;

    m_flashgoDriver->lidar_port = lidar_dev.toUtf8().constData();
    m_flashgoDriver->mcu_port = mcu_dev.toUtf8().constData();
    m_flashgoDriver->lidar_number = Lidar_numver;

    m_flashgoDriver->m_flashgo->lidar_num = Lidar_numver;

    ui->lcdNumber_ID->display(m_flashgoDriver->lidar_number);   //工位号
}

void DialogLidar::on_pushButton_open_clicked()
{
    m_flashgoDriver->lidar_port = lidar_dev.toUtf8().constData();
    m_flashgoDriver->mcu_port = mcu_dev.toUtf8().constData();
    m_flashgoDriver->driver_openUart();
}

void DialogLidar::on_pushButton_getInfo_clicked()
{
    m_flashgoDriver->driver_getDevInfo(lidar_dev.toUtf8().constData());
}

void DialogLidar::on_pushButton_getHealth_clicked()
{
    m_flashgoDriver->driver_getDeviceHealth();
}

void DialogLidar::on_pushButton_stopScan_clicked()
{
    m_flashgoDriver->driver_stopScan();
}

void DialogLidar::Delay_MSec(int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime() < _Timer)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

void DialogLidar::on_pushButton_MoterEn_clicked(bool checked)
{
    bool ret = false;
    ret = m_flashgoDriver->driver_MoterEn(!checked);
    qDebug() << "LD" << Lidar_numver << "driver_moterEn:" << ret;
}

void DialogLidar::on_pushButton_IntensityON_clicked()
{
    m_flashgoDriver->Lidar_Set_Mode(LIDAR_INTENSITY_ON);
}

void DialogLidar::on_pushButton_IntensityOFF_clicked()
{
    m_flashgoDriver->Lidar_Set_Mode(LIDAR_INTENSITY_OFF);
}

void DialogLidar::sl_loop_end()
{
    ui->pushButton_loopTest->setEnabled(true);
    ui->pushButton_loopStop->setText("暂停");
}

void DialogLidar::sl_uart_dis(bool connect_dis)
{
    if(connect_dis)
    {
        ui->lcdNumber_uart->setStyleSheet("background-color: green");
    }
    else
    {
        ui->lcdNumber_uart->setStyleSheet("background-color: red");
    }
}

void DialogLidar::sl_result_dis(LidarResultDisplay dis)
{
    ui->lcdNumber_Blind_Y->display(dis.blind_Y);
    ui->lcdNumber_Blind_N->display(dis.blind_test_times - dis.blind_Y);

    ui->lcdNumber_Intensity_Y->display(dis.intensity_Y);
    ui->lcdNumber_Intensity_N->display(dis.intensity_test_times - dis.intensity_Y);

    ui->lcdNumber_switch_Y->display(dis.switch_Y);
    ui->lcdNumber_switch_N->display(dis.intensity_test_times - dis.switch_Y);
}

//测试开始
void DialogLidar::on_pushButton_loopTest_clicked()
{
    m_flashgoDriver->loop = true;
    m_flashgoDriver->loopThreadInit();
    ui->pushButton_loopTest->setEnabled(false);
}

//测试暂停
void DialogLidar::on_pushButton_loopStop_clicked()
{
    if(m_flashgoDriver->loop_end == false)
    {
        ui->pushButton_loopStop->setText("暂停中");
        m_flashgoDriver->loop = false;
    }
}

//清零
void DialogLidar::on_pushButton_clicked()
{
    m_flashgoDriver->m_flashgo->resetPIDState();
    memset(&m_flashgoDriver->lidarResultDisplay, 0, sizeof(struct LidarResultDisplay));

    ui->lcdNumber_Blind_Y->display(0);
    ui->lcdNumber_Blind_N->display(0);

    ui->lcdNumber_Intensity_Y->display(0);
    ui->lcdNumber_Intensity_N->display(0);

    ui->lcdNumber_switch_Y->display(0);
    ui->lcdNumber_switch_N->display(0);

    ui->lcdNumber_uart->setStyleSheet("background-color: rgb(211, 215, 207)");
}
