#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sParWgt = new sParamWidget(ui->widget_bottom, ui->widget_top, this, 0, false);
    sParWgt->show();
    connect(sParWgt, SIGNAL(cntChanged()), this, SLOT(onParWgt1Moved()));

    sParWgt1 = new sParamWidget(ui->widget_bottom, ui->widget_top, this, 1, false);
    sParWgt1->show();
    connect(sParWgt1, SIGNAL(cntChanged()), this, SLOT(onParWgt2Moved()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onParWgt1Moved()
{
    sParamWidget* sParWgt1 = new sParamWidget(ui->widget_bottom, ui->widget_top, this, 0, true);//ui->widget_bottom
    sParWgt1->show();
}

void MainWindow::onParWgt2Moved()
{
    sParamWidget* sParWgt2 = new sParamWidget(ui->widget_bottom, ui->widget_top, this, 1, true);//ui->widget_bottom
    sParWgt2->show();
}

void MainWindow::on_pushButton_clicked()
{
//    int a= sizeof(_StreamHead);
//    QMessageBox _mSgb;
//    char param[0];
//    _mSgb.setText(QString::number(sizeof(unsigned long))+ "\r" + QString::number(sizeof(_StreamHead)) + "\r" + QString::number(sizeof(param)));
//    _mSgb.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
//    QMessageBox _mSgb;
//    int a=(0xffff >> 3)<<16 | 0xffff >> 3;//536813567
//    _mSgb.setText(QString::number(a));
//    _mSgb.exec();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
//    QPainter* painter = new QPainter;
//    painter->begin(ui->widget_bottom);
//    painter->setPen(QPen(Qt::green, 2, Qt::SolidLine));
//    painter->drawRect(QRect(ui->widget_bottom->rect().x(), ui->widget_bottom->rect().y(), ui->widget_bottom->rect().width(), ui->widget_bottom->rect().height()));
//    painter->end();

//    painter->begin(ui->widget_bottom);
//    painter->setPen(QPen(Qt::red, 2, Qt::SolidLine));
//    painter->drawRect(QRect(ui->widget_top->rect().x(), ui->widget_top->rect().y(), ui->widget_top->rect().width(), ui->widget_top->rect().height()));
//    painter->end();
}
