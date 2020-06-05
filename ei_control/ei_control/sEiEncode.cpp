#include "sEiEncode.h"
#include "ui_sEiEncode.h"

sEiEncode::sEiEncode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sEiEncode)
{
    ui->setupUi(this);
}

sEiEncode::~sEiEncode()
{
    delete ui;
}

/*  EIEN控制命令生成，参数为true表示开，false为关。
 *  灯丝开/关  FIEN
 *  0x01   0x10   0x0    0x2a    0x0     0x2     0x4    0x0   0x0   0x0   XX   CRL    CRH
 *  XX为0/1:  开/关。
 */
QByteArray sEiEncode::FIEN_setting(bool flag)
{
    QByteArray ba;
    ba.resize(13);
    ba[0] = 0x01;
    ba[1] = 0x10;
    ba[2] = 0x0;
    ba[3] = 0x2a;
    ba[4] = 0x0;
    ba[5] = 0x2;
    ba[6] = 0x4;
    ba[7] = 0x0;
    ba[8] = 0x0;
    ba[9] = 0x0;
    if(flag){
        ba[10] = 0x1;
    }else{
        ba[10] = 0x0;
    }
    uchar CRCHi, CRCLo;
    ushort k = sCRC16::usMBCRC16((uchar*)ba.data(), 11, CRCHi, CRCLo);
    ba[11] = CRCLo;
    ba[12] = CRCHi;
    return  ba;
}

/* EIEN控制命令发送后模块的返回值
 * 模块地址	命令	寄存器高地址	寄存器低地址	数据字长度（高8位）	数据字长度（低8位）	  CRC校验（低8位）	 CRC校验（高8位）
      1	     16	    00	       XX	         00	               2	                  XX	             XX
 * 使能的寄存器地址为2a
 */
QByteArray sEiEncode::FIEN_returnValue()
{
    QByteArray ba;
    ba.resize(8);
    ba[0] = 0x01;
    ba[1] = 0x10;
    ba[2] = 0x0;
    ba[3] = 0x2a;
    ba[4] = 0x0;
    ba[5] = 0x2;
    uchar CRCHi, CRCLo;
    ushort k = sCRC16::usMBCRC16((uchar*)ba.data(), 6, CRCHi, CRCLo);
    ba[6] = CRCLo;
    ba[7] = CRCHi;
    return ba;
}

/*	设置EIST
 *  0x01   0x10   0x0    0x32    0x0     0x2     0x4    X1   X2   X3   X4   CRL    CRH
 *  X1 X2 X3 X4 是EIST 32位的浮点数。
 */
QByteArray sEiEncode::EIST_setting(float value)
{
    QByteArray ba;
    ba.resize(13);
    ba[0] = 0x01;
    ba[1] = 0x10;
    ba[2] = 0x0;
    ba[3] = 0x32;
    ba[4] = 0x0;
    ba[5] = 0x2;
    ba[6] = 0x4;
    QByteArray array;
    int len_intVar = sizeof(value);
    array.resize(len_intVar);
    memcpy(ba.data() + 7, &value, len_intVar);
    uchar CRCHi, CRCLo;
    ushort k = sCRC16::usMBCRC16((uchar*)ba.data(), 11, CRCHi, CRCLo);
    ba[11] = CRCLo;
    ba[12] = CRCHi;
    return  ba;
}

/* EIST控制命令发送后模块的返回值
 * 模块地址	命令	寄存器高地址	寄存器低地址	数据字长度（高8位）	数据字长度（低8位）	  CRC校验（低8位）	 CRC校验（高8位）
      1	     16	    00	       XX	         00	               2	                  XX	             XX
 * EIST的寄存器地址为32
 */
QByteArray sEiEncode::EIST_returnValue()
{
    QByteArray ba;
    ba.resize(8);
    ba[0] = 0x01;
    ba[1] = 0x10;
    ba[2] = 0x0;
    ba[3] = 0x32;
    ba[4] = 0x0;
    ba[5] = 0x2;
    uchar CRCHi, CRCLo;
    ushort k = sCRC16::usMBCRC16((uchar*)ba.data(), 6, CRCHi, CRCLo);
    ba[6] = CRCLo;
    ba[7] = CRCHi;
    return ba;
}

/*  设置FIGN
 *  0x01   0x10   0x0    0x0b    0x0     0x2     0x4    X1   X2   X3   X4   CRL    CRH
 *  X1 X2 X3 X4 是FIGN 32位的浮点数。
 */
QByteArray sEiEncode::FIGN_setting(float value)
{
    QByteArray ba;
    ba.resize(13);
    ba[0] = 0x01;
    ba[1] = 0x10;
    ba[2] = 0x0;
    ba[3] = 0x0b;
    ba[4] = 0x0;
    ba[5] = 0x2;
    ba[6] = 0x4;
    QByteArray array;
    int len_intVar = sizeof(value);
    array.resize(len_intVar);
    memcpy(ba.data() + 7, &value, len_intVar);
    uchar CRCHi, CRCLo;
    ushort k = sCRC16::usMBCRC16((uchar*)ba.data(), 11, CRCHi, CRCLo);
    ba[11] = CRCLo;
    ba[12] = CRCHi;
    return  ba;
}

/* FIGN控制命令发送后模块的返回值
 * 模块地址	命令	寄存器高地址	寄存器低地址	数据字长度（高8位）	数据字长度（低8位）	  CRC校验（低8位）	 CRC校验（高8位）
      1	     16	    00	       XX	         00	               2	                  XX	             XX
 * FIGN的寄存器地址为0b
 */
QByteArray sEiEncode::FIGN_returnValue()
{
    QByteArray ba;
    ba.resize(8);
    ba[0] = 0x01;
    ba[1] = 0x10;
    ba[2] = 0x0;
    ba[3] = 0x0b;
    ba[4] = 0x0;
    ba[5] = 0x2;
    uchar CRCHi, CRCLo;
    ushort k = sCRC16::usMBCRC16((uchar*)ba.data(), 6, CRCHi, CRCLo);
    ba[6] = CRCLo;
    ba[7] = CRCHi;
    return ba;
}

/*	读EMIC
 *  0x01   0x03   0x0    0x32    0x0     0x02    CRL    CRH
 */
QByteArray sEiEncode::EMIC_getting()//EMIC读取命令生成
{
    QByteArray ba;
    ba.resize(8);
    ba[0] = 0x01;
    ba[1] = 0x03;
    ba[2] = 0x0;
    ba[3] = 0x32;
    ba[4] = 0x0;
    ba[5] = 0x02;
    uchar CRCHi, CRCLo;
    ushort k = sCRC16::usMBCRC16((uchar*)ba.data(), 6, CRCHi, CRCLo);
    ba[6] = CRCLo;
    ba[7] = CRCHi;
    return  ba;
}
/*	读FILC
 *  0x01   0x03   0x0    0x16    0x0     0x2     CRL    CRH
 */
QByteArray sEiEncode::FILC_getting()//FILC读取命令生成
{
    QByteArray ba;
    ba.resize(8);
    ba[0] = 0x01;
    ba[1] = 0x03;
    ba[2] = 0x0;
    ba[3] = 0x16;
    ba[4] = 0x0;
    ba[5] = 0x02;
    uchar CRCHi, CRCLo;
    ushort k = sCRC16::usMBCRC16((uchar*)ba.data(), 6, CRCHi, CRCLo);
    ba[6] = CRCLo;
    ba[7] = CRCHi;
    return  ba;
}

/*读取两个电流时模块的返回值，长度为4字节浮点数，故返回值应为9个字节
 * 模块地址	命令	数据字节长度 （2-254）	    数据	   CRC校验（低8位）	 CRC校验（高8位）
 *    1	     03	      XX              XX个字节	     XX	              XX
 */
float sEiEncode::EMIC_FILC_decode(QByteArray rt)
{
    if(rt.size() != 9)
        return FLT_MAX;
    //CRC校验
    QByteArray ba;
    ba.resize(7);
    memcpy(ba.data(), rt.data(), 56);//七个字节的数据
    uchar CRCHi, CRCLo;
    ushort k = sCRC16::usMBCRC16((uchar*)ba.data(), 7, CRCHi, CRCLo);
    if((CRCLo != rt[7]) ||(CRCHi != rt[8])){
        return  FLT_MAX;
    }
    //QByteArray转float
    float current;
    memcpy(&current, rt.data() + 3, sizeof(current));
    return current;
}
