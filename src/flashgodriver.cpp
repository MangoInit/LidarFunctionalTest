#include "include/flashgodriver.h"

FlashgoDriver::FlashgoDriver(QObject *parent) : QObject(parent)
{
    lidar_baudrate = 153600;
    mcu_baudrate = 115200;

    m_flashgo = new Flashgo;
    m_flashgo->lidar_num = lidar_number;

    if(!m_flashgo)
    {
        qDebug() << "LD" << lidar_number << "[EAI ERROR]: Create Driver fail, exit\n";
        return ;
    }
}

FlashgoDriver::~FlashgoDriver()
{
    qDebug() << "LD" << lidar_number << "[EAI ERROR]: Received exit signal";
    Stop();
    m_flashgo->disconnect();
    delete m_flashgo;
}

void FlashgoDriver::loopThreadInit()
{
//    _thread = std::thread(&FlashgoDriver::loopFun, this);
    _thread = std::make_shared<boost::thread>(&FlashgoDriver::loopFun, this);
//    _thread.detach();
}

void FlashgoDriver::loopFun()
{
    loop_end = false;
    while(loop == true)
    {
        test_mode = TEST_MODE_NONE;
        std::memset(&lidarResultPeriod, 0 , sizeof (LidarResultPeriod));

        std::cout << "------------------------------------------------------" << thread() << std::endl;
        std::cout << "Hello, World!\t" << std::this_thread::get_id() << std::endl;

        if(false == Lidar_Set_Mode(LIDAR_MODE::LIDAR_CONNECT))
        {
            loop = false;
            Q_EMIT sg_uart_dis(false);
            break;
        }
        Q_EMIT sg_uart_dis(true);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        Lidar_Set_Mode(LIDAR_MODE::LIDAR_OPEN);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        //Get Health to check that if Lidar is connect to Driver
        bool lidar_connected = driver_getDeviceHealth();
        if(lidar_connected == false)
        {
            qDebug() << "LD" << lidar_number << "Lidar is not connect!!!";
            break;
        }

        //光强测试
        Lidar_Set_Mode(LIDAR_MODE::LIDAR_STOP_SCAN);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        Lidar_Set_Mode(LIDAR_MODE::LIDAR_INTENSITY_ON);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        test_mode = TEST_MODE_INTENSITY;
        std::this_thread::sleep_for(std::chrono::milliseconds(18000));

        //盲区测试
        Lidar_Set_Mode(LIDAR_MODE::LIDAR_STOP_SCAN);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        test_mode = TEST_MODE_BLIND_ZONE;
        Lidar_Set_Mode(LIDAR_MODE::LIDAR_INTENSITY_OFF);
        std::this_thread::sleep_for(std::chrono::milliseconds(15000));

        Lidar_Set_Mode(LIDAR_MODE::LIDAR_STOP_SCAN);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        Lidar_Set_Mode(LIDAR_MODE::LIDAR_CLOSE);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        qDebug() << "LD" << lidar_number << " Test Result BlindZone:\tAll:" << lidarResultPeriod.blind_times_period << "Pass:" << lidarResultPeriod.blind_Y_period;
        qDebug() << "LD" << lidar_number << " Test Result Intensity:\tAll:" << lidarResultPeriod.intensity_times_period << "Pass:" << lidarResultPeriod.intensity_Y_period;
        //fun result to display
        resultPeriodToResult();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    loop_end = true;
    Q_EMIT sg_loop_end();
    std::cout << "loop Test Finish" << std::endl;
}

//void *FlashgoDriver::loopFun(void *args)
//{
//    FlashgoDriver *pThis = static_cast<FlashgoDriver *>(args);

//    while(pThis->loop == true)
//    {
//        pThis->test_mode = TEST_MODE_NONE;
//        std::memset(&pThis->lidarResultPeriod, 0 , sizeof (LidarResultPeriod));

//        std::cout << "------------------------------------------------------" << pThis->thread();

//        std::cout << "Hello, World!\t" << std::this_thread::get_id() << std::endl;

//        if(false == pThis->Lidar_Set_Mode(LIDAR_MODE::LIDAR_CONNECT))
//        {
//            pThis->loop = false;
//            break;
//        }
//        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

//        pThis->Lidar_Set_Mode(LIDAR_MODE::LIDAR_OPEN);
//        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

//        pThis->Lidar_Set_Mode(LIDAR_MODE::LIDAR_STOP_SCAN);
//        pThis->test_mode = TEST_MODE_BLIND_ZONE;
//        pThis->Lidar_Set_Mode(LIDAR_MODE::LIDAR_INTENSITY_OFF);
//        std::this_thread::sleep_for(std::chrono::milliseconds(15000));

//        pThis->Lidar_Set_Mode(LIDAR_MODE::LIDAR_STOP_SCAN);
//        pThis->test_mode = TEST_MODE_INTENSITY;
//        pThis->Lidar_Set_Mode(LIDAR_MODE::LIDAR_INTENSITY_ON);
//        std::this_thread::sleep_for(std::chrono::milliseconds(15000));

//        pThis->Lidar_Set_Mode(LIDAR_MODE::LIDAR_STOP_SCAN);
//        std::this_thread::sleep_for(std::chrono::milliseconds(500));

//        pThis->Lidar_Set_Mode(LIDAR_MODE::LIDAR_CLOSE);
//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

//        qDebug() << " Test Result BlindZone:\tAll:" << pThis->lidarResultPeriod.blind_times_period << "Pass:" << pThis->lidarResultPeriod.blind_Y_period;
//        qDebug() << " Test Result Intensity:\tAll:" << pThis->lidarResultPeriod.intensity_times_period << "Pass:" << pThis->lidarResultPeriod.intensity_Y_period;
//        //fun result to display
//        pThis->resultPeriodToResult();
//        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//    }
//    std::cout << "loop Test Finish" << std::endl;
//}

void FlashgoDriver::resultPeriodToResult()
{
    lidarResultDisplay.blind_test_times++;
    lidarResultDisplay.intensity_test_times++;

    if(lidarResultPeriod.switch_period() == true)
        lidarResultDisplay.switch_Y++;

    if(lidarResultPeriod.blind_result() == true)
        lidarResultDisplay.blind_Y++;

    if(lidarResultPeriod.intensity_result() == true)
        lidarResultDisplay.intensity_Y++;

    Q_EMIT sg_result_dis(lidarResultDisplay);
}

bool FlashgoDriver::driver_openUart()
{
    qDebug() << "LD" << lidar_number << "driver_openUart Thread:" << this->thread();
    m_flashgo->isLidarOn = true;
    int result_1 = -1;
    result_1 = m_flashgo->lidar_connect(lidar_port.c_str(), (u_int32_t) lidar_baudrate);
    qDebug() << "LD" << lidar_number << "FlashgoDriver: Lidar connect result:" << result_1 << lidar_port.c_str();

    int result_2 = -1;
    result_2 = m_flashgo->mcu_connect(mcu_port.c_str(), (u_int32_t)mcu_baudrate);
    qDebug() << "LD" << lidar_number << "FlashgoDriver: MCU connect result:" << result_2 << mcu_port.c_str();

    if( (result_1 != -1) && (result_2 != -1))
    {
        return true;
    }
    else
        return false;
}

bool FlashgoDriver::driver_stopScan()
{
    Lidar_Set_Mode(LIDAR_STOP_SCAN);
}

bool FlashgoDriver::driver_MoterEn(bool en)
{
    int result = -1;
    result = m_flashgo->lidarPwrOn(en);
//    qDebug() << "LD" << lidar_number << "Moter Open result:" << result;
    if(result != 5)
    {
        return false;
    }
    return true;
}

void FlashgoDriver::Start()
{
    qDebug() << "LD" << lidar_number << "Starts...";
    boost::lock_guard<boost::mutex> lock(mutex_);
    manually_interrupt_ = false;
    thread_ptr_ = std::make_shared<boost::thread>(&FlashgoDriver::Run, this);
    thread_id = thread_ptr_->get_id();
    is_stoped_ = false;
    qDebug() << "LD" << lidar_number << "Starts Over";
}

void FlashgoDriver::Run()
{
    while(1 && (false == manually_interrupt_))
    {
        ProcessData();
        usleep(3000);
    }
    is_stoped_ = true;
}

void FlashgoDriver::ProcessData()
{
    node_info buff_nodes[node_counts_ *2];
    size_t count = _countof(buff_nodes);

    if(m_flashgo)
        op_result = m_flashgo->grabScanData(buff_nodes, count);

    publish_scan(buff_nodes, count, -180.0, 180.0);
}

void FlashgoDriver::publish_scan(node_info *node, size_t node_count, float angle_min, float angle_max)
{
    LaserScan laserScan;
    std::vector<float> nodes_array;
    std::vector<float> quality_array;
    nodes_array.assign(node_count, 0);
    quality_array.assign(node_count, 0);
    int current_index = 0;

    angle_diff = 360.0/node_count;
    for(u_int i=0; i<node_count; i++)
    {
        if(node[i].distance_q2 > 0)
        {
            float angle = wrap2pi(DEG2RAD(float(node[i].angle_q6_checkbit>>LIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) / 64.0f));
            angle = wrap2pi(2 * M_PI - angle);
            angle = RAD2DEG(wrap2pi(angle));
            current_index = round((angle - angle_min)/angle_diff);
            if (current_index < 0)
            {
                current_index = 0;
            }
            if (current_index >= (int)node_count)
            {
                current_index = node_count - 1;
            }

            nodes_array[current_index] = (float) (node[i].distance_q2>>LIDAR_RESP_MEASUREMENT_DISTANCE_SHIFT)/1000.0;
            quality_array[current_index] = (float) (node[i].sync_quality);
        }
    }

    laserScan.ranges.resize(node_count);
    laserScan.intensities.resize(node_count);

    for(size_t i=0; i<node_count; i++)
    {
        laserScan.ranges[i] = nodes_array[i];
        laserScan.intensities[i] = quality_array[i];
    }
    float radian_min = DEG2RAD(angle_min);
    float radian_max = DEG2RAD(angle_max);
    laserScan.angle_min = radian_min;
    laserScan.angle_max = radian_max;
    laserScan.angle_increment = (laserScan.angle_max - laserScan.angle_min) / (double) node_count;
    laserScan.range_min = 0.12;
    laserScan.range_max = 15.;

//    qDebug() << laserScan.angle_increment << laserScan.angle_max << laserScan.angle_min << laserScan.range_max << laserScan.range_min;
//    qDebug() << "ranges[" << node_count << "]" << laserScan.ranges;
//    qDebug() << "intensities[" << node_count << "]" << laserScan.intensities;

    if(test_mode == TEST_MODE_BLIND_ZONE)
        BlindZoneTest(&laserScan, node_count);
    else if(test_mode == TEST_MODE_INTENSITY)
        IntensityTest(&laserScan, node_count);
    else
        ;
}

//8.8cm from the wall
//BlindZone Test
void FlashgoDriver::BlindZoneTest(LaserScan *laserscan, int points)
{
    if(m_flashgo->lidar_scan_freq <= 114 && m_flashgo->lidar_scan_freq >= 107)
    {
        int i = 0;

        //a complete scan test
//        for(int t=0; t<points; t++)
//        {
//            qDebug() << "LD" << lidar_number << points << "-" << t << "range:" << laserscan->ranges[t] << "\tintensity:" << laserscan->intensities[t];
//        }

        for(int t=0; t<(points/6); t++)
        {
            if((0.120 >= laserscan->ranges[t]) && (0.120 >= laserscan->ranges[t+1]) && (0.120 >= laserscan->ranges[t+2]))
            {
                i++;
//                qDebug() << "LD" << lidar_number << points << t << laserscan->ranges[t];
            }
        }
        for(int t=(points*5/6); t<points; t++)
        {
            if((0.12 >= laserscan->ranges[t]) && (0.12 >= laserscan->ranges[t+1]) && (0.12 >= laserscan->ranges[t+2]))
            {
                i++;
//                qDebug() << "LD" << lidar_number << points << t << laserscan->ranges[t];
            }
        }
        i = i+4;
        qDebug() << "LD" << lidar_number << "All Points:" << points <<  "BlindZone Points:" << i;
        float rad = i*laserscan->angle_increment;
//        qDebug() << "LD" << lidar_number << "rad:" << rad;
        double deg = RAD2DEG((double)rad);
        std::cout << "LD" << lidar_number << "deg:" << deg << std::endl;
        lidarResultPeriod.blind_times_period++;
        if((102.0 >= deg) && (80.0 <= deg))                                                // angle to be determined    //2019-01-24近距离精度问题，暂时放宽2cm
        {
//            qDebug() << "LD" << lidar_number << "[LIDAR BLIND ZONE] Test Pass.";
            lidarResultPeriod.blind_Y_period++;
        }
        else
        {
//            qDebug() << "LD" << lidar_number << "[LIDAR BLIND ZONE] Test Fail!";
        }
    }
}

//above 50cm from the wall
//Intensity Test
void FlashgoDriver::IntensityTest(LaserScan *laserscan, int points)
{
    if(m_flashgo->lidar_scan_freq <= 57 && m_flashgo->lidar_scan_freq >= 54)
    {
        int i_pass = 0;
        int i_fail = 0;
        int t_min = points*170/360;
        int t_max = points*190/360;
        lidarResultPeriod.intensity_times_period++;
        for(int t=t_min; t<t_max; t++)
        {
            if((laserscan->ranges[t] > 0) && (laserscan->intensities[t] > 0))
            {
                double calcIntensity = 24.56*pow((double)laserscan->ranges[t], -0.8261)+4.751;
                if((double)laserscan->intensities[t] > calcIntensity)
                {
                    i_pass++;
                }
                else
                {
                    i_fail++;
                }

//                qDebug() << "LD" << lidar_number << points<< "-" << t \
//                        << "distance:" << laserscan->ranges[t] \
//                        << "\tintensity:" << laserscan->intensities[t] \
//                        << "\t" << laserscan->angle_increment \
//                        << "trueIntensity:" << calcIntensity;
            }
        }

//        qDebug() << "LD" << lidar_number << "[LIDAR INTENSITY]max min : " << t_max << t_min << "i_pass and i_fail:" << i_pass << i_fail;
        if(i_fail <= 3)
        {
            qDebug() << "LD" << lidar_number << "[LIDAR INTENSITY] Test Pass." << points;
            lidarResultPeriod.intensity_Y_period++;
        }
        else
        {
            qDebug() << "LD" << lidar_number << "[LIDAR INTENSITY] Test Fail.\tFail points:" << i_fail;
        }
    }
}

void FlashgoDriver::Stop()
{
    Interrupt();
    WaitForStop();
}

void FlashgoDriver::Interrupt()
{
    boost::lock_guard<boost::mutex> lock(mutex_);
    if (thread_ptr_ != nullptr && !is_stoped_)
    {
        std::stringstream sstrm;
        sstrm << "[thread " << thread_ptr_->get_id() << "] Stop Flashgo PollData ";
        qDebug() << "LD" << lidar_number << QString::fromStdString(sstrm.str());
        thread_ptr_->interrupt();
    }
}


void FlashgoDriver::WaitForStop()
{
    bool res;
    boost::lock_guard<boost::mutex> lock(mutex_);
    if (thread_ptr_ != nullptr && !is_stoped_)
    {
        manually_interrupt_ = true;
        res = thread_ptr_->timed_join(boost::posix_time::seconds(2));
        if(res)
        {
            qDebug() << "LD" << lidar_number << "WaitForStop sucess";
        }
        else
        {
            qDebug() << "LD" << lidar_number << "WaitForStop timeout";
        }
    }
}

bool FlashgoDriver::Lidar_Set_Mode(LIDAR_MODE lidar_mode)
{
    int ret = -1;
    u_int32_t period = LIDAR_MOTER_PWM_PERIOD;/*ns*/
    u_int32_t rate = 0;

    if(!m_flashgo)
    {
        return false;
    }

    switch (lidar_mode)
    {
    case LIDAR_CONNECT:
        if(false == driver_openUart())
            return false;
        break;

    case LIDAR_OPEN:
        driver_MoterEn(false);
        break;

    case LIDAR_CLOSE:
        driver_MoterEn(true);
        break;

    case LIDAR_START_SCAN:
//        driver_startScan();
        break;

    case LIDAR_STOP_SCAN:
        test_mode = TEST_MODE_NONE;
        Stop();
        m_flashgo->stop();
        break;

    case LIDAR_INTENSITY_OFF:
        test_mode = TEST_MODE_BLIND_ZONE;

        ret = m_flashgo->setToIntensityMode();
        qDebug() << "LD" << lidar_number << "setToIntendityMode intensity off return:" << ret;
        if(ret == LIDAR_INTENSITY_TRUN_OFF)
        {
            qDebug() << "LD" << lidar_number << "turn off setToIntensityMode successed.";
        }
        else if(ret == LIDAR_INTENSITY_TRUN_ON)
        {
            if(LIDAR_INTENSITY_TRUN_OFF == m_flashgo->setToIntensityMode())
                qDebug() << "LD" << lidar_number << "turn off setToIntensityMode successed.";
            else
                qDebug() << "LD" << lidar_number << "turn off setToIntensityMode failed!!!!!!";
        }
        else
        {
            qDebug() << "LD" << lidar_number << "TRUN OFF neither ON or OFF. ret:" << ret;
        }

        rate = LIDAR_MOTER_MAX_DUTY_RATE;
        ret = m_flashgo->lidarMoterEn(true, period, rate);
        qDebug() << "LD" << lidar_number << "init lidarMoterEn return: " << ret << "rate:" << rate;
        Stop();
        node_counts_ = LIDAR_NODE_COUNT_DEFAULT;
        m_flashgo->scan_round_points = node_counts_;
        ret = m_flashgo->startScan();
        if(ret != 0)
            qDebug() << "LD" << lidar_number << "turn off startScan. ret: " << ret;
        else
            qDebug() << "LD" << lidar_number << "turn off startScan success.";
        Start();
        break;

    case LIDAR_INTENSITY_ON:
        test_mode = TEST_MODE_INTENSITY;

        ret = m_flashgo->setToIntensityMode();
        qDebug() << "LD" << lidar_number << "setToIntendityMode intensity on return:" << ret;
        if(ret == LIDAR_INTENSITY_TRUN_ON)
        {
            qDebug() << "LD" << lidar_number << "turn on setToIntensityMode successed";
        }
        else if(ret == LIDAR_INTENSITY_TRUN_OFF)
        {
            if(LIDAR_INTENSITY_TRUN_ON == m_flashgo->setToIntensityMode())
                qDebug() << "LD" << lidar_number << "turn on setToIntensityMode successed";
            else
                qDebug() << "LD" << lidar_number << "turn on setToIntensityMode failed!!!!";
        }
        else
        {
            qDebug() << "LD" << lidar_number << "TRUN ON neither ON or OFF. ret:" << ret;
        }

        rate = LIDAR_MOTER_MIN_DUTY_RATE;
        ret = m_flashgo->lidarMoterEn(true, period, rate);
        qDebug() << "LD" << lidar_number << "lidarMoterEn return: " << ret << rate;
        Stop();
        node_counts_ = LIDAR_NODE_COUNT_DOUBLE;
        m_flashgo->scan_round_points = node_counts_;
        ret = m_flashgo->startScan();
        if(ret != 0)
            qDebug() << "LD" << lidar_number << "turn on startScan. ret: " << ret;
        else
            qDebug() << "LD" << lidar_number << "turn on startScan success.";

        Start();
        break;

    default:
        break;
    }
    return true;
}

bool FlashgoDriver::driver_getDevInfo(std::string port)
{
    if (!m_flashgo)
    {
        return false;
    }

    device_info devinfo;
    int i_getinfo = m_flashgo->getInfo(devinfo);
    if (i_getinfo != 0)
    {
        qDebug() << "LD" << lidar_number << "YDLIDAR get DeviceInfo Error\n";
        return false;
    }
    int _samp_rate=4;
    std::string model;
    float freq = 7.0f;
    switch(devinfo.model)
    {
        case 1:
            model="F4";
            _samp_rate=4;
            freq = 7.0;
            break;
        case 4:
            model="S4";
            _samp_rate=4;
            freq = 7.0;
            break;
        case 5:
            model="G4";
            _samp_rate=9;
            freq = 7.0;
            break;
        case 6:
            model="X4";
            _samp_rate=5;
            freq = 7.0;
            break;
        default:
            model = "Unknown";
    }

    uint16_t maxv = (uint16_t)(devinfo.firmware_version>>8);
    uint16_t midv = (uint16_t)(devinfo.firmware_version&0xff)/10;
    uint16_t minv = (uint16_t)(devinfo.firmware_version&0xff)%10;
    if(midv==0)
    {
        midv = minv;
        minv = 0;
    }

    qDebug() << "LD" << lidar_number << "[YDLIDAR INFO] COnnection established in" << port.c_str()
             << "\nFirmware version:" << maxv << "." << midv << "." << minv
             << "\nHardware version:" << (uint16_t)devinfo.hardware_version
             << "\nModel:" <<  model.c_str();

    printf("[YDLIDAR INFO] Connection established in %s:\n"
                   "Firmware version: %u.%u.%u\n"
                   "Hardware version: %u\n"
                   "Model: %s\n"
                   "Serial: ",
           port.c_str(),
           maxv,
           midv,
           minv,
           (uint16_t)devinfo.hardware_version,
           model.c_str());

    for (int i=0;i<16;i++)
    {
        printf("%01X",devinfo.serialnum[i]&0xff);
    }
    printf("\n");

    printf("[YDLIDAR INFO] Current Sampling Rate : %dK\n" , _samp_rate);
    printf("[YDLIDAR INFO] Current Scan Frequency : %fHz\n" , freq);
    qDebug() << "LD" << lidar_number << "[YDLIDAR INFO] Current Sampling Rate : " << _samp_rate << "K";
    qDebug() << "LD" << lidar_number << "[YDLIDAR INFO] Current Scan Frequency :" << freq << "Hz";
    return true;
}

bool FlashgoDriver::driver_getDeviceHealth()
{
    sleep(2);
     int op_result;
     device_health healthinfo;
     qDebug() << "LD" << lidar_number << "Get the health status";
     op_result = m_flashgo->getHealth(healthinfo);
     if (op_result == 0)
     {
         printf("[YDLIDAR INFO] YDLIDAR running correctly! The health status: %s\n", healthinfo.status==0?"well":"bad");
         qDebug() << "LD" << lidar_number << "[YDLIDAR INFO] YDLIDAR running correctly! The health status:" << (healthinfo.status==0?"well":"bad");

         if (healthinfo.status == 2)
         {
             qDebug() << "LD" << lidar_number << "Error, YDLIDAR internal error detected. Please reboot the device to retry.";
             return false;
         }
         else
             return true;
     }
     else
     {
         qDebug() << "LD" << lidar_number << "Error, cannot retrieve YDLIDAR health code: %x" << op_result;
         return false;
     }
}

