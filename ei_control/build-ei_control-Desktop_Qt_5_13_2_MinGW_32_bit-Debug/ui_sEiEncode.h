/********************************************************************************
** Form generated from reading UI file 'sEiEncode.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEIENCODE_H
#define UI_SEIENCODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sEiEncode
{
public:

    void setupUi(QWidget *sEiEncode)
    {
        if (sEiEncode->objectName().isEmpty())
            sEiEncode->setObjectName(QString::fromUtf8("sEiEncode"));
        sEiEncode->resize(400, 300);

        retranslateUi(sEiEncode);

        QMetaObject::connectSlotsByName(sEiEncode);
    } // setupUi

    void retranslateUi(QWidget *sEiEncode)
    {
        sEiEncode->setWindowTitle(QCoreApplication::translate("sEiEncode", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sEiEncode: public Ui_sEiEncode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEIENCODE_H
