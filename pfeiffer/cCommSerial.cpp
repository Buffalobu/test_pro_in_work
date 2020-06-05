#include "cCommSerial.h"
#include <QSerialPortInfo>
#include <qdebug.h>

cCommSerial::cCommSerial(QWidget *parent):QSerialPort(parent)
{
    connect(this, SIGNAL(readyRead()), SLOT(onReadyRead()));
    //connect(this, SIGNAL(bytesWritten(qint64)), SLOT(handleBytesWritten(qint64)));
    connect(this, SIGNAL(error(QSerialPort::SerialPortError)), SLOT(handleError(QSerialPort::SerialPortError)));
}

QString cCommSerial::findDevice(quint16 PID, quint16 VID)
{
    QString portName;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){
        if((info.vendorIdentifier()== VID)&& (info.productIdentifier()== PID)){
            portName= info.portName();
            qDebug() << "Name : " << info.portName();
            qDebug() << "Description : " << info.description();
            qDebug() << "Manufacturer: " << info.manufacturer();
            qDebug() << "Serial Number: " << info.serialNumber();
            qDebug() << "System Location: " << info.systemLocation();
            break;
        }
    }
    return portName;
}

bool cCommSerial::open(QSerialPort& pSerialPort, QString portName, qint32 baudRate)
{
    if(pSerialPort.isOpen())
        return true;
    pSerialPort.setPortName(portName);
    if (!pSerialPort.setBaudRate(baudRate))
        return false;
    if (!pSerialPort.setDataBits(QSerialPort::Data8))
        return false;
    if (!pSerialPort.setParity(QSerialPort::NoParity))
        return false;
    if (!pSerialPort.setStopBits(QSerialPort::OneStop))
        return false;
    if (!pSerialPort.setFlowControl(QSerialPort::NoFlowControl))
        return false;
    if (!pSerialPort.open(QIODevice::ReadWrite))
        return false;
    pSerialPort.readAll();
    return true;
}

qint64 cCommSerial::write(QSerialPort& pSerialPort,
        QByteArray& lpBuffer,
        qint32 nTimeOutMs)
{
    if(!pSerialPort.isOpen())
        return 0;
    qint64 nWritten = pSerialPort.write(lpBuffer);
    pSerialPort.flush();
    if(nWritten != lpBuffer.size()){
        if(!waitForBytesWritten(nTimeOutMs))
            return 0;
    }else
        waitForBytesWritten(nTimeOutMs);
    return nWritten;
}

QByteArray  cCommSerial::read(QSerialPort& pSerialPort,
        qint64 lengthR,
        qint32 nTimeOutMs)
{
    QByteArray readData;
    if(!pSerialPort.isOpen())
        return readData;
    if(pSerialPort.waitForReadyRead(nTimeOutMs))
        readData.append(pSerialPort.readAll());
    if(readData.size()!= lengthR)
        readData.clear();
    return readData;
}

bool cCommSerial::openDevice(quint16 PID, quint16 VID, qint32 baudRate, qint32 delayMS)
{
    if(!isOpen()){
        QString tempPort= findDevice(PID, VID);
        if(tempPort.isEmpty()){
            return false;
        }else{
            if(!open(*this, tempPort, baudRate)){
                close();
                //sleepMS(100);
                return false;
            }
            sleepMS(delayMS);//垃圾板卡配置时间太久，配置完成之前使用会出现问题
        }
    }
    mPID= PID;
    mVID= VID;
    mBaudRate= baudRate;
    mDelayMS= delayMS;
    return true;
}

QByteArray cCommSerial::writeForBack(QByteArray& pWriteBuff, int lengthRead)
{
    QByteArray tempReadBuff;
    if(pWriteBuff.isEmpty())
        return tempReadBuff;
    lock();
    if(!openDevice(mPID, mVID, mBaudRate, mDelayMS)){
        unlock();
        return tempReadBuff;
    }
    qint64 nWrite= write(*this, pWriteBuff);
    if(nWrite== pWriteBuff.size()){
        if(!lengthRead){
            sleepMS(100);
            tempReadBuff= read(*this, nWrite);
            if(tempReadBuff.size()!= nWrite){
                close();
                tempReadBuff.clear();
            }
        }else{
            sleepMS(100);
            tempReadBuff= read(*this, lengthRead);
            //tempReadBuff= readSpecific(*this, lengthRead);
            if(tempReadBuff.size()!= lengthRead){
                close();
                tempReadBuff.clear();
            }
        }
    }else{
        close();
    }
    unlock();
    return tempReadBuff; 
}

bool cCommSerial::ioControl(int dwIoControlCode, void *lpInBuffer, unsigned int nInBufferSize,
                                   void */*lpOutBuffer*/, unsigned int /*nOutBufferSize*/,
                                   unsigned int */*lpBytesReturned*/, unsigned int /*nTimeOutMs*/)
{
    Q_UNUSED(dwIoControlCode) Q_UNUSED(lpInBuffer) Q_UNUSED(nInBufferSize)
//    if(dwIoControlCode == SUART_CMD_WRITE_BAUDRATE){
//        if(isOpen()
//                && lpInBuffer != NULL
//                && nInBufferSize >= sizeof(int)){
//            int* pValue = (int*)lpInBuffer;
//            setBaudRate(*pValue);
//        }
//    }
    return false;
}

void cCommSerial::onReadyRead()
{
//    MSCommBusy.lock();
//    mySleep(200);
//    QByteArray arr = m_serialPort.readAll();
//    if(!arr.isEmpty()){
//        QString qs_data = QString::fromLocal8Bit(arr,arr.size());
//        onRead(qs_data);
//    }
//    MSCommBusy.unlock();
}

void cCommSerial::handleBytesWritten(qint64 /*nBytes*/)
{

}

void cCommSerial::handleError(QSerialPort::SerialPortError err)
{
    const char* szErr[] = {
            "NoError",
            "DeviceNotFoundError",
            "PermissionError",
            "OpenError",
            "ParityError",
            "FramingError",
            "BreakConditionError",
            "WriteError",
            "ReadError",
            "ResourceError",
            "UnsupportedOperationError",
            "UnknownError",
            "TimeoutError",
            "NotOpenError"
        };
    if(err != 0)
        qDebug()<<(tr("UART error: %1").arg(szErr[err]));
}
