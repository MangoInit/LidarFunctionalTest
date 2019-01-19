#include "include/uart.h"

bool isConnect;

UART::UART(QObject *parent) : QObject(parent)
{
    m_serialport = new QSerialPort;

    isConnect = false;
    qDebug() << "new serialPort\t" << QThread::currentThread();
    qRegisterMetaType< QSerialPort::SerialPortError >("QSerialPort::SerialPortError");
}

void UART::uart_disconnect(QSerialPort::SerialPortError error)
{
    qDebug() << m_serialport << " is disconnect\t" << error << QThread::currentThread();
    isConnect = false;
    m_serialport->close();
}

bool UART::uart_open()
{
    foreach (const QSerialPortInfo info, QSerialPortInfo::availablePorts())
    {
        if(info.portName().at(3) == QString("U"))
        {
            if(info.isBusy() == false)
            {
                m_serialport->setPort(info);
                qDebug() << info.portName() << "is open\t" << QThread::currentThread();
                break;
            }
       }
    }

    if(m_serialport->open(QIODevice::ReadWrite))
    {
        m_serialport->setBaudRate(153600);                              //Lidar VaudRate
        m_serialport->setParity(QSerialPort::NoParity);
        m_serialport->setDataBits(QSerialPort::Data8);
        m_serialport->setStopBits(QSerialPort::OneStop);
        m_serialport->setFlowControl(QSerialPort::NoFlowControl);

        connect(m_serialport, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(uart_disconnect(QSerialPort::SerialPortError)));
        connect(m_serialport, SIGNAL(readyRead()), this, SLOT(uart_receive()));
        qDebug() << "m_serialport handle:"  << m_serialport->handle();

        isConnect = true;
        serial_fd = m_serialport->handle();
        qDebug() << "isConnect:" << isConnect;
        return true;
    }
    else
    {
        qDebug() << "m_serialport open fail!";
        return false;
    }
}

void UART::uart_receive()
{
//    qDebug() << "uart is ready for receive";
//    qDebug() << m_serialport->readAll().toHex();
//    m_serialport->readData()
}

void UART::uart_write()
{
    if(isConnect)
    {
        QByteArray b;
        uint8_t cmd[2];
        cmd[0] = LIDAR_CMD_SYNC_BYTE;
        cmd[1] = LIDAR_CMD_SCAN;
        b.append(cmd[0]);
        b.append(cmd[1]);
        int len = sizeof (cmd);
        qDebug() << "cmd:" << b.toHex() << "len:" << len;
        m_serialport->write(b, len);
    }
}

