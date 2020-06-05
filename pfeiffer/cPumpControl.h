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

    static QByteArray pumpOnCMD(){
        return SynCommand(2, 10, 111111).toLatin1();
    }

    static QByteArray createPumpOnCMD(){
//        QByteArray tmpCMD= pumpOnCMD();
//        return ParamCCS::uartCMDData(tmpCMD);
        return QByteArray();
    }

    static QByteArray pumpOffCMD(){
        return SynCommand(2, 10, 0).toLatin1();
    }

    static QByteArray createPumpOffCMD(){
//        QByteArray tmpCMD= pumpOffCMD();
//        return ParamCCS::uartCMDData(tmpCMD);
        return QByteArray();
    }

    static QByteArray nominalspdCMD(){
        return SynCommand(2, 399, 0).toLatin1();
    }

    static QByteArray pumpDriveCMD(){
        return SynCommand(2, 310, 0).toLatin1();
    }

    static QByteArray createPumpDriveCMD(){
//        QByteArray tmpCMD= pumpDriveCMD();
//        return ParamCCS::uartCMDData(tmpCMD);
        return QByteArray();
    }

    static QByteArray pumpSpeedCMD(){
        return SynCommand(2, 309, 0).toLatin1();
    }

    static QByteArray createPumpSpeedCMD(){
//        QByteArray tmpCMD= pumpSpeedCMD();
//        return ParamCCS::uartCMDData(tmpCMD);
        return QByteArray();
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
