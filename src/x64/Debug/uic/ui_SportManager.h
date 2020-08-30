/********************************************************************************
** Form generated from reading UI file 'SportManager.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPORTMANAGER_H
#define UI_SPORTMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SportManagerClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SportManagerClass)
    {
        if (SportManagerClass->objectName().isEmpty())
            SportManagerClass->setObjectName(QString::fromUtf8("SportManagerClass"));
        SportManagerClass->resize(600, 400);
        menuBar = new QMenuBar(SportManagerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        SportManagerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SportManagerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SportManagerClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SportManagerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        SportManagerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SportManagerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SportManagerClass->setStatusBar(statusBar);

        retranslateUi(SportManagerClass);

        QMetaObject::connectSlotsByName(SportManagerClass);
    } // setupUi

    void retranslateUi(QMainWindow *SportManagerClass)
    {
        SportManagerClass->setWindowTitle(QCoreApplication::translate("SportManagerClass", "SportManager", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SportManagerClass: public Ui_SportManagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPORTMANAGER_H
