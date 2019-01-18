#ifndef UART_H
#define UART_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QThread>

#define LIDAR_CMD_SYNC_BYTE                 0xA5

#define LIDAR_CMD_RESTART		            0x40
#define LIDAR_CMD_STOP                      0x65
#define LIDAR_CMD_SCAN                      0x60
#define LIDAR_CMD_FORCE_SCAN                0x61
#define LIDAR_CMD_RESET                     0x80
#define LIDAR_CMD_FORCE_STOP                0x00
#define LIDAR_CMD_GET_EAI                   0x55
#define LIDAR_CMD_GET_DEVICE_INFO           0x90
#define LIDAR_CMD_GET_DEVICE_HEALTH         0x92
#define LIDAR_CMD_COFF_SAVE		            0x94
#define LIDAR_CMD_CHANGE_INTENSITY          0x95
#define LIDAR_CMD_ADD_INTENSITY             0x96
#define LIDAR_CMD_SUB_INTENSITY             0x97

extern bool isConnect;

class UART : public QObject
{
    Q_OBJECT
public:
    explicit UART(QObject *parent = nullptr);
    QSerialPort *m_serialport;
    int serial_fd;

signals:

public slots:
    void uart_disconnect(QSerialPort::SerialPortError error);

    bool uart_open();

    void uart_receive();

    void uart_write();

private:
};

#endif // UART_H
