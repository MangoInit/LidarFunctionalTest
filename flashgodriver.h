#ifndef FLASHGODRIVER_H
#define FLASHGODRIVER_H

#include <QObject>
#include "flashgo.h"
#include <boost/thread.hpp>
#include <signal.h>
#include <strings.h>
#include <math_tools.h>
#include <iostream>
#include <thread>

#define LIDAR_INTENSITY_TRUN_ON 	0
#define LIDAR_INTENSITY_TRUN_OFF 	1
#define RAD2DEG(x) 			((x)*180./M_PI)
#define DEG2RAD(x) 			((x)*M_PI/180.)

enum LIDAR_MODE{
    LIDAR_CONNECT,
    LIDAR_OPEN,
    LIDAR_CLOSE,
    LIDAR_INTENSITY_ON,
    LIDAR_INTENSITY_OFF,
    LIDAR_START_SCAN,
    LIDAR_STOP_SCAN,
    LIDAR_DISCONNECT
};

enum TEST_MODE{
    TEST_MODE_NONE,
    TEST_MODE_BLIND_ZONE,
    TEST_MODE_INTENSITY
};

struct LaserScan
{
    float angle_min;
    float angle_max;
    float angle_increment;
    float range_min;
    float range_max;
    std::vector<float> ranges;
    std::vector<float> intensities;
};

struct LidarResultDisplay
{
    int blind_test_times = 0;
    int intensity_test_times = 0;

    int switch_Y = 0;

    int intensity_Y = 0;
    int blind_Y = 0;
};

class LidarResultPeriod
{
public:
    int blind_times_period = 0;
    int intensity_times_period = 0;

    int intensity_Y_period = 0;
    int blind_Y_period = 0;

    bool switch_period()
    {
        if((blind_times_period >= 20) && (intensity_times_period >= 20))
        {
            return true;
        }
        else
            return false;
    }

    bool blind_result(void)         //盲区测试，每个周期扫描至少20个Scan
    {
        if(blind_times_period >= 20)
        {
            double percent = (double)blind_Y_period/blind_times_period;
            qDebug() << "Blind Success Percent:" << percent;
            if(percent >= 0.65)
            {
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }

    bool intensity_result(void)     //光强测试，每个周期至少扫描20个Scan
    {
        if(intensity_times_period >= 20)
        {
            double percent = (double)intensity_Y_period/intensity_times_period;
            qDebug() << "Intensity Success Percent:" << percent ;
            if(percent >= 0.80)
            {
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
};

class FlashgoDriver : public QObject
{
    Q_OBJECT
public:
    explicit FlashgoDriver(QObject *parent = nullptr);
    ~FlashgoDriver();

    Flashgo *m_flashgo;
    std::string lidar_port;
    std::string mcu_port;
    int lidar_number;
    int test_mode;
    bool loop = false;
    bool loop_end = true;
    LidarResultPeriod lidarResultPeriod;
    LidarResultDisplay lidarResultDisplay;

//    std::thread _thread;
    std::shared_ptr<boost::thread> _thread;
    void loopThreadInit();
    void loopFun();
    void resultPeriodToResult();

signals:
    void sg_result_dis(LidarResultDisplay);
    void sg_uart_dis(bool);
    void sg_loop_end();

public slots:
    bool Lidar_Set_Mode(LIDAR_MODE lidar_mode);
    bool driver_openUart();
    bool driver_getDevInfo(std::string lidar_port);
    bool driver_getDeviceHealth();
    bool driver_stopScan();
    bool driver_MoterEn(bool en);

private:
    float angle_diff = 1.0;
    int op_result;
    int lidar_baudrate;
    int mcu_baudrate;

    int node_counts_ = LIDAR_NODE_COUNT_DEFAULT;
    boost::mutex mutex_;
    double angle_max, angle_min;
    std::shared_ptr<boost::thread> thread_ptr_;
    bool manually_interrupt_ = false;
    bool is_stoped_=false;
    boost::thread::id thread_id;

    void Start();
    void Run();
    void ProcessData();
    void publish_scan(node_info *info, size_t node_count, float angle_min, float angle_max);
    void BlindZoneTest(LaserScan *laserscan, int points);
    void IntensityTest(LaserScan *laserscan, int points);
    void Stop();
    void Interrupt();
    void WaitForStop();
};

#endif // FLASHGODRIVER_H
