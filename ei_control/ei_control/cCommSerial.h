#ifndef COMMSERIAL_H
#define COMMSERIAL_H
#include <QSerialPort>
#include <qdebug.h>
#include <QMutex>
#include <QElapsedTimer>
#include <QCoreApplication>
#include <QWidget>

//#define addLog(msg) qDebug()<<(msg)
//#define SUART_CMD_WRITE_BAUDRATE    1

class cCommSerial : public QSerialPort
{
    Q_OBJECT
public:
    explicit cCommSerial(QWidget *parent = nullptr);
    ~cCommSerial(){
        if(isOpen())
            close();
    }
//    QString findDevice(quint16 PID= 29987, quint16 VID= 6790);
//    bool open(QSerialPort& pSerialPort, QString portName, qint32 baudRate= QSerialPort::Baud9600);
    bool openDevice(quint16 PID= 29987, quint16 VID= 6790, qint32 baudRate= QSerialPort::Baud115200, qint32 delayMS=3000);
    QByteArray writeForBack(QByteArray& pWriteBuff);
    qint64 write(QSerialPort& pSerialPort,
            QByteArray& lpBuffer,
            qint32 nTimeOutMs= 500);
    QByteArray read(QSerialPort& pSerialPort,
            qint64 lengthR,
            qint32 nTimeOutMs= 500);
    bool ioControl(
            int dwIoControlCode,
            void* lpInBuffer = nullptr,
            unsigned int nInBufferSize = 0,
            void* lpOutBuffer = nullptr,
            unsigned int nOutBufferSize = 0,
            unsigned int* lpBytesReturned = nullptr,
            unsigned int nTimeOutMs = ~0
            );
    void sleepMS(int time){
        QElapsedTimer t;
        t.start();
        while(t.elapsed()<time)
            QCoreApplication::processEvents();
    }
    void lock(){
        return mMutex.lock();
    }
    void unlock(){
        return mMutex.unlock();
    }

private:
    QMutex mMutex;
    quint16 mPID= 29987,
        mVID= 6790;
    qint32 mBaudRate= QSerialPort::Baud115200,
        mDelayMS=3000;
    QString findDevice(quint16 PID= 29987, quint16 VID= 6790);
    bool open(QSerialPort& pSerialPort, QString portName, qint32 baudRate= QSerialPort::Baud9600);

public slots:
    void onReadyRead();
    void handleBytesWritten(qint64 nBytes);
    void handleError(QSerialPort::SerialPortError err);
};

#endif // COMMSERIAL_H
