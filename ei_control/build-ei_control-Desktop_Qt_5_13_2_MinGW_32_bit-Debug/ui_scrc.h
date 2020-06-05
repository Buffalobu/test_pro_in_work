/********************************************************************************
** Form generated from reading UI file 'scrc.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCRC_H
#define UI_SCRC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sCRC
{
public:

    void setupUi(QWidget *sCRC)
    {
        if (sCRC->objectName().isEmpty())
            sCRC->setObjectName(QString::fromUtf8("sCRC"));
        sCRC->resize(400, 300);

        retranslateUi(sCRC);

        QMetaObject::connectSlotsByName(sCRC);
    } // setupUi

    void retranslateUi(QWidget *sCRC)
    {
        sCRC->setWindowTitle(QCoreApplication::translate("sCRC", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sCRC: public Ui_sCRC {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCRC_H
