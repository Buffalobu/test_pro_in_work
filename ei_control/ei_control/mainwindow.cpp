#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRegExp>
#include <QRegExpValidator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //参数输入LINE_EDIT范围限定
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_UI_PB_EIST_clicked()
{
     if(mCommSerialEIControl.openDevice(0x6001, 0x0403, 115200)){
         float v_EIST = ui->UI_LE_EIST->text().toFloat();
         QByteArray fien1 = mEiEncode.EIST_setting(v_EIST);
         QByteArray tempReadBuff= mCommSerialEIControl.writeForBack(fien1);
         QByteArray returnArr = mEiEncode.EIST_returnValue();
         if(returnArr != tempReadBuff){
             qDebug() << "error on EIST...";
         }
     }
}

void MainWindow::on_UI_PB_FIGN_clicked()
{
    if(mCommSerialEIControl.openDevice(0x6001, 0x0403, 115200)){
        float v_EIST = ui->UI_LE_FIGN->text().toFloat();
        QByteArray fien1 = mEiEncode.FIGN_setting(v_EIST);
        QByteArray tempReadBuff= mCommSerialEIControl.writeForBack(fien1);
        QByteArray returnArr = mEiEncode.FIGN_returnValue();
        if(returnArr != tempReadBuff){
            qDebug() << "error on FIGN...";
        }
    }
}

void MainWindow::on_UI_CB_FIEN_stateChanged(int arg1)
{
    Q_UNUSED(arg1);
    if(ui->UI_CB_FIEN->isChecked()){
        if(mCommSerialEIControl.openDevice(0x6001, 0x0403, 115200)){
            QByteArray fien = mEiEncode.FIEN_setting(true);
            QByteArray tempReadBuff= mCommSerialEIControl.writeForBack(fien);
            QByteArray returnArr = mEiEncode.FIEN_returnValue();
            if(returnArr != tempReadBuff){
                qDebug() << "error on FIEN...";
            }
        }
    }
}

void MainWindow::on_UI_PB_FILC_clicked()
{
    if(mCommSerialEIControl.openDevice(0x6001, 0x0403, 115200)){
        QByteArray fien = mEiEncode.FILC_getting();
        QByteArray tempReadBuff= mCommSerialEIControl.writeForBack(fien);
        float v_FILC = mEiEncode.EMIC_FILC_decode(tempReadBuff);
        ui->UI_LE_FILC->setText(QString::number(v_FILC));
    }
}

void MainWindow::on_UI_PB_EMIC_clicked()
{
    if(mCommSerialEIControl.openDevice(0x6001, 0x0403, 115200)){
        QByteArray fien = mEiEncode.EMIC_getting();
        QByteArray tempReadBuff= mCommSerialEIControl.writeForBack(fien);
        float v_EMIC = mEiEncode.EMIC_FILC_decode(tempReadBuff);
        ui->UI_LE_EMIC->setText(QString::number(v_EMIC));
    }
}
