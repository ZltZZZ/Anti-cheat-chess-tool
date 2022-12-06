/********************************************************************************
** Form generated from reading UI file 'analysislogwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYSISLOGWINDOW_H
#define UI_ANALYSISLOGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnalysisLogWindow
{
public:
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_7;
    QLabel *count_games_DB;
    QLabel *count_games_susp;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QLabel *label;
    QLabel *time_left;
    QLabel *label_5;
    QLabel *progress;
    QLabel *label_4;
    QLabel *time_all;

    void setupUi(QDialog *AnalysisLogWindow)
    {
        if (AnalysisLogWindow->objectName().isEmpty())
            AnalysisLogWindow->setObjectName("AnalysisLogWindow");
        AnalysisLogWindow->resize(727, 555);
        groupBox = new QGroupBox(AnalysisLogWindow);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(440, 10, 271, 531));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(groupBox);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 245, 485));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        groupBox_2 = new QGroupBox(AnalysisLogWindow);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(11, 11, 421, 211));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        count_games_DB = new QLabel(groupBox_2);
        count_games_DB->setObjectName("count_games_DB");

        verticalLayout_7->addWidget(count_games_DB);

        count_games_susp = new QLabel(groupBox_2);
        count_games_susp->setObjectName("count_games_susp");

        verticalLayout_7->addWidget(count_games_susp);


        gridLayout->addLayout(verticalLayout_7, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);

        label = new QLabel(groupBox_2);
        label->setObjectName("label");

        verticalLayout_3->addWidget(label);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        time_left = new QLabel(groupBox_2);
        time_left->setObjectName("time_left");

        gridLayout->addWidget(time_left, 2, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        progress = new QLabel(groupBox_2);
        progress->setObjectName("progress");

        gridLayout->addWidget(progress, 3, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        time_all = new QLabel(groupBox_2);
        time_all->setObjectName("time_all");

        gridLayout->addWidget(time_all, 1, 1, 1, 1);


        retranslateUi(AnalysisLogWindow);

        QMetaObject::connectSlotsByName(AnalysisLogWindow);
    } // setupUi

    void retranslateUi(QDialog *AnalysisLogWindow)
    {
        AnalysisLogWindow->setWindowTitle(QCoreApplication::translate("AnalysisLogWindow", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("AnalysisLogWindow", "Log", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("AnalysisLogWindow", "GroupBox", nullptr));
        count_games_DB->setText(QCoreApplication::translate("AnalysisLogWindow", "0", nullptr));
        count_games_susp->setText(QCoreApplication::translate("AnalysisLogWindow", "0", nullptr));
        label_3->setText(QCoreApplication::translate("AnalysisLogWindow", "Time :", nullptr));
        label_2->setText(QCoreApplication::translate("AnalysisLogWindow", "DB games analysed (excluding suspect) :", nullptr));
        label->setText(QCoreApplication::translate("AnalysisLogWindow", "Suspect games analyzed :", nullptr));
        time_left->setText(QCoreApplication::translate("AnalysisLogWindow", "0", nullptr));
        label_5->setText(QCoreApplication::translate("AnalysisLogWindow", "Progress :", nullptr));
        progress->setText(QCoreApplication::translate("AnalysisLogWindow", "0", nullptr));
        label_4->setText(QCoreApplication::translate("AnalysisLogWindow", "Time left :", nullptr));
        time_all->setText(QCoreApplication::translate("AnalysisLogWindow", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AnalysisLogWindow: public Ui_AnalysisLogWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYSISLOGWINDOW_H
