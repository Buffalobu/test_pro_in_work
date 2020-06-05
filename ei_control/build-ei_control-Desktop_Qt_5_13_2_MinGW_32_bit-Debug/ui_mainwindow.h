/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QCheckBox *UI_CB_FIEN;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *UI_LE_EIST;
    QLineEdit *UI_LE_FIGN;
    QPushButton *UI_PB_EIST;
    QPushButton *UI_PB_FIGN;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *UI_LE_EMIC;
    QLineEdit *UI_LE_FILC;
    QPushButton *UI_PB_EMIC;
    QPushButton *UI_PB_FILC;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        UI_CB_FIEN = new QCheckBox(centralwidget);
        UI_CB_FIEN->setObjectName(QString::fromUtf8("UI_CB_FIEN"));
        UI_CB_FIEN->setGeometry(QRect(80, 200, 71, 16));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 260, 54, 12));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 310, 54, 12));
        UI_LE_EIST = new QLineEdit(centralwidget);
        UI_LE_EIST->setObjectName(QString::fromUtf8("UI_LE_EIST"));
        UI_LE_EIST->setGeometry(QRect(100, 260, 113, 20));
        UI_LE_FIGN = new QLineEdit(centralwidget);
        UI_LE_FIGN->setObjectName(QString::fromUtf8("UI_LE_FIGN"));
        UI_LE_FIGN->setGeometry(QRect(100, 310, 113, 20));
        UI_PB_EIST = new QPushButton(centralwidget);
        UI_PB_EIST->setObjectName(QString::fromUtf8("UI_PB_EIST"));
        UI_PB_EIST->setGeometry(QRect(240, 260, 75, 23));
        UI_PB_FIGN = new QPushButton(centralwidget);
        UI_PB_FIGN->setObjectName(QString::fromUtf8("UI_PB_FIGN"));
        UI_PB_FIGN->setGeometry(QRect(240, 310, 75, 23));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(390, 260, 54, 12));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(390, 320, 54, 12));
        UI_LE_EMIC = new QLineEdit(centralwidget);
        UI_LE_EMIC->setObjectName(QString::fromUtf8("UI_LE_EMIC"));
        UI_LE_EMIC->setGeometry(QRect(460, 260, 113, 20));
        UI_LE_FILC = new QLineEdit(centralwidget);
        UI_LE_FILC->setObjectName(QString::fromUtf8("UI_LE_FILC"));
        UI_LE_FILC->setGeometry(QRect(460, 320, 113, 20));
        UI_PB_EMIC = new QPushButton(centralwidget);
        UI_PB_EMIC->setObjectName(QString::fromUtf8("UI_PB_EMIC"));
        UI_PB_EMIC->setGeometry(QRect(610, 260, 75, 23));
        UI_PB_FILC = new QPushButton(centralwidget);
        UI_PB_FILC->setObjectName(QString::fromUtf8("UI_PB_FILC"));
        UI_PB_FILC->setGeometry(QRect(610, 320, 75, 23));
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
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        UI_CB_FIEN->setText(QCoreApplication::translate("MainWindow", "FIEN", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "EIST", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "FIGN", nullptr));
        UI_LE_EIST->setText(QCoreApplication::translate("MainWindow", "0.5", nullptr));
        UI_LE_FIGN->setText(QCoreApplication::translate("MainWindow", "55", nullptr));
        UI_PB_EIST->setText(QCoreApplication::translate("MainWindow", "Set", nullptr));
        UI_PB_FIGN->setText(QCoreApplication::translate("MainWindow", "Set", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "EMIC", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "FILC", nullptr));
        UI_PB_EMIC->setText(QCoreApplication::translate("MainWindow", "Get", nullptr));
        UI_PB_FILC->setText(QCoreApplication::translate("MainWindow", "Get", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
