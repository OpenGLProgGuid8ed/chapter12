/********************************************************************************
** Form generated from reading UI file 'imgpro.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMGPRO_H
#define UI_IMGPRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_imgproClass
{
public:

    void setupUi(QWidget *imgproClass)
    {
        if (imgproClass->objectName().isEmpty())
            imgproClass->setObjectName(QStringLiteral("imgproClass"));
        imgproClass->resize(600, 400);

        retranslateUi(imgproClass);

        QMetaObject::connectSlotsByName(imgproClass);
    } // setupUi

    void retranslateUi(QWidget *imgproClass)
    {
        imgproClass->setWindowTitle(QApplication::translate("imgproClass", "imgpro", 0));
    } // retranslateUi

};

namespace Ui {
    class imgproClass: public Ui_imgproClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMGPRO_H
