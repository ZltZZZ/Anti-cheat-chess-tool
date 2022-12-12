/********************************************************************************
** Form generated from reading UI file 'analinfowindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALINFOWINDOW_H
#define UI_ANALINFOWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AnalInfoWindow
{
public:
    QHBoxLayout *horizontalLayout_25;
    QGroupBox *Analysis_params_box;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *Database_params_box_3;
    QVBoxLayout *verticalLayout_8;
    QFormLayout *formLayout;
    QLabel *label_25;
    QLabel *pathDB_3;
    QFormLayout *formLayout_2;
    QLabel *label_26;
    QLabel *name;
    QFormLayout *formLayout_3;
    QLabel *label_27;
    QLabel *type;
    QFormLayout *formLayout_4;
    QLabel *label_28;
    QLabel *minR_3;
    QFormLayout *formLayout_5;
    QLabel *label_29;
    QLabel *maxR_3;
    QFormLayout *formLayout_6;
    QLabel *label_30;
    QLabel *countMoves;
    QFormLayout *formLayout_7;
    QLabel *label_31;
    QLabel *countGames_3;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_9;
    QFormLayout *formLayout_8;
    QLabel *label_32;
    QLabel *pathEngn;
    QFormLayout *formLayout_9;
    QLabel *label_33;
    QLabel *countCpu_3;
    QFormLayout *formLayout_10;
    QLabel *label_34;
    QLabel *countLines_3;
    QFormLayout *formLayout_11;
    QLabel *label_35;
    QLabel *hashSize_3;
    QFormLayout *formLayout_12;
    QLabel *label_36;
    QLabel *moveTime_3;
    QPushButton *pushButton;

    void setupUi(QDialog *AnalInfoWindow)
    {
        if (AnalInfoWindow->objectName().isEmpty())
            AnalInfoWindow->setObjectName("AnalInfoWindow");
        AnalInfoWindow->resize(462, 543);
        horizontalLayout_25 = new QHBoxLayout(AnalInfoWindow);
        horizontalLayout_25->setObjectName("horizontalLayout_25");
        Analysis_params_box = new QGroupBox(AnalInfoWindow);
        Analysis_params_box->setObjectName("Analysis_params_box");
        verticalLayout_7 = new QVBoxLayout(Analysis_params_box);
        verticalLayout_7->setObjectName("verticalLayout_7");
        Database_params_box_3 = new QGroupBox(Analysis_params_box);
        Database_params_box_3->setObjectName("Database_params_box_3");
        verticalLayout_8 = new QVBoxLayout(Database_params_box_3);
        verticalLayout_8->setObjectName("verticalLayout_8");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label_25 = new QLabel(Database_params_box_3);
        label_25->setObjectName("label_25");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_25);

        pathDB_3 = new QLabel(Database_params_box_3);
        pathDB_3->setObjectName("pathDB_3");

        formLayout->setWidget(0, QFormLayout::FieldRole, pathDB_3);


        verticalLayout_8->addLayout(formLayout);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName("formLayout_2");
        label_26 = new QLabel(Database_params_box_3);
        label_26->setObjectName("label_26");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_26);

        name = new QLabel(Database_params_box_3);
        name->setObjectName("name");

        formLayout_2->setWidget(0, QFormLayout::FieldRole, name);


        verticalLayout_8->addLayout(formLayout_2);

        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName("formLayout_3");
        label_27 = new QLabel(Database_params_box_3);
        label_27->setObjectName("label_27");

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_27);

        type = new QLabel(Database_params_box_3);
        type->setObjectName("type");

        formLayout_3->setWidget(0, QFormLayout::FieldRole, type);


        verticalLayout_8->addLayout(formLayout_3);

        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName("formLayout_4");
        label_28 = new QLabel(Database_params_box_3);
        label_28->setObjectName("label_28");

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_28);

        minR_3 = new QLabel(Database_params_box_3);
        minR_3->setObjectName("minR_3");

        formLayout_4->setWidget(0, QFormLayout::FieldRole, minR_3);


        verticalLayout_8->addLayout(formLayout_4);

        formLayout_5 = new QFormLayout();
        formLayout_5->setObjectName("formLayout_5");
        label_29 = new QLabel(Database_params_box_3);
        label_29->setObjectName("label_29");

        formLayout_5->setWidget(0, QFormLayout::LabelRole, label_29);

        maxR_3 = new QLabel(Database_params_box_3);
        maxR_3->setObjectName("maxR_3");

        formLayout_5->setWidget(0, QFormLayout::FieldRole, maxR_3);


        verticalLayout_8->addLayout(formLayout_5);

        formLayout_6 = new QFormLayout();
        formLayout_6->setObjectName("formLayout_6");
        label_30 = new QLabel(Database_params_box_3);
        label_30->setObjectName("label_30");

        formLayout_6->setWidget(0, QFormLayout::LabelRole, label_30);

        countMoves = new QLabel(Database_params_box_3);
        countMoves->setObjectName("countMoves");

        formLayout_6->setWidget(0, QFormLayout::FieldRole, countMoves);


        verticalLayout_8->addLayout(formLayout_6);

        formLayout_7 = new QFormLayout();
        formLayout_7->setObjectName("formLayout_7");
        label_31 = new QLabel(Database_params_box_3);
        label_31->setObjectName("label_31");

        formLayout_7->setWidget(0, QFormLayout::LabelRole, label_31);

        countGames_3 = new QLabel(Database_params_box_3);
        countGames_3->setObjectName("countGames_3");

        formLayout_7->setWidget(0, QFormLayout::FieldRole, countGames_3);


        verticalLayout_8->addLayout(formLayout_7);


        verticalLayout_7->addWidget(Database_params_box_3);

        groupBox_2 = new QGroupBox(Analysis_params_box);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_9 = new QVBoxLayout(groupBox_2);
        verticalLayout_9->setObjectName("verticalLayout_9");
        formLayout_8 = new QFormLayout();
        formLayout_8->setObjectName("formLayout_8");
        label_32 = new QLabel(groupBox_2);
        label_32->setObjectName("label_32");

        formLayout_8->setWidget(0, QFormLayout::LabelRole, label_32);

        pathEngn = new QLabel(groupBox_2);
        pathEngn->setObjectName("pathEngn");

        formLayout_8->setWidget(0, QFormLayout::FieldRole, pathEngn);


        verticalLayout_9->addLayout(formLayout_8);

        formLayout_9 = new QFormLayout();
        formLayout_9->setObjectName("formLayout_9");
        label_33 = new QLabel(groupBox_2);
        label_33->setObjectName("label_33");

        formLayout_9->setWidget(0, QFormLayout::LabelRole, label_33);

        countCpu_3 = new QLabel(groupBox_2);
        countCpu_3->setObjectName("countCpu_3");

        formLayout_9->setWidget(0, QFormLayout::FieldRole, countCpu_3);


        verticalLayout_9->addLayout(formLayout_9);

        formLayout_10 = new QFormLayout();
        formLayout_10->setObjectName("formLayout_10");
        label_34 = new QLabel(groupBox_2);
        label_34->setObjectName("label_34");

        formLayout_10->setWidget(0, QFormLayout::LabelRole, label_34);

        countLines_3 = new QLabel(groupBox_2);
        countLines_3->setObjectName("countLines_3");

        formLayout_10->setWidget(0, QFormLayout::FieldRole, countLines_3);


        verticalLayout_9->addLayout(formLayout_10);

        formLayout_11 = new QFormLayout();
        formLayout_11->setObjectName("formLayout_11");
        label_35 = new QLabel(groupBox_2);
        label_35->setObjectName("label_35");

        formLayout_11->setWidget(0, QFormLayout::LabelRole, label_35);

        hashSize_3 = new QLabel(groupBox_2);
        hashSize_3->setObjectName("hashSize_3");

        formLayout_11->setWidget(0, QFormLayout::FieldRole, hashSize_3);


        verticalLayout_9->addLayout(formLayout_11);

        formLayout_12 = new QFormLayout();
        formLayout_12->setObjectName("formLayout_12");
        label_36 = new QLabel(groupBox_2);
        label_36->setObjectName("label_36");

        formLayout_12->setWidget(0, QFormLayout::LabelRole, label_36);

        moveTime_3 = new QLabel(groupBox_2);
        moveTime_3->setObjectName("moveTime_3");

        formLayout_12->setWidget(0, QFormLayout::FieldRole, moveTime_3);


        verticalLayout_9->addLayout(formLayout_12);


        verticalLayout_7->addWidget(groupBox_2);

        pushButton = new QPushButton(Analysis_params_box);
        pushButton->setObjectName("pushButton");

        verticalLayout_7->addWidget(pushButton);


        horizontalLayout_25->addWidget(Analysis_params_box);


        retranslateUi(AnalInfoWindow);
        QObject::connect(pushButton, &QPushButton::clicked, AnalInfoWindow, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(AnalInfoWindow);
    } // setupUi

    void retranslateUi(QDialog *AnalInfoWindow)
    {
        AnalInfoWindow->setWindowTitle(QCoreApplication::translate("AnalInfoWindow", "Analysis info", nullptr));
        Analysis_params_box->setTitle(QCoreApplication::translate("AnalInfoWindow", "Analysis info", nullptr));
        Database_params_box_3->setTitle(QCoreApplication::translate("AnalInfoWindow", "Database parameters", nullptr));
        label_25->setText(QCoreApplication::translate("AnalInfoWindow", "Path to database (.pgn):", nullptr));
        pathDB_3->setText(QString());
        label_26->setText(QCoreApplication::translate("AnalInfoWindow", "Name of suspect:", nullptr));
        name->setText(QString());
        label_27->setText(QCoreApplication::translate("AnalInfoWindow", "Type of games:", nullptr));
        type->setText(QString());
        label_28->setText(QCoreApplication::translate("AnalInfoWindow", "Min rating:", nullptr));
        minR_3->setText(QString());
        label_29->setText(QCoreApplication::translate("AnalInfoWindow", "Max rating:", nullptr));
        maxR_3->setText(QString());
        label_30->setText(QCoreApplication::translate("AnalInfoWindow", "Max count of moves (for each set of attributes):", nullptr));
        countMoves->setText(QString());
        label_31->setText(QCoreApplication::translate("AnalInfoWindow", "Max count of suspect's games:", nullptr));
        countGames_3->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("AnalInfoWindow", "Engine parameters", nullptr));
        label_32->setText(QCoreApplication::translate("AnalInfoWindow", "Path to engine:", nullptr));
        pathEngn->setText(QString());
        label_33->setText(QCoreApplication::translate("AnalInfoWindow", "Count of CPU threads:", nullptr));
        countCpu_3->setText(QString());
        label_34->setText(QCoreApplication::translate("AnalInfoWindow", "Count of lines to analyse:", nullptr));
        countLines_3->setText(QString());
        label_35->setText(QCoreApplication::translate("AnalInfoWindow", "Hash size (MB):", nullptr));
        hashSize_3->setText(QString());
        label_36->setText(QCoreApplication::translate("AnalInfoWindow", "Move time (sec):", nullptr));
        moveTime_3->setText(QString());
        pushButton->setText(QCoreApplication::translate("AnalInfoWindow", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AnalInfoWindow: public Ui_AnalInfoWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALINFOWINDOW_H
