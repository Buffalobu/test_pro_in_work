/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *UI_PB_CONVERT;
    QPushButton *UI_PB_LOAD;
    QPushButton *UI_PB_READMSB;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(230, 310, 75, 23));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(230, 450, 75, 23));
        UI_PB_CONVERT = new QPushButton(centralwidget);
        UI_PB_CONVERT->setObjectName(QString::fromUtf8("UI_PB_CONVERT"));
        UI_PB_CONVERT->setGeometry(QRect(360, 310, 75, 23));
        UI_PB_LOAD = new QPushButton(centralwidget);
        UI_PB_LOAD->setObjectName(QString::fromUtf8("UI_PB_LOAD"));
        UI_PB_LOAD->setGeometry(QRect(120, 310, 75, 23));
        UI_PB_READMSB = new QPushButton(centralwidget);
        UI_PB_READMSB->setObjectName(QString::fromUtf8("UI_PB_READMSB"));
        UI_PB_READMSB->setGeometry(QRect(500, 310, 75, 23));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "ReadMSB", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "\345\216\213\347\274\251", nullptr));
        UI_PB_CONVERT->setText(QApplication::translate("MainWindow", "\350\275\254\346\215\242", nullptr));
        UI_PB_LOAD->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245", nullptr));
        UI_PB_READMSB->setText(QApplication::translate("MainWindow", "MyReadMSB", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
