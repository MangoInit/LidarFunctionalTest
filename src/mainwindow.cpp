#include "include/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("激光雷达来料抽检");

    qRegisterMetaType< LIDAR_MODE >("LIDAR_MODE");

    QString lidar_dev = "/dev/ttyUSB_Lidar0*_00";
    QString mcu_dev = "/dev/ttyUSB_Lidar0*_01";

    setCentralWidget(ui->gridWidget);

//    scrollArea = new QScrollArea();
//    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);   // 设置垂直滚动条一直可见
//    scrollArea->show();
//    scrollArea->setWidgetResizable(true);
//    scrollArea->setWidget(this);
//    gridLayout->addWidget(scrollArea);

    for(int i=1; i<45; i++)
    {
        m_dialogLidar[i] = new DialogLidar();

        //find serial port
        char c = '0';
        if(i>=10)
        {
            lidar_dev[17] = c + i/10;
            mcu_dev[17] = c + i/10;
        }
        lidar_dev[18] = c+i%10;
        mcu_dev[18] = c+i%10;

        if(m_dialogLidar[i] == nullptr)
        {
            qDebug() << "new dialogLidar" << i << "fail!";
            continue;
        }

        m_dialogLidar[i]->Ass_num_dev(i, lidar_dev, mcu_dev);

        int num_horizontal= 0, num_vertical = 0;
        num_horizontal = (i-1)/9;
        num_vertical = (i-1)%9;
        ui->gridLayout->addWidget(m_dialogLidar[i], num_horizontal, num_vertical);

//        connect(m_controlForm, SIGNAL(sg_driver_OpenChoseUART()), m_dialogLidar[i]->m_flashgoDriver, SLOT(driver_openUart()));
//        connect(m_controlForm, SIGNAL(sg_driver_MoterEn(bool)), m_dialogLidar[i]->m_flashgoDriver, SLOT(driver_MoterEn(bool)));
//        connect(m_controlForm, SIGNAL(sg_driver_Lidar_Set_Mode(LIDAR_MODE)), m_dialogLidar[i]->m_flashgoDriver, SLOT(Lidar_Set_Mode(LIDAR_MODE)));
//                m_dialogLidar[i]->m_flashgoDriver, &FlashgoDriver::loopFun);
    }
    m_controlForm = new ControlForm();
    ui->gridLayout->addWidget(m_controlForm, 4, 8);
    connect(m_controlForm, &ControlForm::sg_control_start, this, &MainWindow::sl_control_loopStart);
    connect(m_controlForm, &ControlForm::sg_control_stop, this, &MainWindow::sl_control_loopStop);
    connect(m_controlForm, &ControlForm::sg_control_reset, this, &MainWindow::sl_control_reset);
    m_controlForm->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
    {
        qDebug() << "wheel up";
    }
    else
    {
        qDebug() << "wheel down";
    }
}

void MainWindow::sl_control_loopStart(int nums)
{
    if(nums >44)
        return ;
    for(int i=0; i<nums; i++)
    {
        m_dialogLidar[i+1]->on_pushButton_loopTest_clicked();
    }
}

void MainWindow::sl_control_loopStop(int nums)
{
    if(nums > 44)
        return ;
    for(int i=0; i<nums; i++)
    {
        m_dialogLidar[i+1]->on_pushButton_loopStop_clicked();
    }
}

void MainWindow::sl_control_reset(int nums)
{
    if(nums > 44)
        return ;
    for(int i=0; i<nums; i++)
    {
        m_dialogLidar[i+1]->on_pushButton_clicked();
    }
}

void MainWindow::on_action_triggered()
{
    m_controlForm = new ControlForm();
    connect(m_controlForm, &ControlForm::sg_control_start, this, &MainWindow::sl_control_loopStart);
    connect(m_controlForm, &ControlForm::sg_control_stop, this, &MainWindow::sl_control_loopStop);
    connect(m_controlForm, &ControlForm::sg_control_reset, this, &MainWindow::sl_control_reset);
    m_controlForm->show();
}
