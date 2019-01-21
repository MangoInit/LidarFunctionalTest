#ifndef FLASHGO_H
#define FLASHGO_H

#include <QDebug>

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sstream>
#include <semaphore.h>
#include <malloc.h>
#include <stdbool.h>
#include <vector>
#include <asm/ioctls.h>
#include <asm/termbits.h>
//#include <termios.h>//
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "event.h"
#include "locker.h"

#define UNUSED(x) (void)x

#define _countof(_Array) (int)(sizeof(_Array) / sizeof(_Array[0]))


#define THROW(exceptionClass, message) throw exceptionClass(__FILE__, \
__LINE__, (message) )

#define Quality_Use 1 

#define MCU_CMD_HEADER                      0xAA
#define MCU_CMD_EN_CLOSE                    0x20
#define MCU_CMD_EN_OPEN                     0x21
#define MCU_CMD_EN_PWM                      0x22

#define LIDAR_CMD_RESTART		            0x40
#define LIDAR_CMD_STOP                      0x65
#define LIDAR_CMD_SCAN                      0x60
#define LIDAR_CMD_FORCE_SCAN                0x61
#define LIDAR_CMD_RESET                     0x80
#define LIDAR_CMD_FORCE_STOP                0x00
//#define LIDAR_CMD_GET_EAI                   0x55
#define LIDAR_CMD_GET_DEVICE_INFO           0x90
#define LIDAR_CMD_GET_DEVICE_HEALTH         0x92
#define LIDAR_CMD_COFF_SAVE		            0x94
#define LIDAR_CMD_CHANGE_INTENSITY          0x95
#define LIDAR_CMD_ADD_INTENSITY             0x96
#define LIDAR_CMD_SUB_INTENSITY             0x97

#define LIDAR_ANS_TYPE_DEVINFO              0x4
#define LIDAR_ANS_TYPE_DEVHEALTH            0x6
#define LIDAR_CMD_SYNC_BYTE                 0xA5
#define LIDAR_CMDFLAG_HAS_PAYLOAD           0x80
#define LIDAR_ANS_SYNC_BYTE1                0xA5
#define LIDAR_ANS_SYNC_BYTE2                0x5A
#define LIDAR_ANS_TYPE_MEASUREMENT          0x81
#define LIDAR_RESP_MEASUREMENT_SYNCBIT        (0x1<<0)
#define LIDAR_RESP_MEASUREMENT_QUALITY_SHIFT  2
#define LIDAR_RESP_MEASUREMENT_CHECKBIT       (0x1<<0)
#define LIDAR_RESP_MEASUREMENT_ANGLE_SHIFT    1
#define LIDAR_CMD_RUN_POSITIVE             0x06
#define LIDAR_CMD_RUN_INVERSION            0x07
#define LIDAR_CMD_SET_AIMSPEED_ADDMIC      0x09
#define LIDAR_CMD_SET_AIMSPEED_DISMIC      0x0A
#define LIDAR_CMD_SET_AIMSPEED_ADD         0x0B
#define LIDAR_CMD_SET_AIMSPEED_DIS         0x0C
#define LIDAR_CMD_GET_AIMSPEED             0x0D

#define LIDAR_CMD_SET_SAMPLING_RATE        0xD0
#define LIDAR_CMD_GET_SAMPLING_RATE        0xD1
//#define PWM_DEVICE                         "/dev/extra-misc" //R16 pwm out
//#define PWM_DEVICE                          "/dev/ttyUSB_Lidar00_01"

#define LIDAR_RESP_MEASUREMENT_DISTANCE_SHIFT 2
#define LIDAR_CURRENT_SCAN_RATE		   4000
#define LIDAR_SCAN_FREQ_GAIN		   10	
#define LIDAR_NODE_COUNT_DEFAULT      	   360      //最低点数要求
#define LIDAR_NODE_COUNT_DOUBLE            720      //最高点数要求

//#define LIDAR_MOTER_PWM_PERIOD          200000
#define LIDAR_MOTER_PWM_PERIOD          200000
#define LIDAR_MOTER_MAX_DUTY_RATE       100000
//#define LIDAR_MOTER_MAX_DUTY_RATE       78000
//#define LIDAR_MOTER_MEDIUM_DUTY_RATE  100000  
#define LIDAR_MOTER_MEDIUM_DUTY_RATE    173000 /* 4000/571=7K */ 
#define LIDAR_MOTER_MIN_DUTY_RATE     200000
//#define LIDAR_MOTER_MIN_DUTY_RATE       185500

#define LIDAR_DRIVER_LOG_NAME           "pita_lidar_driver"
#define LIDAR_DRIVER_LOG_PATH            "/root/logs/pita_lidar_driver/"
#define LIDAR_DRIVER_LOG(...) pita::frame::Logging::Debug(LIDAR_DRIVER_LOG_NAME, pita::frame::log::severity_level::debug, __VA_ARGS__)

#define EXTRA_MISC_SET_PWM _IOW('e', 1, misc_args_t *)
#define EXTRA_MISC_GET_PWM _IOR('e', 2, misc_args_t *)
#define EXTRA_MISC_SET_PP_SW _IOW('e', 3, int)
#define EXTRA_MISC_GET_PP_SW _IOR('e', 4, int *)
#define EXTRA_MISC_SET_M_SW  _IOW('e', 5, int) 
#define EXTRA_MISC_GET_M_SW  _IOR('e', 6, int)
#define EXTRA_MISC_LIDAR_PWR_ON  _IOW('f', 3, int)


#define PackageSampleMaxLngth 0x100
typedef enum
{
  CT_Normal = 0,
  CT_RingStart  = 1,
  CT_Tail,
}CT;
#define Node_Default_Quality (10)
#define Node_Sync 1
#define Node_NotSync 2
#define PackagePaidBytes 10
#if(Quality_Use)
#define PackageSampleBytes 3
#else
#define PackageSampleBytes 2
#endif
#define PH 0x55AA
struct node_info_origin
{
        u_int8_t    sync_quality;
        u_int16_t   angle_q6_checkbit;
        u_int16_t   distance_q2;
}__attribute__((packed)) ;

struct node_info{
    u_int8_t    sync_flag;
    u_int8_t    sync_quality;
    u_int16_t   angle_q6_checkbit;
    u_int16_t   distance_q2;
} __attribute__((packed)) ;

#if(Quality_Use)
struct PackageNode
{
    u_int8_t PakageSampleQuality;
    u_int16_t PakageSampleDistance;
}__attribute__((packed));

struct node_package {
    u_int16_t  package_Head;
    u_int8_t   package_CT;
    u_int8_t   nowPackageNum;
    u_int16_t  packageFirstSampleAngle;
    u_int16_t  packageLastSampleAngle;
    u_int16_t  checkSum;
    PackageNode  packageSample[PackageSampleMaxLngth];
} __attribute__((packed)) ;

#else
struct node_package {
    u_int16_t  package_Head;
    u_int8_t   package_CT;
    u_int8_t   nowPackageNum;
    u_int16_t  packageFirstSampleAngle;
    u_int16_t  packageLastSampleAngle;
    u_int16_t  checkSum;
    u_int16_t  packageSampleDistance[PackageSampleMaxLngth];
} __attribute__((packed)) ;
#endif

struct device_info{
    u_int8_t   model;
    u_int16_t  firmware_version;
    u_int8_t   hardware_version;
    u_int8_t   serialnum[16];
} __attribute__((packed)) ;

 struct device_health {
    u_int8_t   status;
    u_int16_t  error_code;
} __attribute__((packed))  ;

struct sampling_rate {
	uint8_t rate;
} __attribute__((packed))  ;

struct scan_frequency {
	uint32_t frequency;
} __attribute__((packed))  ;

struct cmd_packet {
    u_int8_t syncByte;
    u_int8_t cmd_flag;
    u_int8_t size;
    u_int8_t data[0];
} __attribute__((packed)) ;

struct mcu_cmd_packet {
    u_int8_t syncByte;
    u_int8_t cmd_flag;
    u_int8_t freq_flag;
    u_int8_t en_pwm1;
    u_int8_t en_pwm2;
    u_int8_t size;
    u_int8_t data[0];
} __attribute__((packed)) ;

 struct lidar_ans_header {
    u_int8_t  syncByte1;
    u_int8_t  syncByte2;
    u_int32_t size:30;
    u_int32_t subType:2;
    u_int8_t  type;
} __attribute__((packed));

struct scanDot {
     u_int8_t   quality;
     float angle;
     float dist;
 };

typedef struct misc_args 
{
        int duty;
        int period;
        bool enable;
}misc_args_t;

typedef struct
{
    float A0;          /**< The derived gain, A0 = Kp + Ki + Kd . */
    float A1;          /**< The derived gain, A1 = -Kp - 2Kd. */
    float A2;          /**< The derived gain, A2 = Kd . */
    float state[3];    /**< The state array of length 3. */
    float Kp;          /**< The proportional gain. */
    float Ki;          /**< The integral gain. */
    float Kd;          /**< The derivative gain. */
} arm_pid_instance_f32;

typedef struct lidar_pid_args
{
    float kp;
    float ki;
    float kd;
} lidar_pid_args_t;

class Flashgo
{
public:
    Flashgo();
    ~Flashgo();

    int lidar_num;
    arm_pid_instance_f32 motorPidInstance[2];
    uint8_t lidar_scan_freq;
    uint16_t lidar_points_per_round;

    void undistorted(node_info*node);
    int lidar_connect(const char * lidar_port_path, u_int32_t baudrate);
    int mcu_connect(const char *mcu_port_path, u_int32_t baudrate);
    void disconnect();
    int getHealth(device_health & health, u_int32_t timeout = DEFAULT_TIMEOUT);
    int setToIntensityMode(u_int32_t timeout = DEFAULT_TIMEOUT);
    int getInfo(device_info & info, u_int32_t timeout = DEFAULT_TIMEOUT);
    int startScan(bool force = false, u_int32_t timeout = DEFAULT_TIMEOUT) ;
    int stop();
    int grabScanData(node_info * nodebuffer, size_t & count, u_int32_t timeout = DEFAULT_TIMEOUT) ;
    int createThread();
    u_int32_t getms();
    void simpleScanData(std::vector<scanDot> * scan_data , node_info *buffer, size_t count);
    int reset(uint32_t timeout = DEFAULT_TIMEOUT);
    int lidarMoterEn(bool enable, u_int32_t period, u_int32_t rate);
    int lidarPwrOn(bool enable); 

    int addIntensity(u_int32_t timeout, u_int8_t &coff);
    int subIntensity(u_int32_t timeout, u_int8_t &coff);
    int intensityCoffSave(u_int32_t timeout, u_int8_t &coff);

    void MotorPidInit(arm_pid_instance_f32 *pid_instance, float Kp, float Ki, float Kd, int32_t resetStateFlag);
    float arm_pid_f32(arm_pid_instance_f32 *S, float in);
    void arm_pid_init_f32(arm_pid_instance_f32 *S, int32_t resetStateFlag);
    void resetPIDState();
    int pidControlTask();
protected:
    int waitPackage(node_info * node, u_int32_t timeout = DEFAULT_TIMEOUT);
    int waitScanData(node_info * nodebuffer, size_t & count, u_int32_t timeout = DEFAULT_TIMEOUT);
    int cacheScanData();
    int sendCommand(u_int8_t cmd, const void * payload = NULL, size_t payloadsize = 0);
    int waitResponseHeader(lidar_ans_header * header, u_int32_t timeout = DEFAULT_TIMEOUT);
    int waitForData(size_t data_count, int timeout = -1, size_t * returned_size = NULL);
    int getData(unsigned char * data, size_t size);
    int sendData(const unsigned char * data, size_t size);
    int mcu_sendData(const unsigned char * data, size_t size);
    void  disableDataGrabbing();
     void _thread_t( );
     void _task_t( );
    void dummyRead(void); 

private:
    int lidar_serial_fd;
    int mcu_serial_fd;
//    pthread_t threadId;
//    pthread_t pidTaskId;
    std::shared_ptr<boost::thread> threadId;
    std::shared_ptr<boost::thread> pidTaskId;

    size_t required_tx_cnt;
    size_t required_rx_cnt;
    size_t mcu_required_tx_cnt;

    Locker     _scanning_lock;
    Event     _dataEvt;
    Locker    _lock;
    Locker    _pid_lock;
    int _sampling_rate;

    lidar_pid_args_t _lidar_pid[2];


     node_package package;
     u_int16_t package_Sample_Index;
     u_int16_t IntervalSampleAngle;
     u_int16_t IntervalSampleAngle_LastPackage;
     u_int16_t FirstSampleAngle;
     u_int16_t LastSampleAngle;
     u_int16_t CheckSun;
     u_int16_t CheckSunCal;
     u_int16_t SampleNumlAndCTCal;
     u_int16_t LastSampleAngleCal;
     bool CheckSunResult;
     u_int16_t Valu8Tou16;
     int lost_count;
     uint16_t num_per_round;

public:
    bool     lidar_isConnected;
    bool     mcu_isConnected;
    bool     isScanning;
    bool     isThreadOn;
    bool     isLidarOn;
    enum {
        DEFAULT_TIMEOUT = 2000, //2000 ms
        MAX_SCAN_NODES = 2048,
    };
    node_info      scan_node_buf[2048];
    size_t         scan_node_count;
    int 	   scan_round_points = LIDAR_NODE_COUNT_DOUBLE; 
};


class SerialException : public std::exception
{
  // Disable copy constructors
  SerialException& operator=(const SerialException&);
  std::string e_what_;
public:
  SerialException (const char *description) {
      std::stringstream ss;
      ss << "SerialException " << description << " failed.";
      e_what_ = ss.str();
  }
  SerialException (const SerialException& other) : e_what_(other.e_what_) {}
  virtual ~SerialException() throw() {}
  virtual const char* what () const throw () {
    return e_what_.c_str();
  }
};

class IOException : public std::exception
{
  // Disable copy constructors
  IOException& operator=(const IOException&);
  std::string file_;
  int line_;
  std::string e_what_;
  int errno_;
public:
  explicit IOException (std::string file, int line, int errnum)
    : file_(file), line_(line), errno_(errnum) {
      std::stringstream ss;
#if defined(_WIN32) && !defined(__MINGW32__)
      char error_str [1024];
      strerror_s(error_str, 1024, errnum);
#else
      char * error_str = strerror(errnum);
#endif
      ss << "IO Exception (" << errno_ << "): " << error_str;
      ss << ", file " << file_ << ", line " << line_ << ".";
      e_what_ = ss.str();
  }
  explicit IOException (std::string file, int line, const char * description)
    : file_(file), line_(line), errno_(0) {
      std::stringstream ss;
      ss << "IO Exception: " << description;
      ss << ", file " << file_ << ", line " << line_ << ".";
      e_what_ = ss.str();
  }
  virtual ~IOException() throw() {}
  IOException (const IOException& other) : line_(other.line_), e_what_(other.e_what_), errno_(other.errno_) {}

  int getErrorNumber () const { return errno_; }

  virtual const char* what () const throw () {
    return e_what_.c_str();
  }
};

class PortNotOpenedException : public std::exception
{
  // Disable copy constructors
  const PortNotOpenedException& operator=(PortNotOpenedException);
  std::string e_what_;
public:
  PortNotOpenedException (const char * description)  {
      std::stringstream ss;
      ss << "PortNotOpenedException " << description << " failed.";
      e_what_ = ss.str();
  }
  PortNotOpenedException (const PortNotOpenedException& other) : e_what_(other.e_what_) {}
  virtual ~PortNotOpenedException() throw() {}
  virtual const char* what () const throw () {
    return e_what_.c_str();
  }

};

#endif // FLASHGO_H
