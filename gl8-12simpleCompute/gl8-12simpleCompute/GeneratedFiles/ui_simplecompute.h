/********************************************************************************
** Form generated from reading UI file 'simplecompute.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLECOMPUTE_H
#define UI_SIMPLECOMPUTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_simpleComputeClass
{
public:

    void setupUi(QWidget *simpleComputeClass)
    {
        if (simpleComputeClass->objectName().isEmpty())
            simpleComputeClass->setObjectName(QStringLiteral("simpleComputeClass"));
        simpleComputeClass->resize(600, 400);

        retranslateUi(simpleComputeClass);

        QMetaObject::connectSlotsByName(simpleComputeClass);
    } // setupUi

    void retranslateUi(QWidget *simpleComputeClass)
    {
        simpleComputeClass->setWindowTitle(QApplication::translate("simpleComputeClass", "simpleCompute", 0));
    } // retranslateUi

};

namespace Ui {
    class simpleComputeClass: public Ui_simpleComputeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLECOMPUTE_H
