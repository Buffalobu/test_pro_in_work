//#include "cPumpControl.h"
//#include <ui/smainwindow.h>
//#include <sobject.h>
//#include <sproject.h>
#include "cPumpControl.h"
#include <QDebug>
#include <QTimerEvent>

QString cmbCommands[]={ "001 | heating"
                        ,"002 | standby"
                        ,"004 | rutimectrl"
                        ,"009 | errorackn"
                        ,"010 | pumpgstatn"
                        ,"012 | enablevent"
                        ,"013 | brake"
                        ,"017 | cfgspdswpt"
                        ,"019 | cfg do2"
                        ,"023 | motorpump"
                        ,"024 | cfg do1"
                        ,"025 | dpmode bkp"
                        ,"026 | spdsetmode"
                        ,"027 | gasmode"
                        ,"030 | ventmode"
                        ,"035 | cfg acc a1"
                        ,"036 | cfg acc b1"
                        ,"037 | cfg acc a2"
                        ,"038 | cfg acc b2"
                        ,"045 | cfg rel r1"
                        ,"046 | cfg rel r2"
                        ,"047 | cfg rel r3"
                        ,"050 | sealing gas"
                        ,"055 | cfg ao1"
                        ,"057 | cfg al1"
                        ,"060 | ctrlvialnt"
                        ,"061 | intseilckd"
                        ,"062 | cfg di1"
                        ,"063 | cfg di2"
                        ,"064 | cfg di3"
                        ,"300 | remoteprio"
                        ,"301 | opfluiddef"
                        ,"302 | spdswptatt"
                        ,"303 | error code"
                        ,"304 | ovtempelec"
                        ,"305 | ovtemppump"
                        ,"306 | setspdatt"
                        ,"307 | pumpaccel"
                        ,"308 | setrotspd"
                        ,"309 | actualspd"
                        ,"310 | drvcurrent"
                        ,"311 | ophrspump"
                        ,"312 | fw version"
                        ,"313 | drvvoltage"
                        ,"314 | ophrselec"
                        ,"315 | nominal spd"
                        ,"316 | drvpower"
                        ,"319 | pumpcylces"
                        ,"324 | temppwrstg"
                        ,"326 | tempelec"
                        ,"330 | temppmpbot"
                        ,"336 | acceldecel"
                        ,"342 | tempbearng"
                        ,"346 | tempmotor"
                        ,"349 | elecname"
                        ,"354 | hw version"
                        ,"360 | errhist1"
                        ,"361 | errhist2"
                        ,"362 | errhist3"
                        ,"363 | errhist4"
                        ,"364 | errhist5"
                        ,"365 | errhist6"
                        ,"366 | errhist7"
                        ,"367 | errhist8"
                        ,"368 | errhist9"
                        ,"369 | errhist10"
                        ,"384 | temprotor"
                        ,"397 | setrotspd"
                        ,"398 | actualspd"
                        ,"399 | nominalspd"
                        ,"700 | rutimesval"
                        ,"701 | spdswpt1"
                        ,"707 | spdsval"
                        ,"708 | pwrsval"
                        ,"710 | swoff bkp"
                        ,"711 | swon bkp"
                        ,"717 | stdbysval"
                        ,"719 | spdswpt2"
                        ,"720 | ventspd"
                        ,"721 | venttime"
                        ,"777 | nomspdconf"
                        ,"797 | rs485 adr"};

QString cPumpControl::CHkSTR(QString sString)
{
    quint32 chknum=0;
    QByteArray tmpStr=sString.toUtf8();

    for(qint32 i=0;i< tmpStr.size();i++)
        chknum = chknum + static_cast<quint32>(tmpStr[i]);
    chknum %= 256;
    QString CHkSTR;
    CHkSTR.sprintf("%03d",chknum);
    return CHkSTR;
}

QString cPumpControl::SynCommand(int paddr,int PcommID, int Pdata)
{
    QString sAction, sdatalen, tmpstr;
    if(PcommID >= 300 && PcommID <= 399){
        sAction = "00";
        sdatalen = "02=?";

        tmpstr.sprintf("%03d", paddr);
        tmpstr = tmpstr.right(3) + sAction;
        QString tmpstr2;
        tmpstr2.sprintf("%03d", PcommID);
        tmpstr2 = tmpstr2.right(3) + sdatalen;
        tmpstr += tmpstr2;

        return tmpstr + CHkSTR(tmpstr) + '\r';
    }else{
        QString sdata;
        sAction = "10";
        sdatalen = "06";
        if ((PcommID != 23 && PcommID != 50 && PcommID != 61 && (PcommID >= 17 && PcommID <= 100))
            || PcommID == 708 || PcommID == 720 || PcommID == 797)
            sdatalen = "03";
        if(PcommID == 26)
            sdatalen = "06";  //控制转速模式为6位
        if(sdatalen == "06")
            sdata.sprintf("%06d", Pdata);
        else
            sdata.sprintf("%03d", Pdata);
        QString tmpstr;
        tmpstr.sprintf("%03d", paddr);
        tmpstr = tmpstr.right(3)+ sAction;
        QString tmpstr2;
        tmpstr2.sprintf("%03d", PcommID);
        tmpstr2 = tmpstr2.right(3) + sdatalen + sdata;
        tmpstr += tmpstr2;
        return tmpstr + CHkSTR(tmpstr) + '\r';
    }
}

QString cPumpControl::SynCommand(int paddr,int PcommID, QString Pdata)
{
    QString sAction, sdatalen, tmpstr;
    if(PcommID >= 300 && PcommID <= 399){
        sAction = "00";
        sdatalen = "02=?";

        tmpstr.sprintf("%03d", paddr);
        tmpstr = tmpstr.right(3) + sAction;
        QString tmpstr2;
        tmpstr2.sprintf("%03d", PcommID);
        tmpstr2 = tmpstr2.right(3) + sdatalen;
        tmpstr += tmpstr2;

        return tmpstr + CHkSTR(tmpstr) + '\r';
    }else{
        QString sdata;
        sAction = "10";
        sdatalen = "06";
        if ((PcommID != 23 && PcommID != 50 && PcommID != 61 && (PcommID >= 17 && PcommID <= 100))
            || PcommID == 708 || PcommID == 720 || PcommID == 797)
            sdatalen = "03";

        if(Pdata.size()> 6)
            Pdata = Pdata.right(6);
        if(Pdata.size()> 3 && sdatalen != "06")
            Pdata = Pdata.right(3);
        if(Pdata.size()< 6 && sdatalen == "06"){
            tmpstr = "";
            for(int i=0;i<6 - Pdata.size();i++)
                tmpstr = tmpstr + "0";
            Pdata = tmpstr + Pdata;
        }
        if(Pdata.size()< 3 && sdatalen == "03"){
            tmpstr = "";
            for(int i=0;i<3 - Pdata.size();i++)
                tmpstr = tmpstr + "0";
            Pdata = tmpstr + Pdata;
        }
        sdata = Pdata;

        tmpstr.sprintf("%03d", paddr);
        tmpstr = tmpstr.right(3) + sAction;
        QString tmpstr2;
        tmpstr2.sprintf("%03d", PcommID);
        tmpstr2 = tmpstr2.right(3) + sdatalen + sdata;
        tmpstr += tmpstr2;
        return tmpstr + CHkSTR(tmpstr) + '\r';
    }
}

double cPumpControl::getDrive(const QByteArray& tmpR)
{
    return QString::fromLocal8Bit(tmpR,tmpR.size()).mid(10, 6).toDouble()/100.0;
}

qint32 cPumpControl::getSpeed(const QByteArray& tmpR)
{
    return QString::fromLocal8Bit(tmpR,tmpR.size()).mid(10, 6).toInt();
}

bool cPumpControl::getDrive(const QByteArray& tmpR, _STATE_REQUEST& pSTATE_REQUEST)
{
    if(tmpR.size()<512)
        return false;
    quint32* pCMD32= (quint32*)(tmpR.data());
    int lengthCMD16= pCMD32[125]&0xff;
    QByteArray mBaReq_r;
    mBaReq_r.resize(lengthCMD16);
    for(int i=0;i<lengthCMD16;i++)
        mBaReq_r.data()[i]=static_cast<char>(pCMD32[i+5]& 0xff);

    pSTATE_REQUEST.adcValue[0]= static_cast<double>(pCMD32[3] & 0x0000ffff) * 20.0 / 65535 - 10;
    pSTATE_REQUEST.adcValue[1]= static_cast<double>((pCMD32[3]>>16) & 0x0000ffff) * 20.0 / 65535 - 10;
    pSTATE_REQUEST.adcValue[2]= static_cast<double>(pCMD32[4] & 0x0000ffff) * 20.0 / 65535 - 10;
    pSTATE_REQUEST.adcValue[3]= static_cast<double>((pCMD32[4]>>16) & 0x0000ffff) * 20.0 / 65535 - 10;
    pSTATE_REQUEST.driveCurrent= getDrive(mBaReq_r);//pSTATE_REQUEST.driveCurrent= QString::fromLocal8Bit(mBaReq_r,mBaReq_r.size()).mid(10, 6).toDouble()/100.0;
    return true;
}

bool cPumpControl::getRotatinSpeed(const QByteArray& tmpR, _STATE_REQUEST& pSTATE_REQUEST)
{
    if(tmpR.size()<512)
        return false;
    quint32* pCMD32= (quint32*)(tmpR.data());
    int lengthCMD16= pCMD32[125]&0xff;
    QByteArray mBaReq_r;
    mBaReq_r.resize(lengthCMD16);
    for(int i=0;i<lengthCMD16;i++)
        mBaReq_r.data()[i]= static_cast<char>(pCMD32[i+5]& 0xff);

    pSTATE_REQUEST.adcValue[0]= static_cast<double>(pCMD32[3] & 0x0000ffff) * 20.0 / 65535 - 10;
    pSTATE_REQUEST.adcValue[1]= static_cast<double>((pCMD32[3]>>16) & 0x0000ffff) * 20.0 / 65535 - 10;
    pSTATE_REQUEST.adcValue[2]= static_cast<double>(pCMD32[4] & 0x0000ffff) * 20.0 / 65535 - 10;
    pSTATE_REQUEST.adcValue[3]= static_cast<double>((pCMD32[4]>>16) & 0x0000ffff) * 20.0 / 65535 - 10;
    pSTATE_REQUEST.rotatinSpeed= getSpeed(mBaReq_r);//pSTATE_REQUEST.rotatinSpeed= QString::fromLocal8Bit(mBaReq_r,mBaReq_r.size()).mid(10, 6).toInt();
    return true;
}

qint32 cPumpControl::getnominalspd(const QByteArray &tmpR)
{
    return QString::fromLocal8Bit(tmpR,tmpR.size()).mid(10, 6).toInt();
}
