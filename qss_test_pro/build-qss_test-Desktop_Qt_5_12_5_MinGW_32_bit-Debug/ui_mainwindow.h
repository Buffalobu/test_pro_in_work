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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QCheckBox *checkBox;
    QRadioButton *radioButton;
    QComboBox *comboBox;
    QGroupBox *groupBox;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWidget *widget;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QLabel *m_pIconLabel;
    QLabel *m_pTitleLabel;
    QPushButton *m_pMinimizeButton;
    QPushButton *m_pMaximizeButton;
    QPushButton *m_pCloseButton;
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
        pushButton->setGeometry(QRect(120, 170, 75, 23));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 1px solid #333333;\n"
"    padding: 4px;\n"
"    min-width: 65px;\n"
"    min-height: 12px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: rgb(242, 255, 246);\n"
"    border-color: #444444;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #111111;\n"
"    border-color: #333333;\n"
"    color: yellow;\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    color: #333333;\n"
"}"));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(120, 250, 71, 16));
        checkBox->setStyleSheet(QString::fromUtf8("QCheckBox::indicator{\n"
"    width: 16px;\n"
"    height: 16px;\n"
"    background-color: #111111;\n"
"    border: 1px solid #333333;\n"
"}\n"
"\n"
"QCheckBox::indicator::checked{\n"
"    background-color: qradialgradient(cx:0.5, cy:0.5, fx:0.25, fy:0.15, radius:0.3, stop:0 #BBBBBB, stop:1 #111111);\n"
"}\n"
"\n"
"QCheckBox::indicator:disabled {\n"
"    background-color: #444444;\n"
"}\n"
"\n"
"QCheckBox::indicator::checked:disabled {\n"
"    background-color: qradialgradient(cx:0.5, cy:0.5, fx:0.25, fy:0.15, radius:0.3, stop:0 #BBBBBB, stop:1 #444444);\n"
"}\n"
""));
        radioButton = new QRadioButton(centralwidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(110, 320, 89, 16));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(100, 390, 111, 31));
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    background-color: black;\n"
"    border: 1px solid #333333;\n"
"    color: white;\n"
"    padding:1px 2em 1px 3px;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    border-left: 1px solid #333333;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    border: 2px solid #333333;\n"
"    width: 6px;\n"
"    height: 6px;\n"
"    background: #5f5f5f;\n"
"}\n"
""));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(300, 350, 241, 181));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 2px solid #333333;\n"
"    margin-top: 2ex;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    color:rgb(0, 0, 0);\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left;\n"
"    margin-left: 5px;\n"
"}"));
        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 50, 75, 23));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(30, 80, 75, 23));
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(30, 110, 75, 23));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 801, 32));
        widget->setMinimumSize(QSize(0, 32));
        widget->setMaximumSize(QSize(16777215, 32));
        widget1 = new QWidget(widget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(0, 0, 801, 34));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        m_pIconLabel = new QLabel(widget1);
        m_pIconLabel->setObjectName(QString::fromUtf8("m_pIconLabel"));
        m_pIconLabel->setMinimumSize(QSize(32, 32));
        m_pIconLabel->setMaximumSize(QSize(32, 32));
        m_pIconLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/logo_32.jpg")));

        horizontalLayout->addWidget(m_pIconLabel);

        m_pTitleLabel = new QLabel(widget1);
        m_pTitleLabel->setObjectName(QString::fromUtf8("m_pTitleLabel"));
        m_pTitleLabel->setMinimumSize(QSize(0, 32));

        horizontalLayout->addWidget(m_pTitleLabel);

        m_pMinimizeButton = new QPushButton(widget1);
        m_pMinimizeButton->setObjectName(QString::fromUtf8("m_pMinimizeButton"));
        m_pMinimizeButton->setMinimumSize(QSize(0, 32));

        horizontalLayout->addWidget(m_pMinimizeButton);

        m_pMaximizeButton = new QPushButton(widget1);
        m_pMaximizeButton->setObjectName(QString::fromUtf8("m_pMaximizeButton"));
        m_pMaximizeButton->setMinimumSize(QSize(0, 32));

        horizontalLayout->addWidget(m_pMaximizeButton);

        m_pCloseButton = new QPushButton(widget1);
        m_pCloseButton->setObjectName(QString::fromUtf8("m_pCloseButton"));
        m_pCloseButton->setMinimumSize(QSize(0, 32));

        horizontalLayout->addWidget(m_pCloseButton);

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
        pushButton->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "CheckBox", nullptr));
        radioButton->setText(QApplication::translate("MainWindow", "RadioButton", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "GroupBox", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        m_pIconLabel->setText(QString());
        m_pTitleLabel->setText(QApplication::translate("MainWindow", "LIT", nullptr));
        m_pMinimizeButton->setText(QApplication::translate("MainWindow", "\346\234\200\345\260\217\345\214\226", nullptr));
        m_pMaximizeButton->setText(QApplication::translate("MainWindow", "\350\277\230\345\216\237", nullptr));
        m_pCloseButton->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
