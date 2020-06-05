#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sparamwidget.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct _StreamHead{
    enum Type_Param{Type_Null, Type_Tuning, Type_Acquisition};
    unsigned long length = 0;
    Type_Param typeParam = Type_Null;
    unsigned long dateTime = 0;
    //cParamValue::_Segment segment;
    char param[0];
    _StreamHead(){}
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void onParWgt1Moved();
    void onParWgt2Moved();

private:
    Ui::MainWindow *ui;
    sParamWidget* sParWgt = nullptr;
    sParamWidget* sParWgt1 = nullptr;
};
#endif // MAINWINDOW_H
