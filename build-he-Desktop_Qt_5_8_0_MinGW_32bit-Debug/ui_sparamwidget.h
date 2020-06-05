/********************************************************************************
** Form generated from reading UI file 'sparamwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPARAMWIDGET_H
#define UI_SPARAMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sParamWidget
{
public:

    void setupUi(QWidget *sParamWidget)
    {
        if (sParamWidget->objectName().isEmpty())
            sParamWidget->setObjectName(QStringLiteral("sParamWidget"));
        sParamWidget->resize(265, 187);

        retranslateUi(sParamWidget);

        QMetaObject::connectSlotsByName(sParamWidget);
    } // setupUi

    void retranslateUi(QWidget *sParamWidget)
    {
        sParamWidget->setWindowTitle(QApplication::translate("sParamWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class sParamWidget: public Ui_sParamWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPARAMWIDGET_H
