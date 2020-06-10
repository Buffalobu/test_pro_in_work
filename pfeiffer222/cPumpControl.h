#ifndef cPumpControl_H
#define cPumpControl_H

#include <QByteArray>
#include <QString>
#define _PUMP_READ_SIZE 20
class cPumpControl
{
public:
    explicit cPumpControl(){}
    ~cPumpControl(){}

    struct _STATE_REQUEST_CCS{
        double adcValue[4]={0,0,0,0};
    };

    struct _STATE_REQUEST:_STATE_REQUEST_CCS{
        int rotatinSpeed=0;
        double driveCurrent=0;
    };

    static QByteArray pumpOnCMD(int paddr){
        return SynCommand(paddr, 10, 111111).toLatin1();
    }

    static QByteArray createPumpOnCMD(){
//        QByteArray tmpCMD= pumpOnCMD();
//        return ParamCCS::uartCMDData(tmpCMD);
        return QByteArray();
    }

    static QByteArray pumpOffCMD(int paddr){
        return SynCommand(paddr, 10, 0).toLatin1();
    }

    static QByteArray createPumpOffCMD(){
//        QByteArray tmpCMD= pumpOffCMD();
//        return ParamCCS::uartCMDData(tmpCMD);
        return QByteArray();
    }

    static QByteArray nominalspdCMD(int paddr){
        return SynCommand(paddr, 399, 0).toLatin1();
    }

    static QByteArray pumpDriveCMD(int paddr){
        return SynCommand(paddr, 310, 0).toLatin1();
    }

    static QByteArray createPumpDriveCMD(){
//        QByteArray tmpCMD= pumpDriveCMD();
//        return ParamCCS::uartCMDData(tmpCMD);
        return QByteArray();
    }

    static QByteArray pumpSpeedCMD(int paddr){
        return SynCommand(paddr, 309, 0).toLatin1();
    }

    static QByteArray createPumpSpeedCMD(){
//        QByteArray tmpCMD= pumpSpeedCMD();
//        return ParamCCS::uartCMDData(tmpCMD);
        return QByteArray();
    }

    static QByteArray pumpSpeedControlEnableCMD(int paddr){
        return SynCommand(paddr, 26, 111111).toLatin1();//注意要6个1，一个1不行！
    }

    static QByteArray pumpSpeedValueCMD(int paddr, QString val){
        return SynCommand(paddr, 707, val).toLatin1();//传入的val也要六位！
    }

    static double getDrive(const QByteArray& tmpR);
    static bool getDrive(const QByteArray& tmpR, _STATE_REQUEST& pSTATE_REQUEST);

    static qint32 getSpeed(const QByteArray& tmpR);
    static bool getRotatinSpeed(const QByteArray& tmpR, _STATE_REQUEST& pSTATE_REQUEST);

    static qint32 getnominalspd(const QByteArray& tmpR);
private:
    static QString CHkSTR(QString sString);
    static QString SynCommand(int paddr,int PcommID, int Pdata);
    static QString SynCommand(int paddr,int PcommID, QString Pdata);
//    static QByteArray uartCMDData(QByteArray& baReq_s_comm);
//    static uint32_t checkSum(uint32_t* data, size_t size);
};

#endif // cPumpControl_H
