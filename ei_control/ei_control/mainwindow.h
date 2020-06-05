#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <cCommSerial.h>
#include <QByteArray>
#include <sEiEncode.h>
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
    sEiEncode mEiEncode;

private slots:
    void on_UI_PB_EIST_clicked();

    void on_UI_PB_FIGN_clicked();

    void on_UI_CB_FIEN_stateChanged(int arg1);

    void on_UI_PB_FILC_clicked();

    void on_UI_PB_EMIC_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
