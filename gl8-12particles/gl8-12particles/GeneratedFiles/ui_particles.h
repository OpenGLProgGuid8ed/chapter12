/********************************************************************************
** Form generated from reading UI file 'particles.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARTICLES_H
#define UI_PARTICLES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_particlesClass
{
public:

    void setupUi(QWidget *particlesClass)
    {
        if (particlesClass->objectName().isEmpty())
            particlesClass->setObjectName(QStringLiteral("particlesClass"));
        particlesClass->resize(600, 400);

        retranslateUi(particlesClass);

        QMetaObject::connectSlotsByName(particlesClass);
    } // setupUi

    void retranslateUi(QWidget *particlesClass)
    {
        particlesClass->setWindowTitle(QApplication::translate("particlesClass", "particles", 0));
    } // retranslateUi

};

namespace Ui {
    class particlesClass: public Ui_particlesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARTICLES_H
