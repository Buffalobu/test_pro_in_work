#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <cCommSerial.h>
#include <QByteArray>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    cCommSerial mCommSerialEIControl;

    int mTimerState = -1;
    void timerEvent(QTimerEvent *evt);

    QByteArray Control_Code_Open();
    QByteArray Control_Code_Close();
    bool showDrive(QByteArray& pArray);
    bool showRotatinSpeed(QByteArray& pArray);

    void updateStatePump();

private slots:
    void on_UI_PB_Start_clicked();

    void on_UI_PB_CLOSE_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
