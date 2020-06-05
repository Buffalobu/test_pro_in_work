#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTranslator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    translator = new QTranslator(qApp);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    if(translator != nullptr)
    {
        delete  translator;
        translator = nullptr;
    }
    delete ui;
}

/**
* @projectName translate_test
* @brief       摘要
* @param       参数1,参数2...
* @author      LuoYong
* @date        2019-11-11
*/
void MainWindow::on_pushButton_clicked()
{
    if(!m_bTranslator)
    {
        //此文件：cn.qm放在G:\hello\build-translate_test-Desktop_Qt_5_13_2_MinGW_32_bit-Debug文件夹下。
        translator->load("cn.qm");
        qApp->installTranslator(translator);
        ui->retranslateUi(this);
    }
    else
    {
        qApp->removeTranslator(translator);
        ui->retranslateUi(this);
    }
    m_bTranslator = !m_bTranslator;
}
