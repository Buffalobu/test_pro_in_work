#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cPumpControl.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->UI_LE_SPEED->setEnabled(false);
    ui->UI_LE_CURRENT->setEnabled(false);
    ui->UI_LE_SPEED_O->setEnabled(false);

    ui->UI_LE_SPEED_CONTROL->setVisible(false);
    ui->label_7->setVisible(false);
    ui->label_8->setVisible(false);
//    ui->UI_PB_SETTING->setVisible(false);

    ui->UI_CB_PUMPTYPE->addItem(QString(tr("分子泵")));
    ui->UI_CB_PUMPTYPE->addItem(QString(tr("隔膜泵")));
    ui->UI_CB_PUMPTYPE->setCurrentIndex(0);

}

MainWindow::~MainWindow()
{
    if(mTimerState != -1)
        killTimer(mTimerState);
    mTimerState = -1;
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *evt)
{
    if(evt->timerId()== mTimerState){
        updateStatePump();
    }
}

void MainWindow::updateStatePump(){
    //if(mCommSerialPump.openDevice(0xEA60, 0x10C4, QSerialPort::Baud9600, 300)){新线问题
    if(mCommSerialEIControl.openDevice(0x6001, 0x0403, 9600, 300)){
        QByteArray tempWriteBuff, tempWriteBuff1;
        if(ui->UI_CB_PUMPTYPE->currentText() == tr("分子泵")){
            tempWriteBuff= cPumpControl::pumpDriveCMD(1);
            tempWriteBuff1= cPumpControl::pumpSpeedCMD(1);
        }
        if(ui->UI_CB_PUMPTYPE->currentText() == tr("隔膜泵")){
            tempWriteBuff= cPumpControl::pumpDriveCMD(2);
            tempWriteBuff1= cPumpControl::pumpSpeedCMD(2);
        }
        QByteArray tempReadBuff= mCommSerialEIControl.writeForBack(tempWriteBuff, 20);//
        showDrive(tempReadBuff);
        QByteArray tempReadBuff1= mCommSerialEIControl.writeForBack(tempWriteBuff1, 20);//
        showRotatinSpeed(tempReadBuff1);
    }
}

void MainWindow::on_UI_PB_Start_clicked()
{
    if(mCommSerialEIControl.openDevice(0x6001, 0x0403)){

//        QByteArray fien1 = Control_Code_Open();
        if(ui->UI_CB_PUMPTYPE->currentText() == tr("分子泵")){
            QByteArray fien1 = cPumpControl::pumpOnCMD(1);
            QByteArray tempReadBuff= mCommSerialEIControl.writeForBack(fien1);
        }
        if(ui->UI_CB_PUMPTYPE->currentText() == tr("隔膜泵")){
            QByteArray fien1 = cPumpControl::pumpOnCMD(2);
            QByteArray tempReadBuff= mCommSerialEIControl.writeForBack(fien1);
        }
    }
}


QByteArray MainWindow::Control_Code_Open()
{
    QByteArray ba;
    ba.resize(20);
    ba[0] = 0x30;//48
    ba[1] = 0x34;//52
    ba[2] = 0x32;//50

    ba[3] = 0x31;//49
    ba[4] = 0x30;//48

    ba[5] = 0x30;//48
    ba[6] = 0x31;//49
    ba[7] = 0x30;//48

    ba[8] = 0x30;//48
    ba[9] = 0x36;//54

    ba[10] = 0x31;//49
    ba[11] = 0x31;//49
    ba[12] = 0x31;//49
    ba[13] = 0x31;//49
    ba[14] = 0x31;//49
    ba[15] = 0x31;//49 sum=786, mod256=20

    ba[16] = 0x30;//48
    ba[17] = 0x32;//50
    ba[18] = 0x30;//48

    ba[19] = 0x0D;//13
    return  ba;
}

QByteArray MainWindow::Control_Code_Close(){
    QByteArray ba;
    ba.resize(20);
    ba[0] = 0x30;//48
    ba[1] = 0x34;//52
    ba[2] = 0x32;//50

    ba[3] = 0x31;//49
    ba[4] = 0x30;//48

    ba[5] = 0x30;//48
    ba[6] = 0x31;//49
    ba[7] = 0x30;//48

    ba[8] = 0x30;//48
    ba[9] = 0x36;//54

    ba[10] = 0x30;//48
    ba[11] = 0x30;//48
    ba[12] = 0x30;//48
    ba[13] = 0x30;//48
    ba[14] = 0x30;//48
    ba[15] = 0x30;//48 sum=782, mod256=14

    ba[16] = 0x30;//48
    ba[17] = 0x31;//49
    ba[18] = 0x34;//52

    ba[19] = 0x0D;//13
    return  ba;

}

void MainWindow::on_UI_PB_CLOSE_clicked()
{
    if(mCommSerialEIControl.openDevice(0x6001, 0x0403, 115200)){
        if(ui->UI_CB_PUMPTYPE->currentText() == tr("分子泵")){
            QByteArray fien1 = cPumpControl::pumpOffCMD(1);
            QByteArray tempReadBuff= mCommSerialEIControl.writeForBack(fien1);
        }
        if(ui->UI_CB_PUMPTYPE->currentText() == tr("隔膜泵")){
            QByteArray fien1 = cPumpControl::pumpOffCMD(2);
            QByteArray tempReadBuff= mCommSerialEIControl.writeForBack(fien1);
        }
    }

}


bool MainWindow::showDrive(QByteArray& pArray)
{
    QPalette pa;
    if(pArray.size()!= _PUMP_READ_SIZE){
        pa.setColor(QPalette::WindowText, Qt::red);
        ui->UI_LE_CURRENT->setText(tr("分子泵未连接"));
        return false;
    }else{
        double tempV= cPumpControl::getDrive(pArray);
        pa.setColor(QPalette::WindowText, Qt::black);
        ui->UI_LE_CURRENT->setPalette(pa);
        ui->UI_LE_CURRENT->setText(QString::number(tempV, 'f', 4));
        return true;
    }
}

bool MainWindow::showRotatinSpeed(QByteArray& pArray)
{
    QPalette pa;
    if(pArray.size()!= _PUMP_READ_SIZE){
        pa.setColor(QPalette::WindowText, Qt::red);
        ui->UI_LE_SPEED->setText(tr("分子泵未连接"));
        return false;
    }else{
        qint32 tempV= cPumpControl::getSpeed(pArray);
        pa.setColor(QPalette::WindowText, Qt::black);
        ui->UI_LE_SPEED->setPalette(pa);
        ui->UI_LE_SPEED->setText(QString::number(tempV));
        return true;
    }
}

void MainWindow::on_U_PB_UPDATE_clicked()
{
    mTimerState = startTimer(500);
}

void MainWindow::on_UI_PB_ERDING_clicked()
{
    if(mCommSerialEIControl.openDevice(0x6001, 0x0403)){
        QByteArray tempWriteBuff, tempReadBuff1;
        if(ui->UI_CB_PUMPTYPE->currentText() == tr("分子泵")){
            tempWriteBuff= cPumpControl::nominalspdCMD(1);
            tempReadBuff1= mCommSerialEIControl.writeForBack(tempWriteBuff, 20);//
        }
        if(ui->UI_CB_PUMPTYPE->currentText() == tr("隔膜泵")){
            tempWriteBuff= cPumpControl::nominalspdCMD(2);
            tempReadBuff1= mCommSerialEIControl.writeForBack(tempWriteBuff, 20);//
        }

        QPalette pa;
        if(tempReadBuff1.size()!= _PUMP_READ_SIZE){
            pa.setColor(QPalette::WindowText, Qt::red);
            ui->UI_LE_SPEED_O->setText(tr("分子泵未连接"));
        }else{
            qint32 tempV= cPumpControl::getSpeed(tempReadBuff1);
            pa.setColor(QPalette::WindowText, Qt::black);
            ui->UI_LE_SPEED_O->setPalette(pa);
            ui->UI_LE_SPEED_O->setText(QString::number(tempV));
        }
    }
}

//void MainWindow::on_UI_PB_SETTING_clicked()
//{
//    QString val = ui->UI_LE_SPEED_CONTROL->text().trimmed();
//    if(val.size() != 6 || val == "000075")
//        return;
//    QByteArray tempWriteBuff= cPumpControl::pumpSpeedControlEnableCMD();
// //    QByteArray tempReadBuff= mCommSerialEIControl.writeForBack(tempWriteBuff, 20);
// //    if(tempReadBuff.size() == 0)
// //        return;
//    QByteArray tempWriteBuff1 = cPumpControl::pumpSpeedValueCMD(val);
//    QByteArray tempReadBuff1= mCommSerialEIControl.writeForBack(tempWriteBuff1, 20);

//}
