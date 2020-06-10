#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool isFileExist(QString fullFilePath);



private slots:
    void on_UI_PB_SEARCH_clicked();

    void on_UI_PB_SCH_PS_clicked();

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
