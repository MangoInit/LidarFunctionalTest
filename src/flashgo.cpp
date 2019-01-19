#include "include/flashgo.h"
#include "include/event.h"
#include "include/locker.h"

u_int32_t lidar_baudrate = 153600;
u_int32_t mcu_baudrate = 115200;


Flashgo::Flashgo()
{
    lidar_isConnected = false;
    isScanning = false;
    isThreadOn = false;
    isLidarOn = false;

    memset(_lidar_pid, 0, sizeof(lidar_pid_args_t)*2);
    /* 1000, 200, 0 */
    _lidar_pid[0].kp = 1000;
    _lidar_pid[0].ki = 100;
    _lidar_pid[0].kd = 0;

    _lidar_pid[1].kp = 1000;
    _lidar_pid[1].ki = 100;
    _lidar_pid[1].kd = 0;
    
    lidar_scan_freq = 0;        //频率
    lidar_points_per_round = 0;

    memset(&motorPidInstance[0], 0, 2*sizeof(arm_pid_instance_f32));

    lidar_serial_fd = -1;
    mcu_serial_fd = -1;

     memset(&package, 0, 4 * sizeof(node_package));
     package_Sample_Index = 0;
     IntervalSampleAngle = 0;
     IntervalSampleAngle_LastPackage = 0;
     FirstSampleAngle = 0;
     LastSampleAngle = 0;
     CheckSun = 0;
     CheckSunCal = 0;
     SampleNumlAndCTCal = 0;
     LastSampleAngleCal = 0;
     CheckSunResult = true;
     Valu8Tou16 = 0;
     lost_count = 0;
     num_per_round = 0;
}

Flashgo::~Flashgo()
{
    {
        ScopedLocker l(_scanning_lock);
        isScanning = false;
    }

    if (isThreadOn || threadId || pidTaskId)
    {
        if (threadId)
        {
            //pthread_join(threadId, NULL);
        }

        if (pidTaskId)
        {
            //pthread_join(pidTaskId, NULL);
        }
    }
}

int Flashgo::lidar_connect(const char *lidar_port_path, u_int32_t baudrate)
{

    lidar_baudrate = baudrate;
    if (lidar_isConnected)
    {
        close(lidar_serial_fd);
    }

    {
        ScopedLocker l(_lock);
        if (lidar_serial_fd != -1)
        {
            close(lidar_serial_fd);
            qDebug() << "LD" << lidar_num << "close ??????";
        }

        lidar_serial_fd = -1;

        lidar_serial_fd = open(lidar_port_path, O_RDWR | O_NOCTTY | O_NDELAY);
        if (lidar_serial_fd == -1)
        {
            return -1;
        }

        struct termios2 options, oldopt;

        if ((ioctl(lidar_serial_fd, TCGETS2, &oldopt)) < 0)
        {
            printf("[EAI ERROR]: error to get the termios2 , %s\n", strerror(errno));
            return -1;
        }
        bzero(&options, sizeof(struct termios2));

        options.c_cflag = BOTHER;
        options.c_cflag |= (CLOCAL | CREAD);
        options.c_cflag &= ~CSTOPB;
        options.c_cflag &= ~CSIZE;
        options.c_cflag &= ~PARENB;
        options.c_cflag |= CS8;
        options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
        options.c_iflag &= ~(IXON | IXOFF | IXANY);
        options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IGNBRK);
        options.c_oflag &= ~OPOST;
        options.c_ispeed = baudrate;
        options.c_ospeed = baudrate;

        if (ioctl(lidar_serial_fd, TCFLSH, TCIFLUSH) != 0)
        {
            fprintf(stderr, "TCIFLUSH FAILED !!!\n");
        }

        if ((ioctl(lidar_serial_fd, TCSETS2, &options)) < 0)
        {
            printf("[EAI ERROR]: error to s the termios2 , %s\n", strerror(errno));
            return -1;
        }

    }
    fprintf(stderr, "[EAI ERROR] connect sucessfully\n");
    lidar_isConnected = true;
    return lidar_serial_fd;
}

int Flashgo::mcu_connect(const char *mcu_port_path, u_int32_t baudrate)
{
    mcu_baudrate = baudrate;
    if (mcu_isConnected)
    {
        close(mcu_serial_fd);
    }

    {
        ScopedLocker l(_lock);
        if (mcu_serial_fd != -1)
        {
            close(mcu_serial_fd);
        }

        mcu_serial_fd = -1;

        mcu_serial_fd = open(mcu_port_path, O_RDWR | O_NOCTTY | O_NDELAY);
        if (mcu_serial_fd == -1)
        {
            return -1;
        }

        struct termios2 options, oldopt;

        if ((ioctl(mcu_serial_fd, TCGETS2, &oldopt)) < 0)
        {
            printf("[MCU ERROR]: error to get the termios2 , %s\n", strerror(errno));
            return -1;
        }
        bzero(&options, sizeof(struct termios2));

        options.c_cflag = BOTHER;
        options.c_cflag |= (CLOCAL | CREAD);
        options.c_cflag &= ~CSTOPB;
        options.c_cflag &= ~CSIZE;
        options.c_cflag &= ~PARENB;
        options.c_cflag |= CS8;
        options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
        options.c_iflag &= ~(IXON | IXOFF | IXANY);
        options.c_iflag &= ~(INLCR | IGNCR | ICRNL | IGNBRK);
        options.c_oflag &= ~OPOST;
        options.c_ispeed = baudrate;
        options.c_ospeed = baudrate;

        if (ioctl(mcu_serial_fd, TCFLSH, TCIFLUSH) != 0)
        {
            fprintf(stderr, "MCU TCIFLUSH FAILED !!!\n");
        }

        if ((ioctl(mcu_serial_fd, TCSETS2, &options)) < 0)
        {
            printf("[MCU ERROR]: error to s the termios2 , %s\n", strerror(errno));
            return -1;
        }

    }
    fprintf(stderr, "[MCU ERROR] connect sucessfully\n");
    mcu_isConnected = true;
    return mcu_serial_fd;
}

void Flashgo::disconnect()
{
    if (!lidar_isConnected)
    {
        return;
    }
    stop();
    if (lidar_serial_fd != -1)
    {
        int ret;
        ret = close(lidar_serial_fd);
        if (ret == 0)
        {
            lidar_serial_fd = -1;
        }
        else
        {
            THROW (IOException, errno);
        }
   }
    lidar_isConnected = false;
    lidar_serial_fd = -1;
}

void Flashgo::disableDataGrabbing()
{
    qDebug() << "LD" << lidar_num << "disable data grabbing begin";

    {
        ScopedLocker l(_scanning_lock);
        isScanning = false;
    }

    isScanning = false;
    if (isThreadOn)
    {
        if (threadId)
        {
            std::cout << "threadId : " << threadId << std::endl;
            threadId->detach();
        }
	
        if(pidTaskId)
        {
            std::cout << "pidTaskId : " << pidTaskId << std::endl;
            pidTaskId->detach();
        }

        isThreadOn = false;
    }

    qDebug() << "LD" << lidar_num << "disable data grabbing end";
}

int Flashgo::sendCommand(u_int8_t cmd, const void *payload, size_t payloadsize)
{
    u_int8_t pkt_header[10];
    cmd_packet *header = reinterpret_cast<cmd_packet * >(pkt_header);

    if (!lidar_isConnected)
    {
        return -2;
    }

    header->syncByte = LIDAR_CMD_SYNC_BYTE;
    header->cmd_flag = cmd;
    sendData(pkt_header, 2);

    return 0;
}

int Flashgo::sendData(const unsigned char *data, size_t size)
{
    if (!lidar_isConnected)
    {
        return 0;
    }

    if (data == NULL || size == 0)
    {
        return 0;
    }

    size_t tx_len = 0;
    required_tx_cnt = 0;
    do
    {
        int ans = write(lidar_serial_fd, data + tx_len, size - tx_len);
        if (ans == -1)
        {
            return tx_len;
        }
        tx_len += ans;
        required_tx_cnt = tx_len;
    } while (tx_len < size);

    return tx_len;
}

int Flashgo::mcu_sendData(const unsigned char *data, size_t size)
{
    if (!mcu_isConnected)
    {
        qDebug() << "LD" << lidar_num << "mcu_isConnected:" << mcu_isConnected;
        return 0;
    }

    if (data == NULL || size == 0)
    {
        qDebug() << "LD" << lidar_num << "mcu_sendData: " << *data << size;
        return 0;
    }

    size_t tx_len = 0;
    mcu_required_tx_cnt = 0;
    do
    {
        int ans = write(mcu_serial_fd, data + tx_len, size - tx_len);
        if (ans == -1)
        {
            return tx_len;
        }
        tx_len += ans;
        mcu_required_tx_cnt = tx_len;
    } while (tx_len < size);

    return tx_len;
}

int Flashgo::getData(unsigned char *data, size_t size)
{
    if (!lidar_isConnected)
    {
        return -1;
    }
    int ans = read(lidar_serial_fd, data, size);
    return ans;
}

u_int32_t Flashgo::getms()
{
    struct timespec currentTime;
    memset(&currentTime, 0, sizeof(currentTime));
    currentTime.tv_sec = currentTime.tv_nsec = 0;
    clock_gettime(CLOCK_MONOTONIC, &currentTime);
    u_int32_t tms = currentTime.tv_sec * 1000L + currentTime.tv_nsec / 1000000L;
    memset(&currentTime, 0, sizeof(currentTime));
    return tms;
}

int Flashgo::waitResponseHeader(lidar_ans_header *header, u_int32_t timeout)
{
    int recvPos = 0;
    u_int32_t startTs = getms();
    u_int8_t recvBuffer[sizeof(lidar_ans_header)];
    u_int8_t *headerBuffer = reinterpret_cast<u_int8_t *>(header);
    u_int32_t waitTime;

    while ((waitTime = getms() - startTs) <= timeout)
    {
        size_t remainSize = sizeof(lidar_ans_header) - recvPos;
        size_t recvSize;

        int ans = waitForData(remainSize, timeout - waitTime, &recvSize);
        if (ans == -2)
        {
            return -2;
        }
        else if (ans == -1)
        {
            return -1;
        }

        if (recvSize > remainSize)
        { recvSize = remainSize; }

        ans = getData(recvBuffer, recvSize);
        if (ans == -1)
        {
            return -2;
        }

        for (size_t pos = 0; pos < recvSize; ++pos)
        {
            u_int8_t currentByte = recvBuffer[pos];
            switch (recvPos)
            {
                case 0:
                    if (currentByte != LIDAR_ANS_SYNC_BYTE1)
                    {
                        continue;
                    }
                    break;
                case 1:
                    if (currentByte != LIDAR_ANS_SYNC_BYTE2)
                    {
                        recvPos = 0;
                        continue;
                    }
                    break;
            }
            headerBuffer[recvPos++] = currentByte;

            if (recvPos == sizeof(lidar_ans_header))
            {
                return 0;
            }
        }
    }
    return -1;
}

int Flashgo::waitForData(size_t data_count, int timeout, size_t *returned_size)
{
    size_t length = 0;
    if (returned_size == NULL)
    {
        returned_size = (size_t *) &length;
    }

    int max_fd;
    fd_set input_set;
    struct timeval timeout_val;
    int cnt = 0;

    FD_ZERO(&input_set);
    FD_SET(lidar_serial_fd, &input_set);
    max_fd = lidar_serial_fd + 1;

    timeout_val.tv_sec = timeout / 1000;
    timeout_val.tv_usec = (timeout % 1000) * 1000;

    if (lidar_isConnected)
    {
        if (ioctl(lidar_serial_fd, FIONREAD, returned_size) == -1)
        {
            THROW (IOException, errno);
            return -2;
        }
        if (*returned_size >= data_count)
        {
            return 0;
        }
    }

    while (lidar_isConnected)
    {
        cnt++;

        int n = select(max_fd, &input_set, NULL, NULL, &timeout_val);
        if (n < 0)
        {
            // Select was interrupted
            if (errno == EINTR)
            {
                return -1;
            }
            // Otherwise there was some error
            THROW (IOException, errno);
            return -2;
        }
        else if (n == 0)
        {
            return -1;
        }
        else
        {
            assert (FD_ISSET(lidar_serial_fd, &input_set));
            if (ioctl(lidar_serial_fd, FIONREAD, returned_size) == -1)
            {
                THROW (IOException, errno);
                return -2;
            }

            if (*returned_size >= data_count)
            {
                return 0;
            }
            else
            {
                int remain_timeout = timeout_val.tv_sec * 1000000 + timeout_val.tv_usec;
                int expect_remain_time = (data_count - *returned_size) * 1000000 * 8 / lidar_baudrate;
                if (remain_timeout > expect_remain_time)
                {
                    usleep(expect_remain_time);
                }
                else
                {
            /* timeout */
            qDebug() << "LD" << lidar_num << "wait for data timeout";
            break;
                }
            }
        }
    }

    return -2;
}


void Flashgo::dummyRead(void)
{
    unsigned char buf[256];
 
    if (!lidar_isConnected)
    {
        return;
    }
    (void)getData(buf, 256);
  
    return;
}

int Flashgo::getHealth(device_health &health, u_int32_t timeout)
{
    int ans;
    if (!lidar_isConnected)
    {
        return -2;
    }

    disableDataGrabbing();
    {
        ScopedLocker l(_lock);

        dummyRead();

        if ((ans = sendCommand(LIDAR_CMD_GET_DEVICE_HEALTH)) != 0)
        {
            return ans;
        }
        lidar_ans_header response_header;
        if ((ans = waitResponseHeader(&response_header, timeout)) != 0)
        {
            return ans;
        }

        if (response_header.type != LIDAR_ANS_TYPE_DEVHEALTH)
        {
            return -3;
        }

        if (response_header.size < sizeof(device_health))
        {
            return -3;
        }

        if (waitForData(response_header.size, timeout) != 0)
        {
            return -1;
        }

        getData(reinterpret_cast<u_int8_t *>(&health), sizeof(health));
    }
    return 0;
}

int Flashgo::getInfo(device_info &info, u_int32_t timeout)
{
    int ans;
    if (!lidar_isConnected)
    {
        return -2;
    }

    disableDataGrabbing();
    {
        ScopedLocker l(_lock);

        dummyRead();
        if ((ans = sendCommand(LIDAR_CMD_GET_DEVICE_INFO)) != 0)
        {
            qDebug() << "LD" << lidar_num << "sendCommand ans:" << ans;
            return ans;
        }
        lidar_ans_header response_header;

        if ((ans = waitResponseHeader(&response_header, timeout)) != 0)
        {
            qDebug() << "LD" << lidar_num << "qDebug here......waitResponseHeader return:" << ans;
            return ans;
        }

        if (response_header.type != LIDAR_ANS_TYPE_DEVINFO)
        {
            return -3;
        }

        if (response_header.size < sizeof(lidar_ans_header))
        {
            return -3;
        }

        if (waitForData(response_header.size, timeout) != 0)
        {
            return -1;
        }
        getData(reinterpret_cast<u_int8_t *>(&info), sizeof(info));
    }
    return 0;
}

int Flashgo::setToIntensityMode(u_int32_t timeout)
{
    int ans;

    if (!lidar_isConnected || (false == isLidarOn))
    {
        return -2;
    }

    stop();
    {
        ScopedLocker l(_lock);
        if ((ans = sendCommand(LIDAR_CMD_CHANGE_INTENSITY)) != 0)
        {
            return ans;
        }

        lidar_ans_header response_header;
        if ((ans = waitResponseHeader(&response_header, timeout)) != 0)
        {
            return ans;
        }

        if (response_header.type != LIDAR_ANS_TYPE_DEVINFO)
        {
            return -3;
        }

        if (response_header.size != 1)
        {
            return -3;
        }

        if (waitForData(response_header.size, timeout) != 0)
        {
            return -1;
        }

        uint8_t data[10];
        memset(&data[0], 0, 10);
        getData(data, 10);

        if (data[0] == 1)
        { return 1; }
    }

    return 0;
}

int Flashgo::startScan(bool force, u_int32_t timeout)
{
    int ans;

    qDebug() << "LD" << lidar_num << "start scanning...";
    if (!lidar_isConnected || (false == isLidarOn))
    {
        return -2;
    }
    if (isScanning)
    {
        qDebug() << "LD" << lidar_num << "startScan: isScanning = " << isScanning;
        return 0;
    }

    qDebug() << "LD" << lidar_num << "join the thread";

    stop();
    {
        ScopedLocker l(_lock);
        if ((ans = sendCommand(force ? LIDAR_CMD_FORCE_SCAN : LIDAR_CMD_SCAN)) != 0)
        {
            return ans;
        }
        lidar_ans_header response_header;
        if ((ans = waitResponseHeader(&response_header, timeout)) != 0)
        {
            return ans;
        }
        if (response_header.type != LIDAR_ANS_TYPE_MEASUREMENT)
        {
            return -3;
        }
        if (response_header.size < sizeof(node_info_origin))
        {
            return -3;
        }
        qDebug() << "LD" << lidar_num << "create scan thread";
        isScanning = true;
        ans = this->createThread();
        return ans;
    }
    return 0;
}

void Flashgo::_thread_t( )
{
//    qDebug() << "_thread_t: thread id" << pthread_self();
//    Flashgo *pThis = static_cast<Flashgo *>(args);
//    pThis->cacheScanData();
//    return NULL;
    cacheScanData();
}


void Flashgo::_task_t()
{
//    Flashgo *pThis = static_cast<Flashgo *>(args);
//    pThis->pidControlTask();
//    return NULL;
    pidControlTask();
}

int Flashgo::createThread()
{
//    qDebug() << "LD" << lidar_num << "createThread thread id: " << pthread_self();

    threadId = std::make_shared<boost::thread>(&Flashgo::_thread_t, this);
    pidTaskId = std::make_shared<boost::thread>(&Flashgo::_task_t, this);

//    if (pthread_create(&threadId, NULL, _thread_t, (void *) this) != 0)
//    {
//        isThreadOn = false;
//        return -2;
//    }

//    if (pthread_create(&pidTaskId, NULL, _task_t, (void *) this) != 0)
//    {
//        isThreadOn = false;
//        return -2;
//    }

    isThreadOn = true;
    return 0;
}

int Flashgo::stop()
{
    int ans;
    unsigned char local_buf[256];

    if (false == isLidarOn)
    {
        return -2;
    }

    disableDataGrabbing();
    {
        ScopedLocker l(_lock);
        ans = sendCommand(LIDAR_CMD_FORCE_STOP);
        qDebug() << "LD" << lidar_num << "Lidar stop" << ans;
        if (ans != 0)
        {
            return ans;
        }
    }
    
     /* dummy read */	
    (void)usleep(20000);
    (void)getData(local_buf, 256);

    return 0;
}

int Flashgo::pidControlTask()
{
    float error = 0.0;    
    float motor_pwm_width = 0.0;
    uint32_t rate = 0;

    for(int k = 0; k < 2; k++)
    {
        MotorPidInit((arm_pid_instance_f32 *)&motorPidInstance[0], 1000, 150, 0);   //360       normal      Off
        MotorPidInit((arm_pid_instance_f32 *)&motorPidInstance[1], 600, 100, 0);   //720       intensity   on
    }

    while(isScanning)
    {
        if(!lidar_scan_freq)
        {
            usleep(100000);
            continue;
        }

        //Try to use Points to Feedback
        error = float(LIDAR_SCAN_FREQ_GAIN*LIDAR_CURRENT_SCAN_RATE/scan_round_points) - lidar_scan_freq;

        /* 360 points */
        if(scan_round_points == LIDAR_NODE_COUNT_DEFAULT)
        {
            motor_pwm_width = arm_pid_f32(&motorPidInstance[0], error);
            motor_pwm_width = abs(motor_pwm_width);
            if(motor_pwm_width > LIDAR_MOTER_PWM_PERIOD)
            {
                rate = /*54540*/0;
//                rate = 100000;
            }
            else
            {
                rate = round(motor_pwm_width);
            }

            lidarMoterEn(true, LIDAR_MOTER_PWM_PERIOD, rate);
            usleep(100000);
        }
        /* 720 points */
        else 
        {
            motor_pwm_width = arm_pid_f32(&motorPidInstance[1], -error);
            motor_pwm_width = abs(motor_pwm_width);
            if(motor_pwm_width > LIDAR_MOTER_PWM_PERIOD)
            {
                rate = /*LIDAR_MOTER_PWM_PERIOD*/200000;
            }
            else
            {
                rate = round(motor_pwm_width);
            }

            lidarMoterEn(true, LIDAR_MOTER_PWM_PERIOD, rate);
            usleep(200000);
        }

        qDebug() << "LD" << lidar_num \
                 << "error:" << error \
                 << "motor_pwm_width:" << motor_pwm_width \
                 << "scan_round_points:" << scan_round_points \
                 << "rate:" << rate/1000 \
                 << "lidar_scan_freq:" << lidar_scan_freq;
    }

    return 0;
}

int Flashgo::cacheScanData()
{
    qDebug() << "LD" << lidar_num << "cacheScanData() : thread id" << pthread_self();
    node_info local_buf[128];
    size_t count = 128;
    node_info local_scan[MAX_SCAN_NODES];
    size_t scan_count = 0;
    int ans;
    memset(local_scan, 0, sizeof(local_scan));

    waitScanData(local_buf, count);
//    qDebug() << "LD" << lidar_num << "cacheScanData: local_buf:" << local_buf->angle_q6_checkbit;

    while (isScanning)
    {
        if ((ans = waitScanData(local_buf, count)) != 0)
        {
            if (ans != -1)
            {
                fprintf(stderr, "exit scanning thread. exit code:%d!!", ans);
                {
                    ScopedLocker l(_scanning_lock);
                    isScanning = false;
                }
                return -2;
            }
        }

        for (size_t pos = 0; pos < count; ++pos)
        {
            if (local_buf[pos].sync_flag & LIDAR_RESP_MEASUREMENT_SYNCBIT)
            {
                if ((local_scan[0].sync_flag & LIDAR_RESP_MEASUREMENT_SYNCBIT))
                {
                    _lock.lock();
                    memcpy(scan_node_buf, local_scan, scan_count * sizeof(node_info));
                    scan_node_count = scan_count;//
                    _dataEvt.set();
                    _lock.unlock();
                }
                scan_count = 0;
            }
            local_scan[scan_count++] = local_buf[pos];
            if (scan_count == _countof(local_scan))
            { scan_count -= 1; }
        }
    }
    {
        ScopedLocker l(_scanning_lock);
        isScanning = false;
    }
    return 0;
}

int Flashgo::waitPackage(node_info *node, u_int32_t timeout)
{
    int recvPos = 0;
    u_int32_t startTs = getms();
    u_int8_t recvBuffer[sizeof(node_package)];
    u_int32_t waitTime;

//    static node_package package;
//    static u_int16_t package_Sample_Index = 0;
//    static u_int16_t IntervalSampleAngle = 0;
//    static u_int16_t IntervalSampleAngle_LastPackage = 0;
//    static u_int16_t FirstSampleAngle = 0;
//    static u_int16_t LastSampleAngle = 0;
//    static u_int16_t CheckSun = 0;

//    static u_int16_t CheckSunCal = 0;
//    static u_int16_t SampleNumlAndCTCal = 0;
//    static u_int16_t LastSampleAngleCal = 0;
//    static bool CheckSunResult = true;
//    static u_int16_t Valu8Tou16 = 0;
    
    u_int8_t *packageBuffer = (u_int8_t *) &package.package_Head;
    u_int8_t package_Sample_Num = 0;
    //int k = 0;
//    static int lost_count = 0;

    int32_t AngleCorrectForDistance;
    int package_recvPos = 0;
    uint8_t package_type = 0;
    uint8_t scan_frequence = 0;
//    static uint16_t num_per_round = 0;

    if (package_Sample_Index == 0)
    {
        recvPos = 0;
        while ((waitTime = getms() - startTs) <= timeout)
        {
            size_t remainSize = PackagePaidBytes - recvPos;
            size_t recvSize;
            int ans = waitForData(remainSize, timeout - waitTime, &recvSize);
            if (ans == -2)
            {
                return -2;
            }
            else if (ans == -1)
            {
                return -1;
            }

            if (recvSize > remainSize)
            { recvSize = remainSize; }

            getData(recvBuffer, recvSize);

            for (size_t pos = 0; pos < recvSize; ++pos)
            {
                u_int8_t currentByte = recvBuffer[pos];
                switch (recvPos)
                {
                    case 0:
                        if (currentByte == (PH & 0xFF))
                        {

                        }
                        else
                        {
                            continue;
                        }
                        break;
                    case 1:
                        CheckSunCal = PH;
                        if (currentByte == (PH >> 8))
                        {

                        }
                        else
                        {
                            recvPos = 0;
                            continue;
                        }
                        break;
                    case 2:
                        SampleNumlAndCTCal = currentByte;
                        package_type = currentByte&0x01;
                        if ((package_type == CT_Normal) || (package_type == CT_RingStart))
                        {
                            scan_frequence = (currentByte&0xFE)>>1;
                            if(package_type == CT_RingStart)
                            {
                                lidar_points_per_round = num_per_round;
                                _pid_lock.lock();
                                lidar_scan_freq = scan_frequence;
                                _pid_lock.unlock();
                                num_per_round = 0;
                            }
                        }
                        else
                        {
                            recvPos = 0;
                            continue;
                        }
                        break;
                    case 3:
                        SampleNumlAndCTCal += (currentByte * 0x100);
                        package_Sample_Num = currentByte;
                        num_per_round += package_Sample_Num;
                        break;
                    case 4:
                        if (currentByte & LIDAR_RESP_MEASUREMENT_CHECKBIT)
                        {
                            FirstSampleAngle = currentByte;
                        }
                        else
                        {
                            recvPos = 0;
                            continue;
                        }
                        break;
                    case 5:
                        FirstSampleAngle += currentByte * 0x100;
                        CheckSunCal ^= FirstSampleAngle;
                        FirstSampleAngle = FirstSampleAngle >> 1;
                        break;
                    case 6:
                        if (currentByte & LIDAR_RESP_MEASUREMENT_CHECKBIT)
                        {
                            LastSampleAngle = currentByte;
                        }
                        else
                        {
                            recvPos = 0;
                            continue;
                        }
                        break;
                    case 7:
                        LastSampleAngle = currentByte * 0x100 + LastSampleAngle;
                        LastSampleAngleCal = LastSampleAngle;
                        LastSampleAngle = LastSampleAngle >> 1;
                        if (package_Sample_Num == 1)
                        {
                            IntervalSampleAngle = 0;
                        }
                        else
                        {
                            if (LastSampleAngle < FirstSampleAngle)
                            {
                                if ((FirstSampleAngle > 270 * 64) && (LastSampleAngle < 90 * 64))
                                {
                                    IntervalSampleAngle =
                                            (360 * 64 + LastSampleAngle - FirstSampleAngle) / (package_Sample_Num - 1);
                                    IntervalSampleAngle_LastPackage = IntervalSampleAngle;
                                }
                                else
                                {
                                    IntervalSampleAngle = IntervalSampleAngle_LastPackage;
                                }
                            }
                            else
                            {
                                IntervalSampleAngle = (LastSampleAngle - FirstSampleAngle) / (package_Sample_Num - 1);
                                IntervalSampleAngle_LastPackage = IntervalSampleAngle;
                            }
                        }
                        break;
                    case 8:
                        CheckSun = currentByte;
                        break;
                    case 9:
                        CheckSun += (currentByte * 0x100);
                        break;
                }
                packageBuffer[recvPos++] = currentByte;
            }

            if (recvPos == PackagePaidBytes)
            {
                package_recvPos = recvPos;
                break;
            }
        }

        if (PackagePaidBytes == recvPos)
        {
            startTs = getms();
            recvPos = 0;
            while ((waitTime = getms() - startTs) <= timeout)
            {
                size_t remainSize = package_Sample_Num * PackageSampleBytes - recvPos;
                size_t recvSize;
                int ans = waitForData(remainSize, timeout - waitTime, &recvSize);
                if (ans == -2)
                {
                    return -2;
                }
                else if (ans == -1)
                {
                    return -1;
                }

                if (recvSize > remainSize)
                { recvSize = remainSize; }

                getData(recvBuffer, recvSize);

                for (size_t pos = 0; pos < recvSize; ++pos)
                {
#if(Quality_Use)
                    if (recvPos % 3 == 2)
                    {
                        Valu8Tou16 += recvBuffer[pos] * 0x100;
                        CheckSunCal ^= Valu8Tou16;
                    }
                    else if (recvPos % 3 == 1)
                    {
                        Valu8Tou16 = recvBuffer[pos];

                    }
                    else
                    {
                        CheckSunCal ^= recvBuffer[pos];

                    }
#else
                    if(recvPos%2 == 1){
            Valu8Tou16 += recvBuffer[pos]*0x100;
            CheckSunCal ^= Valu8Tou16;
            }else{
            Valu8Tou16 = recvBuffer[pos];
            }
#endif
                    packageBuffer[package_recvPos + recvPos] = recvBuffer[pos];
                    recvPos++;
                }
                if (package_Sample_Num * PackageSampleBytes == recvPos)
                {
                    package_recvPos += recvPos;
                    break;
                }
            }
            if (package_Sample_Num * PackageSampleBytes != recvPos)
            {
                return -1;
            }
        }
        else
        {
            return -1;
        }
        CheckSunCal ^= SampleNumlAndCTCal;
        CheckSunCal ^= LastSampleAngleCal;

        if (CheckSunCal != CheckSun)
        {
            lost_count++;
//            printf("checksun is false!!!!CheckSunCal:0x%x, CheckSun:0x%x, lost count:%x\n", CheckSunCal, CheckSun, lost_count);
            qDebug() << "LD" << lidar_num << "checksun is false!!!CheckSunCal:" << CheckSunCal << "CheckSun:" << CheckSun << "lost count:" << lost_count;
            CheckSunResult = false;
        }
        else
        {
            CheckSunResult = true;
        }

    }

    if (package.package_CT == CT_Normal)
    {
        /*(*node).sync_quality = Node_Default_Quality + Node_NotSync;*/
        (*node).sync_flag = Node_NotSync;
    }
    else
    {
        /*(*node).sync_quality = Node_Default_Quality + Node_Sync;*/
        (*node).sync_flag = Node_Sync;
    }
    
    (*node).sync_quality = Node_Default_Quality;

    if (CheckSunResult == true)
    {
#if(Quality_Use)

        (*node).sync_quality = (uint8_t((package.packageSample[package_Sample_Index].PakageSampleDistance&0x03)<< (8-LIDAR_RESP_MEASUREMENT_DISTANCE_SHIFT)) |
                                (package.packageSample[package_Sample_Index].PakageSampleQuality >> LIDAR_RESP_MEASUREMENT_QUALITY_SHIFT));
        
        (*node).distance_q2 = package.packageSample[package_Sample_Index].PakageSampleDistance;
//        qDebug() << "-----" << (*node).distance_q2;
#else
        (*node).distance_q2 = package.packageSampleDistance[package_Sample_Index];
#endif

        if ((*node).distance_q2>>LIDAR_RESP_MEASUREMENT_DISTANCE_SHIFT != 0)
        {
            AngleCorrectForDistance = (int32_t) (
                    ((atan(((21.8 * (155.3 - ((*node).distance_q2>>LIDAR_RESP_MEASUREMENT_DISTANCE_SHIFT))) / 155.3) / ((*node).distance_q2>>LIDAR_RESP_MEASUREMENT_DISTANCE_SHIFT))) *
                     180.0 / 3.1415) * 64.0);
        }
        else
        {
            AngleCorrectForDistance = 0;
        }

        if ((FirstSampleAngle + IntervalSampleAngle * package_Sample_Index + AngleCorrectForDistance) < 0)
        {
            (*node).angle_q6_checkbit =
                    ((uint16_t)(FirstSampleAngle + IntervalSampleAngle * package_Sample_Index + AngleCorrectForDistance +
                      360 * 64) << 1) + LIDAR_RESP_MEASUREMENT_CHECKBIT;
        }
        else
        {
            if ((FirstSampleAngle + IntervalSampleAngle * package_Sample_Index + AngleCorrectForDistance) > 360 * 64)
            {
                (*node).angle_q6_checkbit =
                        ((uint16_t)(FirstSampleAngle + IntervalSampleAngle * package_Sample_Index + AngleCorrectForDistance -
                          360 * 64) << 1) + LIDAR_RESP_MEASUREMENT_CHECKBIT;
            }
            else
            {
                (*node).angle_q6_checkbit =
                        ((uint16_t)(FirstSampleAngle + IntervalSampleAngle * package_Sample_Index + AngleCorrectForDistance)
                                << 1) + LIDAR_RESP_MEASUREMENT_CHECKBIT;
//                qDebug() << "3-angle_q6_checkbit:" << (*node).angle_q6_checkbit;
            }
        }
    }
    else
    {
        (*node).sync_flag = Node_NotSync;
        (*node).sync_quality = Node_Default_Quality;
        (*node).angle_q6_checkbit = LIDAR_RESP_MEASUREMENT_CHECKBIT;
        (*node).distance_q2 = 0;
    }

    ////AddCurrentOdomInfomation
//    update_odom();
//    node->odom=odom_current_;

    package_Sample_Index++;
    if (package_Sample_Index >= package.nowPackageNum)
    {
        package_Sample_Index = 0;
    }
    return 0;
}

int Flashgo::waitScanData(node_info *nodebuffer, size_t &count, u_int32_t timeout)
{
    if (!lidar_isConnected)
    {
        count = 0;
        return -2;
    }

    size_t recvNodeCount = 0;
    u_int32_t startTs = getms();
    u_int32_t waitTime;
    int ans;
    while ((waitTime = getms() - startTs) <= timeout && recvNodeCount < count)
    {
        node_info node;
        if ((ans = waitPackage(&node, timeout - waitTime)) != 0)
        {
            return ans;
        }

        nodebuffer[recvNodeCount++] = node;

        if (recvNodeCount == count)
        {
            return 0;
        }
    }
    count = recvNodeCount;
    return -1;
}

int Flashgo::grabScanData(node_info *nodebuffer, size_t &count, u_int32_t timeout)
{
    switch (_dataEvt.wait(timeout))
    {
        case Event::EVENT_TIMEOUT:
            count = 0;
            return -2;
        case Event::EVENT_OK:
        {
            if (scan_node_count == 0)
            {
                return -2;
            }
            size_t size_to_copy = std::min<size_t>(count, scan_node_count);
            ScopedLocker l(_lock);
            memcpy(nodebuffer, scan_node_buf, size_to_copy * sizeof(node_info));
            count = size_to_copy;
            scan_node_count = 0;
        }
            return 0;
        default:
            count = 0;
            return -1;
    }
}

void Flashgo::simpleScanData(std::vector<scanDot> *scan_data, node_info *buffer, size_t count)
{
    scan_data->clear();
    for (int pos = 0; pos < (int) count; ++pos)
    {
        scanDot dot;
        if (!(buffer[pos].distance_q2>>LIDAR_RESP_MEASUREMENT_DISTANCE_SHIFT))
        { continue; }
        dot.quality = (buffer[pos].sync_quality);
        dot.angle = (buffer[pos].angle_q6_checkbit >> LIDAR_RESP_MEASUREMENT_ANGLE_SHIFT) / 64.0f;
        dot.dist = buffer[pos].distance_q2>>LIDAR_RESP_MEASUREMENT_DISTANCE_SHIFT;
        scan_data->push_back(dot);
    }
}

int Flashgo::reset(uint32_t timeout)
{
    UNUSED(timeout);
    int ans;
    if (!lidar_isConnected)
    {
        return -2;
    }

    ScopedLocker l(_lock);

    if ((ans = sendCommand(LIDAR_CMD_RESET)) != 0)
    {
        return ans;
    }

    return 0;
}

int Flashgo::lidarMoterEn(bool enable, u_int32_t period, u_int32_t rate)
{
    if(!enable)
    {
        return -1;
    }

    rate = rate*9600/200000;

    u_int8_t pkt_header[10];
    mcu_cmd_packet *header = reinterpret_cast<mcu_cmd_packet * >(pkt_header);
    header->syncByte = MCU_CMD_HEADER;
    header->cmd_flag = MCU_CMD_EN_PWM;
    header->freq_flag = 0x00;
    header->en_pwm1 = rate >> 8;
    header->en_pwm2 = rate & 0xFF;
//    qDebug() << "LD" << lidar_num << "pwd out:" << rate;

    int ret = mcu_sendData(pkt_header, 5);
    return ret;
}

int Flashgo::lidarPwrOn(bool enable)
{
    u_int8_t pkt_header[10];
    mcu_cmd_packet *header = reinterpret_cast<mcu_cmd_packet * >(pkt_header);
    header->syncByte = MCU_CMD_HEADER;
    if(enable)
    {
        header->cmd_flag = MCU_CMD_EN_OPEN;
    }
    else
    {
        header->cmd_flag = MCU_CMD_EN_CLOSE;
    }
    header->freq_flag = 0x00;
    header->en_pwm1 = 0x00;
    header->en_pwm2 = 0x00;
    int ret = mcu_sendData(pkt_header, 5);
//    qDebug() << "LD" << lidar_num << "lidarPwrOn ret = " << ret << pkt_header[0] << pkt_header[1] << pkt_header[2];
    return ret;
}

void Flashgo::undistorted(node_info *node)
{
}


int Flashgo::addIntensity(u_int32_t timeout, u_int8_t &coff)
{
    int ans;
    if (!lidar_isConnected || (false == isLidarOn))
    {
        return -2;
    }

    stop();
    {
        ScopedLocker l(_lock);
        if ((ans = sendCommand(LIDAR_CMD_ADD_INTENSITY)) != 0)
        {
            return ans;
        }

        lidar_ans_header response_header;
        if ((ans = waitResponseHeader(&response_header, timeout)) != 0)
        {
            return ans;
        }

        if (response_header.type != LIDAR_ANS_TYPE_DEVINFO)
        {
            return -3;
        }

        if (response_header.size != 1)
        {
            return -3;
        }

        if (waitForData(response_header.size, timeout) != 0)
        {
            return -1;
        }

        uint8_t data[10];
        memset(&data[0], 0, 10);
        getData(data, 10);

    if (data[0] > 0x9B)
        { return -2; }
        coff = data[0];
    }

    return 0;
}


int Flashgo::subIntensity(u_int32_t timeout, u_int8_t &coff)
{
    int ans;
    if (!lidar_isConnected || (false == isLidarOn))
    {
        return -2;
    }

    stop();
    {
        ScopedLocker l(_lock);
        if ((ans = sendCommand(LIDAR_CMD_SUB_INTENSITY)) != 0)
        {
            return ans;
        }

        lidar_ans_header response_header;
        if ((ans = waitResponseHeader(&response_header, timeout)) != 0)
        {
            return ans;
        }

        if (response_header.type != LIDAR_ANS_TYPE_DEVINFO)
        {
            return -3;
        }

        if (response_header.size != 1)
        {
            return -3;
        }

        if (waitForData(response_header.size, timeout) != 0)
        {
            return -1;
        }

        uint8_t data[10];
        memset(&data[0], 0, 10);
        getData(data, 10);

        if (data[0] > 0x9B)
        { return -2; }
    coff = data[0];
    }

    return 0;
}

int Flashgo::intensityCoffSave(u_int32_t timeout, u_int8_t &coff)
{
    int ans;
    if (!lidar_isConnected || (false == isLidarOn))
    {
        return -2;
    }

    stop();
    {
        ScopedLocker l(_lock);
        if ((ans = sendCommand(LIDAR_CMD_COFF_SAVE)) != 0)
        {
            return ans;
        }

        lidar_ans_header response_header;
        if ((ans = waitResponseHeader(&response_header, timeout)) != 0)
        {
            return ans;
        }

        if (response_header.type != LIDAR_ANS_TYPE_DEVINFO)
        {
            return -3;
        }

        if (response_header.size != 1)
        {
            return -3;
        }

        if (waitForData(response_header.size, timeout) != 0)
        {
            return -1;
        }

        uint8_t data[10];
        memset(&data[0], 0, 10);
        getData(data, 10);

        if (data[0] == 0xFF)
        {
        return -2;
        }

    coff = data[0];
    }

    return 0;
}

void Flashgo::MotorPidInit(arm_pid_instance_f32 *pid_instance, float Kp, float Ki, float Kd)
{
	pid_instance->Kp = Kp;
	pid_instance->Ki = Ki;
	pid_instance->Kd = Kd;
	arm_pid_init_f32(pid_instance, 0);
}

float Flashgo::arm_pid_f32(arm_pid_instance_f32 *S, float in)
{
    float out;

    /* y[n] = y[n-1] + A0 * x[n] + A1 * x[n-1] + A2 * x[n-2]  */
    out = (S->A0 * in) +
      (S->A1 * S->state[0]) + (S->A2 * S->state[1]) + (S->state[2]);

    /* Update state */
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;

    /* return to application */
    return (out);
}

void Flashgo::arm_pid_init_f32(arm_pid_instance_f32 *S, int32_t resetStateFlag)
{

    /* Derived coefficient A0 */
    S->A0 = S->Kp + S->Ki + S->Kd;

    /* Derived coefficient A1 */
    S->A1 = (-S->Kp) - ((float) 2.0 * S->Kd);

    /* Derived coefficient A2 */
    S->A2 = S->Kd;

    /* Check whether state needs reset or not */
    if(resetStateFlag)
    {
        /* Clear the state buffer.  The size will be always 3 samples */
        memset(S->state, 0, 3u * sizeof(float));
    }
}
