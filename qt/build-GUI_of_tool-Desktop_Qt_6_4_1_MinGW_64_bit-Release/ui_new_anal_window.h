/********************************************************************************
** Form generated from reading UI file 'new_anal_window.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEW_ANAL_WINDOW_H
#define UI_NEW_ANAL_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_New_anal_window
{
public:
    QVBoxLayout *verticalLayout_2;
    QGroupBox *Analysis_params_box;
    QVBoxLayout *verticalLayout;
    QGroupBox *Database_params_box;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *pathDB;
    QToolButton *toolButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *nameSusp;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QRadioButton *bullet;
    QRadioButton *blitz;
    QRadioButton *classic;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QRadioButton *minRDontUse;
    QRadioButton *minRUse;
    QLineEdit *minR;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_6;
    QRadioButton *maxRDontUse;
    QRadioButton *maxRUse;
    QLineEdit *maxR;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_7;
    QRadioButton *countMovesDontUse;
    QRadioButton *countMovesUse;
    QLineEdit *countMoves;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QRadioButton *countGamesDontUse;
    QRadioButton *countGamesUse;
    QLineEdit *countGames;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_2;
    QLineEdit *pathEngine;
    QToolButton *toolButton_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QRadioButton *countCPUDef;
    QRadioButton *countCPUCustom;
    QLineEdit *countCpu;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_10;
    QRadioButton *countLinesDef;
    QRadioButton *countLinesCustom;
    QLineEdit *countLines;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_11;
    QRadioButton *hashSizeDef;
    QRadioButton *hashSizeCustom;
    QLineEdit *hashSize;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_12;
    QRadioButton *moveTimeDef;
    QRadioButton *moveTimeCustom;
    QLineEdit *moveTime;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *StartAnalButt;
    QPushButton *loadConfButt;
    QPushButton *saveConfButt;
    QPushButton *CanselButt;
    QDialogButtonBox *OrdinaryButtBox;
    QButtonGroup *MinRButtBox;
    QButtonGroup *CountMovesButtBox;
    QButtonGroup *MoveTimeButtBox;
    QButtonGroup *CountCpuButtBox;
    QButtonGroup *HashSizeButtBox;
    QButtonGroup *MaxRButtBox;
    QButtonGroup *CountLinesButtBox;
    QButtonGroup *CountGamesButtBox;
    QButtonGroup *TypeOfGamesButtBox;

    void setupUi(QDialog *New_anal_window)
    {
        if (New_anal_window->objectName().isEmpty())
            New_anal_window->setObjectName("New_anal_window");
        New_anal_window->resize(801, 601);
        verticalLayout_2 = new QVBoxLayout(New_anal_window);
        verticalLayout_2->setObjectName("verticalLayout_2");
        Analysis_params_box = new QGroupBox(New_anal_window);
        Analysis_params_box->setObjectName("Analysis_params_box");
        verticalLayout = new QVBoxLayout(Analysis_params_box);
        verticalLayout->setObjectName("verticalLayout");
        Database_params_box = new QGroupBox(Analysis_params_box);
        Database_params_box->setObjectName("Database_params_box");
        verticalLayout_3 = new QVBoxLayout(Database_params_box);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_3 = new QLabel(Database_params_box);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        pathDB = new QLineEdit(Database_params_box);
        pathDB->setObjectName("pathDB");
        pathDB->setMaxLength(256);

        horizontalLayout->addWidget(pathDB);

        toolButton = new QToolButton(Database_params_box);
        toolButton->setObjectName("toolButton");

        horizontalLayout->addWidget(toolButton);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(Database_params_box);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        nameSusp = new QLineEdit(Database_params_box);
        nameSusp->setObjectName("nameSusp");
        nameSusp->setMaxLength(61);
        nameSusp->setCursorMoveStyle(Qt::LogicalMoveStyle);

        horizontalLayout_2->addWidget(nameSusp);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_4 = new QLabel(Database_params_box);
        label_4->setObjectName("label_4");

        horizontalLayout_3->addWidget(label_4);

        bullet = new QRadioButton(Database_params_box);
        TypeOfGamesButtBox = new QButtonGroup(New_anal_window);
        TypeOfGamesButtBox->setObjectName("TypeOfGamesButtBox");
        TypeOfGamesButtBox->setExclusive(true);
        TypeOfGamesButtBox->addButton(bullet);
        bullet->setObjectName("bullet");
        bullet->setChecked(true);

        horizontalLayout_3->addWidget(bullet);

        blitz = new QRadioButton(Database_params_box);
        TypeOfGamesButtBox->addButton(blitz);
        blitz->setObjectName("blitz");

        horizontalLayout_3->addWidget(blitz);

        classic = new QRadioButton(Database_params_box);
        TypeOfGamesButtBox->addButton(classic);
        classic->setObjectName("classic");

        horizontalLayout_3->addWidget(classic);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_5 = new QLabel(Database_params_box);
        label_5->setObjectName("label_5");

        horizontalLayout_4->addWidget(label_5);

        minRDontUse = new QRadioButton(Database_params_box);
        MinRButtBox = new QButtonGroup(New_anal_window);
        MinRButtBox->setObjectName("MinRButtBox");
        MinRButtBox->addButton(minRDontUse);
        minRDontUse->setObjectName("minRDontUse");
        minRDontUse->setChecked(true);

        horizontalLayout_4->addWidget(minRDontUse);

        minRUse = new QRadioButton(Database_params_box);
        MinRButtBox->addButton(minRUse);
        minRUse->setObjectName("minRUse");

        horizontalLayout_4->addWidget(minRUse);

        minR = new QLineEdit(Database_params_box);
        minR->setObjectName("minR");
        minR->setFocusPolicy(Qt::StrongFocus);
        minR->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);"));
        minR->setReadOnly(true);
        minR->setClearButtonEnabled(false);

        horizontalLayout_4->addWidget(minR);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_6 = new QLabel(Database_params_box);
        label_6->setObjectName("label_6");

        horizontalLayout_5->addWidget(label_6);

        maxRDontUse = new QRadioButton(Database_params_box);
        MaxRButtBox = new QButtonGroup(New_anal_window);
        MaxRButtBox->setObjectName("MaxRButtBox");
        MaxRButtBox->addButton(maxRDontUse);
        maxRDontUse->setObjectName("maxRDontUse");
        maxRDontUse->setChecked(true);

        horizontalLayout_5->addWidget(maxRDontUse);

        maxRUse = new QRadioButton(Database_params_box);
        MaxRButtBox->addButton(maxRUse);
        maxRUse->setObjectName("maxRUse");

        horizontalLayout_5->addWidget(maxRUse);

        maxR = new QLineEdit(Database_params_box);
        maxR->setObjectName("maxR");
        maxR->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);"));
        maxR->setReadOnly(true);
        maxR->setCursorMoveStyle(Qt::LogicalMoveStyle);

        horizontalLayout_5->addWidget(maxR);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_7 = new QLabel(Database_params_box);
        label_7->setObjectName("label_7");

        horizontalLayout_6->addWidget(label_7);

        countMovesDontUse = new QRadioButton(Database_params_box);
        CountMovesButtBox = new QButtonGroup(New_anal_window);
        CountMovesButtBox->setObjectName("CountMovesButtBox");
        CountMovesButtBox->addButton(countMovesDontUse);
        countMovesDontUse->setObjectName("countMovesDontUse");
        countMovesDontUse->setChecked(true);

        horizontalLayout_6->addWidget(countMovesDontUse);

        countMovesUse = new QRadioButton(Database_params_box);
        CountMovesButtBox->addButton(countMovesUse);
        countMovesUse->setObjectName("countMovesUse");

        horizontalLayout_6->addWidget(countMovesUse);

        countMoves = new QLineEdit(Database_params_box);
        countMoves->setObjectName("countMoves");
        countMoves->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);"));
        countMoves->setReadOnly(true);

        horizontalLayout_6->addWidget(countMoves);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_8 = new QLabel(Database_params_box);
        label_8->setObjectName("label_8");

        horizontalLayout_7->addWidget(label_8);

        countGamesDontUse = new QRadioButton(Database_params_box);
        CountGamesButtBox = new QButtonGroup(New_anal_window);
        CountGamesButtBox->setObjectName("CountGamesButtBox");
        CountGamesButtBox->addButton(countGamesDontUse);
        countGamesDontUse->setObjectName("countGamesDontUse");
        countGamesDontUse->setChecked(true);

        horizontalLayout_7->addWidget(countGamesDontUse);

        countGamesUse = new QRadioButton(Database_params_box);
        CountGamesButtBox->addButton(countGamesUse);
        countGamesUse->setObjectName("countGamesUse");

        horizontalLayout_7->addWidget(countGamesUse);

        countGames = new QLineEdit(Database_params_box);
        countGames->setObjectName("countGames");
        countGames->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);"));
        countGames->setReadOnly(true);

        horizontalLayout_7->addWidget(countGames);


        verticalLayout_3->addLayout(horizontalLayout_7);


        verticalLayout->addWidget(Database_params_box);

        groupBox = new QGroupBox(Analysis_params_box);
        groupBox->setObjectName("groupBox");
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout_8->addWidget(label_2);

        pathEngine = new QLineEdit(groupBox);
        pathEngine->setObjectName("pathEngine");
        pathEngine->setMaxLength(256);

        horizontalLayout_8->addWidget(pathEngine);

        toolButton_2 = new QToolButton(groupBox);
        toolButton_2->setObjectName("toolButton_2");

        horizontalLayout_8->addWidget(toolButton_2);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_9 = new QLabel(groupBox);
        label_9->setObjectName("label_9");

        horizontalLayout_9->addWidget(label_9);

        countCPUDef = new QRadioButton(groupBox);
        CountCpuButtBox = new QButtonGroup(New_anal_window);
        CountCpuButtBox->setObjectName("CountCpuButtBox");
        CountCpuButtBox->addButton(countCPUDef);
        countCPUDef->setObjectName("countCPUDef");
        countCPUDef->setCheckable(true);
        countCPUDef->setChecked(true);
        countCPUDef->setAutoExclusive(true);

        horizontalLayout_9->addWidget(countCPUDef);

        countCPUCustom = new QRadioButton(groupBox);
        CountCpuButtBox->addButton(countCPUCustom);
        countCPUCustom->setObjectName("countCPUCustom");

        horizontalLayout_9->addWidget(countCPUCustom);

        countCpu = new QLineEdit(groupBox);
        countCpu->setObjectName("countCpu");
        countCpu->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);"));
        countCpu->setReadOnly(true);

        horizontalLayout_9->addWidget(countCpu);


        verticalLayout_4->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_10 = new QLabel(groupBox);
        label_10->setObjectName("label_10");

        horizontalLayout_10->addWidget(label_10);

        countLinesDef = new QRadioButton(groupBox);
        CountLinesButtBox = new QButtonGroup(New_anal_window);
        CountLinesButtBox->setObjectName("CountLinesButtBox");
        CountLinesButtBox->addButton(countLinesDef);
        countLinesDef->setObjectName("countLinesDef");
        countLinesDef->setChecked(true);
        countLinesDef->setAutoExclusive(true);

        horizontalLayout_10->addWidget(countLinesDef);

        countLinesCustom = new QRadioButton(groupBox);
        CountLinesButtBox->addButton(countLinesCustom);
        countLinesCustom->setObjectName("countLinesCustom");

        horizontalLayout_10->addWidget(countLinesCustom);

        countLines = new QLineEdit(groupBox);
        countLines->setObjectName("countLines");
        countLines->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);"));
        countLines->setReadOnly(true);

        horizontalLayout_10->addWidget(countLines);


        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_11 = new QLabel(groupBox);
        label_11->setObjectName("label_11");

        horizontalLayout_11->addWidget(label_11);

        hashSizeDef = new QRadioButton(groupBox);
        HashSizeButtBox = new QButtonGroup(New_anal_window);
        HashSizeButtBox->setObjectName("HashSizeButtBox");
        HashSizeButtBox->addButton(hashSizeDef);
        hashSizeDef->setObjectName("hashSizeDef");
        hashSizeDef->setChecked(true);
        hashSizeDef->setAutoExclusive(true);

        horizontalLayout_11->addWidget(hashSizeDef);

        hashSizeCustom = new QRadioButton(groupBox);
        HashSizeButtBox->addButton(hashSizeCustom);
        hashSizeCustom->setObjectName("hashSizeCustom");

        horizontalLayout_11->addWidget(hashSizeCustom);

        hashSize = new QLineEdit(groupBox);
        hashSize->setObjectName("hashSize");
        hashSize->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);"));
        hashSize->setReadOnly(true);

        horizontalLayout_11->addWidget(hashSize);


        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        label_12 = new QLabel(groupBox);
        label_12->setObjectName("label_12");

        horizontalLayout_12->addWidget(label_12);

        moveTimeDef = new QRadioButton(groupBox);
        MoveTimeButtBox = new QButtonGroup(New_anal_window);
        MoveTimeButtBox->setObjectName("MoveTimeButtBox");
        MoveTimeButtBox->addButton(moveTimeDef);
        moveTimeDef->setObjectName("moveTimeDef");
        moveTimeDef->setChecked(true);
        moveTimeDef->setAutoExclusive(true);

        horizontalLayout_12->addWidget(moveTimeDef);

        moveTimeCustom = new QRadioButton(groupBox);
        MoveTimeButtBox->addButton(moveTimeCustom);
        moveTimeCustom->setObjectName("moveTimeCustom");

        horizontalLayout_12->addWidget(moveTimeCustom);

        moveTime = new QLineEdit(groupBox);
        moveTime->setObjectName("moveTime");
        moveTime->setStyleSheet(QString::fromUtf8("background-color: rgb(240, 240, 240);"));
        moveTime->setReadOnly(true);

        horizontalLayout_12->addWidget(moveTime);


        verticalLayout_4->addLayout(horizontalLayout_12);


        verticalLayout->addWidget(groupBox);


        verticalLayout_2->addWidget(Analysis_params_box);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        StartAnalButt = new QPushButton(New_anal_window);
        StartAnalButt->setObjectName("StartAnalButt");

        horizontalLayout_13->addWidget(StartAnalButt);

        loadConfButt = new QPushButton(New_anal_window);
        loadConfButt->setObjectName("loadConfButt");

        horizontalLayout_13->addWidget(loadConfButt);

        saveConfButt = new QPushButton(New_anal_window);
        saveConfButt->setObjectName("saveConfButt");

        horizontalLayout_13->addWidget(saveConfButt);

        CanselButt = new QPushButton(New_anal_window);
        CanselButt->setObjectName("CanselButt");

        horizontalLayout_13->addWidget(CanselButt);


        verticalLayout_2->addLayout(horizontalLayout_13);

        OrdinaryButtBox = new QDialogButtonBox(New_anal_window);
        OrdinaryButtBox->setObjectName("OrdinaryButtBox");
        OrdinaryButtBox->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(OrdinaryButtBox);


        retranslateUi(New_anal_window);
        QObject::connect(OrdinaryButtBox, &QDialogButtonBox::accepted, New_anal_window, qOverload<>(&QDialog::accept));
        QObject::connect(OrdinaryButtBox, &QDialogButtonBox::rejected, New_anal_window, qOverload<>(&QDialog::reject));
        QObject::connect(minRDontUse, &QRadioButton::clicked, minR, qOverload<>(&QLineEdit::clear));
        QObject::connect(maxRDontUse, &QRadioButton::clicked, maxR, qOverload<>(&QLineEdit::clear));
        QObject::connect(countMovesDontUse, &QRadioButton::clicked, countMoves, qOverload<>(&QLineEdit::clear));
        QObject::connect(countGamesDontUse, &QRadioButton::clicked, countGames, qOverload<>(&QLineEdit::clear));
        QObject::connect(countCPUDef, &QRadioButton::clicked, countCpu, qOverload<>(&QLineEdit::clear));
        QObject::connect(countLinesDef, &QRadioButton::clicked, countLines, qOverload<>(&QLineEdit::clear));
        QObject::connect(hashSizeDef, &QRadioButton::clicked, hashSize, qOverload<>(&QLineEdit::clear));
        QObject::connect(moveTimeDef, &QRadioButton::clicked, moveTime, qOverload<>(&QLineEdit::clear));
        QObject::connect(CanselButt, &QPushButton::clicked, New_anal_window, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(New_anal_window);
    } // setupUi

    void retranslateUi(QDialog *New_anal_window)
    {
        New_anal_window->setWindowTitle(QCoreApplication::translate("New_anal_window", "Dialog", nullptr));
        Analysis_params_box->setTitle(QCoreApplication::translate("New_anal_window", "Analysis parameters", nullptr));
        Database_params_box->setTitle(QCoreApplication::translate("New_anal_window", "Database parameters", nullptr));
        label_3->setText(QCoreApplication::translate("New_anal_window", "Path to database (.pgn)", nullptr));
        toolButton->setText(QCoreApplication::translate("New_anal_window", "...", nullptr));
        label->setText(QCoreApplication::translate("New_anal_window", "Name of suspect", nullptr));
        label_4->setText(QCoreApplication::translate("New_anal_window", "Type of games", nullptr));
        bullet->setText(QCoreApplication::translate("New_anal_window", "Bullet", nullptr));
        blitz->setText(QCoreApplication::translate("New_anal_window", "Blitz", nullptr));
        classic->setText(QCoreApplication::translate("New_anal_window", "Classic", nullptr));
        label_5->setText(QCoreApplication::translate("New_anal_window", "Min rating", nullptr));
        minRDontUse->setText(QCoreApplication::translate("New_anal_window", "don't use", nullptr));
        minRUse->setText(QCoreApplication::translate("New_anal_window", "use", nullptr));
        minR->setInputMask(QString());
        label_6->setText(QCoreApplication::translate("New_anal_window", "Max rating", nullptr));
        maxRDontUse->setText(QCoreApplication::translate("New_anal_window", "don't use", nullptr));
        maxRUse->setText(QCoreApplication::translate("New_anal_window", "use", nullptr));
        maxR->setInputMask(QString());
        label_7->setText(QCoreApplication::translate("New_anal_window", "Max count of moves (for each set of attributes)", nullptr));
        countMovesDontUse->setText(QCoreApplication::translate("New_anal_window", "don't use (not recommended)", nullptr));
        countMovesUse->setText(QCoreApplication::translate("New_anal_window", "use", nullptr));
        countMoves->setInputMask(QString());
        label_8->setText(QCoreApplication::translate("New_anal_window", "Max count of suspect's games", nullptr));
        countGamesDontUse->setText(QCoreApplication::translate("New_anal_window", "don't use (not recommended)", nullptr));
        countGamesUse->setText(QCoreApplication::translate("New_anal_window", "use", nullptr));
        countGames->setInputMask(QString());
        groupBox->setTitle(QCoreApplication::translate("New_anal_window", "Engine parameters", nullptr));
        label_2->setText(QCoreApplication::translate("New_anal_window", "Path to engine", nullptr));
        toolButton_2->setText(QCoreApplication::translate("New_anal_window", "...", nullptr));
        label_9->setText(QCoreApplication::translate("New_anal_window", "Count of CPU threads", nullptr));
        countCPUDef->setText(QCoreApplication::translate("New_anal_window", "default (1)", nullptr));
        countCPUCustom->setText(QCoreApplication::translate("New_anal_window", "custom", nullptr));
        countCpu->setInputMask(QString());
        label_10->setText(QCoreApplication::translate("New_anal_window", "Count of lines to analyse", nullptr));
        countLinesDef->setText(QCoreApplication::translate("New_anal_window", "default (4)", nullptr));
        countLinesCustom->setText(QCoreApplication::translate("New_anal_window", "custom", nullptr));
        countLines->setInputMask(QString());
        label_11->setText(QCoreApplication::translate("New_anal_window", "Hash size (MB)", nullptr));
        hashSizeDef->setText(QCoreApplication::translate("New_anal_window", "default (32 MB)", nullptr));
        hashSizeCustom->setText(QCoreApplication::translate("New_anal_window", "custom", nullptr));
        hashSize->setInputMask(QString());
        label_12->setText(QCoreApplication::translate("New_anal_window", "Move time (sec)", nullptr));
        moveTimeDef->setText(QCoreApplication::translate("New_anal_window", "default (1 sec)", nullptr));
        moveTimeCustom->setText(QCoreApplication::translate("New_anal_window", "custom", nullptr));
        moveTime->setInputMask(QString());
        StartAnalButt->setText(QCoreApplication::translate("New_anal_window", "Start analysis", nullptr));
        loadConfButt->setText(QCoreApplication::translate("New_anal_window", "Load configuration", nullptr));
        saveConfButt->setText(QCoreApplication::translate("New_anal_window", "Save configuration", nullptr));
        CanselButt->setText(QCoreApplication::translate("New_anal_window", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class New_anal_window: public Ui_New_anal_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEW_ANAL_WINDOW_H
