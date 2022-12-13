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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
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
    QHBoxLayout *horizontalLayout;
    QPlainTextEdit *logText;
    QScrollBar *verticalScrollBar;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *progress;
    QLabel *label_4;
    QLabel *time_all;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QLabel *time_left;
    QVBoxLayout *verticalLayout_7;
    QLabel *count_games_DB;
    QLabel *count_games_susp;
    QLabel *label_5;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *continueButt;
    QPushButton *pauseButt;
    QPushButton *stopButt;
    QPushButton *closeButt;

    void setupUi(QDialog *AnalysisLogWindow)
    {
        if (AnalysisLogWindow->objectName().isEmpty())
            AnalysisLogWindow->setObjectName("AnalysisLogWindow");
        AnalysisLogWindow->resize(803, 555);
        groupBox = new QGroupBox(AnalysisLogWindow);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(440, 10, 351, 531));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(groupBox);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 325, 485));
        horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout->setObjectName("horizontalLayout");
        logText = new QPlainTextEdit(scrollAreaWidgetContents);
        logText->setObjectName("logText");
        QFont font;
        font.setFamilies({QString::fromUtf8("SimSun")});
        font.setPointSize(12);
        font.setBold(false);
        logText->setFont(font);

        horizontalLayout->addWidget(logText);

        verticalScrollBar = new QScrollBar(scrollAreaWidgetContents);
        verticalScrollBar->setObjectName("verticalScrollBar");
        verticalScrollBar->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(verticalScrollBar);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        verticalLayoutWidget = new QWidget(AnalysisLogWindow);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 20, 421, 256));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(verticalLayoutWidget);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName("gridLayout");
        progress = new QLabel(groupBox_2);
        progress->setObjectName("progress");

        gridLayout->addWidget(progress, 3, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        time_all = new QLabel(groupBox_2);
        time_all->setObjectName("time_all");

        gridLayout->addWidget(time_all, 1, 1, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);

        label = new QLabel(groupBox_2);
        label->setObjectName("label");

        verticalLayout_3->addWidget(label);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        time_left = new QLabel(groupBox_2);
        time_left->setObjectName("time_left");

        gridLayout->addWidget(time_left, 2, 1, 1, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        count_games_DB = new QLabel(groupBox_2);
        count_games_DB->setObjectName("count_games_DB");

        verticalLayout_7->addWidget(count_games_DB);

        count_games_susp = new QLabel(groupBox_2);
        count_games_susp->setObjectName("count_games_susp");

        verticalLayout_7->addWidget(count_games_susp);


        gridLayout->addLayout(verticalLayout_7, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 3, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(verticalLayoutWidget);
        groupBox_3->setObjectName("groupBox_3");
        horizontalLayout_2 = new QHBoxLayout(groupBox_3);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        continueButt = new QPushButton(groupBox_3);
        continueButt->setObjectName("continueButt");
        continueButt->setEnabled(false);

        horizontalLayout_2->addWidget(continueButt);

        pauseButt = new QPushButton(groupBox_3);
        pauseButt->setObjectName("pauseButt");

        horizontalLayout_2->addWidget(pauseButt);

        stopButt = new QPushButton(groupBox_3);
        stopButt->setObjectName("stopButt");

        horizontalLayout_2->addWidget(stopButt);


        verticalLayout_2->addWidget(groupBox_3);

        closeButt = new QPushButton(AnalysisLogWindow);
        closeButt->setObjectName("closeButt");
        closeButt->setEnabled(false);
        closeButt->setGeometry(QRect(20, 510, 93, 29));

        retranslateUi(AnalysisLogWindow);
        QObject::connect(closeButt, &QPushButton::clicked, AnalysisLogWindow, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(AnalysisLogWindow);
    } // setupUi

    void retranslateUi(QDialog *AnalysisLogWindow)
    {
        AnalysisLogWindow->setWindowTitle(QCoreApplication::translate("AnalysisLogWindow", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("AnalysisLogWindow", "Log", nullptr));
        logText->setPlainText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("AnalysisLogWindow", "Analysis", nullptr));
        progress->setText(QCoreApplication::translate("AnalysisLogWindow", "0%", nullptr));
        label_4->setText(QCoreApplication::translate("AnalysisLogWindow", "Time left :", nullptr));
        time_all->setText(QCoreApplication::translate("AnalysisLogWindow", "0:0:0:0", nullptr));
        label_2->setText(QCoreApplication::translate("AnalysisLogWindow", "DB games analysed (excluding suspect) :", nullptr));
        label->setText(QCoreApplication::translate("AnalysisLogWindow", "Suspect games analyzed :", nullptr));
        label_3->setText(QCoreApplication::translate("AnalysisLogWindow", "Time :", nullptr));
        time_left->setText(QCoreApplication::translate("AnalysisLogWindow", "0:0:0:0", nullptr));
        count_games_DB->setText(QCoreApplication::translate("AnalysisLogWindow", "0", nullptr));
        count_games_susp->setText(QCoreApplication::translate("AnalysisLogWindow", "0", nullptr));
        label_5->setText(QCoreApplication::translate("AnalysisLogWindow", "Progress :", nullptr));
        groupBox_3->setTitle(QString());
        continueButt->setText(QCoreApplication::translate("AnalysisLogWindow", "continue", nullptr));
        pauseButt->setText(QCoreApplication::translate("AnalysisLogWindow", "pause", nullptr));
        stopButt->setText(QCoreApplication::translate("AnalysisLogWindow", "stop", nullptr));
        closeButt->setText(QCoreApplication::translate("AnalysisLogWindow", "close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AnalysisLogWindow: public Ui_AnalysisLogWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYSISLOGWINDOW_H
