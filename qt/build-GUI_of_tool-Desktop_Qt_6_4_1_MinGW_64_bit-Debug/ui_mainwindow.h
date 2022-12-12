/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_analysisi;
    QAction *actionOpen_analysis;
    QAction *actionSave;
    QAction *actionQuit;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_2;
    QTableView *analTablePlayer;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_3;
    QTableView *analTableDB;
    QHBoxLayout *horizontalLayout;
    QPushButton *infoAnalButt;
    QPushButton *buildGraphButt;
    QPushButton *closeDBButt;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuOptions;
    QMenu *menuFilter;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(987, 680);
        actionNew_analysisi = new QAction(MainWindow);
        actionNew_analysisi->setObjectName("actionNew_analysisi");
        actionOpen_analysis = new QAction(MainWindow);
        actionOpen_analysis->setObjectName("actionOpen_analysis");
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName("actionQuit");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        horizontalLayout_2 = new QHBoxLayout(tab);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        analTablePlayer = new QTableView(tab);
        analTablePlayer->setObjectName("analTablePlayer");

        horizontalLayout_2->addWidget(analTablePlayer);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        horizontalLayout_3 = new QHBoxLayout(tab_2);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        analTableDB = new QTableView(tab_2);
        analTableDB->setObjectName("analTableDB");

        horizontalLayout_3->addWidget(analTableDB);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidget);


        verticalLayout->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        infoAnalButt = new QPushButton(centralwidget);
        infoAnalButt->setObjectName("infoAnalButt");
        infoAnalButt->setEnabled(false);

        horizontalLayout->addWidget(infoAnalButt);

        buildGraphButt = new QPushButton(centralwidget);
        buildGraphButt->setObjectName("buildGraphButt");
        buildGraphButt->setEnabled(false);

        horizontalLayout->addWidget(buildGraphButt);

        closeDBButt = new QPushButton(centralwidget);
        closeDBButt->setObjectName("closeDBButt");
        closeDBButt->setEnabled(false);

        horizontalLayout->addWidget(closeDBButt);


        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 987, 32));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName("menuOptions");
        menuFilter = new QMenu(menubar);
        menuFilter->setObjectName("menuFilter");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menubar->addAction(menuFilter->menuAction());
        menuFile->addAction(actionNew_analysisi);
        menuFile->addAction(actionOpen_analysis);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew_analysisi->setText(QCoreApplication::translate("MainWindow", "New analysisi", nullptr));
        actionOpen_analysis->setText(QCoreApplication::translate("MainWindow", "Open analysis", nullptr));
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Analysis results", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Suspect", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "DataBase", nullptr));
        infoAnalButt->setText(QCoreApplication::translate("MainWindow", "Information about analysis", nullptr));
        buildGraphButt->setText(QCoreApplication::translate("MainWindow", "Build Graph", nullptr));
        closeDBButt->setText(QCoreApplication::translate("MainWindow", "Close analysis", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuOptions->setTitle(QCoreApplication::translate("MainWindow", "Options", nullptr));
        menuFilter->setTitle(QCoreApplication::translate("MainWindow", "Filter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
