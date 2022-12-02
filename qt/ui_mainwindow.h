/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_analisis;
    QAction *actionNew_analisis;
    QAction *actionSave_analisis;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menufile;
    QMenu *menuOptions;
    QMenu *menuFilter;
    QMenu *menuQuit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        actionOpen_analisis = new QAction(MainWindow);
        actionOpen_analisis->setObjectName(QString::fromUtf8("actionOpen_analisis"));
        actionNew_analisis = new QAction(MainWindow);
        actionNew_analisis->setObjectName(QString::fromUtf8("actionNew_analisis"));
        actionSave_analisis = new QAction(MainWindow);
        actionSave_analisis->setObjectName(QString::fromUtf8("actionSave_analisis"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menufile = new QMenu(menubar);
        menufile->setObjectName(QString::fromUtf8("menufile"));
        menufile->setTearOffEnabled(false);
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        menuFilter = new QMenu(menubar);
        menuFilter->setObjectName(QString::fromUtf8("menuFilter"));
        menuQuit = new QMenu(menubar);
        menuQuit->setObjectName(QString::fromUtf8("menuQuit"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menufile->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menubar->addAction(menuFilter->menuAction());
        menubar->addAction(menuQuit->menuAction());
        menufile->addAction(actionOpen_analisis);
        menufile->addAction(actionNew_analisis);
        menufile->addAction(actionSave_analisis);
        menufile->addSeparator();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen_analisis->setText(QCoreApplication::translate("MainWindow", "Open analisis", nullptr));
        actionNew_analisis->setText(QCoreApplication::translate("MainWindow", "New analisis", nullptr));
        actionSave_analisis->setText(QCoreApplication::translate("MainWindow", "Save analisis", nullptr));
        menufile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuOptions->setTitle(QCoreApplication::translate("MainWindow", "Options", nullptr));
        menuFilter->setTitle(QCoreApplication::translate("MainWindow", "Filter", nullptr));
        menuQuit->setTitle(QCoreApplication::translate("MainWindow", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
