#include "mainwindow.h"
#include "ui_analinfowindow.h"
#include "ui_mainwindow.h"
#include "new_anal_window.h"
#include "analysislogwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}


void MainWindow::on_actionNew_analysisi_triggered()
{
    New_anal_window* wind = new New_anal_window;
    wind->setModal(true);
    wind->setWindowTitle("New analysis parameters");
    wind->main_w_ptr = this;
    wind->setAttribute(Qt::WA_DeleteOnClose, true);
    connect(this, &MainWindow::close_newAnalWindow, wind, &New_anal_window::closeW);
    wind->exec();
}

void MainWindow::start_analyze(parser* prsr, engine* engn, suspect_portrait* player, suspect_portrait* db){
    AnalysisLogWindow* logW = new AnalysisLogWindow;
    parser* prsrCpy = (parser*)malloc(sizeof(parser));
    engine* engnCpy = (engine*)malloc(sizeof(engine));
    suspect_portrait* playerCpy = (suspect_portrait*)malloc(sizeof(suspect_portrait));
    suspect_portrait* dbCpy = (suspect_portrait*)malloc(sizeof(suspect_portrait));

    memcpy(prsrCpy, prsr, sizeof(parser));
    memcpy(engnCpy, engn, sizeof(engine));
    memcpy(playerCpy, player, sizeof(suspect_portrait));
    memcpy(dbCpy, db, sizeof(suspect_portrait));
    anal = new AnalysisHandler("1", prsrCpy, engnCpy, playerCpy, dbCpy, logW);
    QThread::currentThread()->setPriority(QThread::LowestPriority);
    anal->start(QThread::InheritPriority);

    emit close_newAnalWindow();

    logW->setModal(true);
    logW->setWindowTitle("Analysis in progress");
    logW->setAttribute(Qt::WA_DeleteOnClose, true);
    logW->show();
    connect(logW, SIGNAL(some_sign()), this, SLOT(stop_analysis()));

    free(prsrCpy);
    free(engnCpy);
    free(playerCpy);
    free(dbCpy);

}

void MainWindow::on_actionOpen_analysis_triggered()
{
    // Open file .sa with analisis
    QString str;
    QString fileName = QFileDialog::getOpenFileName(this, "Open analysis", QDir::homePath(), "Saved analysis (*.sa)");
    QFile sa(fileName);
    if (!sa.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(this, "Error", "Can't open that file, please try again");
        return;
    }
    QTextStream in (&sa);

    // Create SQL db
    analDB = QSqlDatabase::addDatabase("QSQLITE");
    analDB.setDatabaseName("AnalysisDB.db");
    if (!analDB.open()){
        QMessageBox::critical(this, "Error", "Can't create database, please try again");
        return;
    }

    // Init new tables with SoA and results for player and db
    query = new QSqlQuery(analDB);
    query->exec("CREATE TABLE AnalysisPlayer(P TINYINT, N TINYINT, B TINYINT, R TINYINT, Q TINYINT, "
                "AC_suspect TINYINT, Moves_suspect BIGINT);");
    query->exec("CREATE TABLE AnalysisDB(P TINYINT, N TINYINT, B TINYINT, R TINYINT, Q TINYINT, "
                "AC_database TINYINT, Moves_database BIGINT);");


    modelPlayer = new QSqlTableModel(this, analDB);
    modelPlayer->setTable("AnalysisPlayer");
    modelPlayer->select();
    modelDB = new QSqlTableModel(this, analDB);
    modelDB->setTable("AnalysisDB");
    modelDB->select();

    // Prepare ui of tables
    ui->analTablePlayer->setModel(modelPlayer);
    ui->analTablePlayer->resizeColumnsToContents();
    ui->analTablePlayer->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->analTablePlayer->horizontalHeader()->setStretchLastSection(true);
    ui->analTablePlayer->setSortingEnabled(true);
    ui->analTableDB->setModel(modelDB);
    ui->analTableDB->resizeColumnsToContents();
    ui->analTableDB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->analTableDB->horizontalHeader()->setStretchLastSection(true);
    ui->analTableDB->setSortingEnabled(true);

    // Open window with information about analisis's parameters
    analIfnfoW = new AnalInfoWindow();

    // Read analysis info
    while (!in.atEnd()) {
        str = in.readLine();

        if (str.isEmpty()){
            break;
        }else{
            QStringList strList = str.split(" ", Qt::SkipEmptyParts);
            if (strList.at(0) == "DB"){
                analIfnfoW->ui->pathDB_3->setText(strList.at(1));
            }else if (strList.at(0) == "NAME"){
                analIfnfoW->ui->name->setText(strList.at(1));
            }else if (strList.at(0) == "ENGINE"){
                analIfnfoW->ui->pathEngn->setText(strList.at(1));
            }else if (strList.at(0) == "CPU"){
                analIfnfoW->ui->countCpu_3->setText(strList.at(1));
            }else if (strList.at(0) == "LINES"){
                analIfnfoW->ui->countLines_3->setText(strList.at(1));
            }else if (strList.at(0) == "HASH"){
                analIfnfoW->ui->hashSize_3->setText(strList.at(1));
            }else if (strList.at(0) == "MOVETIME"){
                analIfnfoW->ui->moveTime_3->setText(strList.at(1));
            }else if (strList.at(0) == "TYPE"){
                analIfnfoW->ui->type->setText(strList.at(1));
            }else if (strList.at(0) == "MINR"){
                if (strList.at(1).toInt() == NO_RATING_MIN) analIfnfoW->ui->minR_3->setText("-");
                else analIfnfoW->ui->minR_3->setText(strList.at(1));
            }else if (strList.at(0) == "MAXR"){
                if (strList.at(1).toInt() == NO_RATING_MAX) analIfnfoW->ui->maxR_3->setText("-");
                else analIfnfoW->ui->maxR_3->setText(strList.at(1));
            }else if (strList.at(0) == "COUNTMOVES"){
                if (strList.at(1).toInt() == MAX_MOVE_COUNT_DEF) analIfnfoW->ui->countMoves->setText("-");
                else analIfnfoW->ui->countMoves->setText(strList.at(1));
            }else if (strList.at(0) == "COUNTGAMES"){
                if (strList.at(1).toInt() == MAX_GAME_COUNT_DEF) analIfnfoW->ui->countGames_3->setText("-");
                else analIfnfoW->ui->countGames_3->setText(strList.at(1));
            }
        }
    }
    analIfnfoW->show();

    // Read SoA and AC
    // First read suspects AC
    while (!in.atEnd()) {
        str = in.readLine();

        if (str.isEmpty()){
            break;
        }else{
            QStringList strList = str.split(" ", Qt::SkipEmptyParts);
            query->prepare("INSERT INTO AnalysisPlayer ( P, N, B, R, Q, AC_suspect, Moves_suspect ) "
                   "VALUES (:P, :N, :B, :R, :Q, :AC_suspect, :Moves_suspect ) ");

            if (strList.at(0) != "X"){
                query->bindValue(":P", strList.at(0).toInt());
            }
            if (strList.at(1) != "X"){
                query->bindValue(":N", strList.at(1).toInt());
            }
            if (strList.at(2) != "X"){
                query->bindValue(":B", strList.at(2).toInt());
            }
            if (strList.at(3) != "X"){
                query->bindValue(":R", strList.at(3).toInt());
            }
            if (strList.at(4) != "X"){
                query->bindValue(":Q", strList.at(4).toInt());
            }
            if (strList.at(5) != "X"){
                query->bindValue(":AC_suspect", (int)strList.at(5).toFloat());
            }
            if (strList.at(6) != "X"){
                query->bindValue(":Moves_suspect", strList.at(6).toInt());
            }

            query->exec();
        }
    }

    // Second insert results in db table
    while (!in.atEnd()) {
        str = in.readLine();

        if (str.isEmpty()){
            break;
        }else {
            QStringList strList = str.split(" ", Qt::SkipEmptyParts);
            query->prepare("INSERT INTO AnalysisDB ( P, N, B, R, Q, AC_database, Moves_database ) "
                   "VALUES (:P, :N, :B, :R, :Q, :AC_database, :Moves_database ) ");

            if (strList.at(0) != "X"){
                query->bindValue(":P", strList.at(0).toInt());
            }
            if (strList.at(1) != "X"){
                query->bindValue(":N", strList.at(1).toInt());
            }
            if (strList.at(2) != "X"){
                query->bindValue(":B", strList.at(2).toInt());
            }
            if (strList.at(3) != "X"){
                query->bindValue(":R", strList.at(3).toInt());
            }
            if (strList.at(4) != "X"){
                query->bindValue(":Q", strList.at(4).toInt());
            }
            if (strList.at(5) != "X"){
                query->bindValue(":AC_database", (int)strList.at(5).toFloat());
            }
            if (strList.at(6) != "X"){
                query->bindValue(":Moves_database", strList.at(6).toInt());
            }

            query->exec();
        }
    }

    modelPlayer->select();
    modelDB->select();

    ui->closeDBButt->setEnabled(true);
    ui->infoAnalButt->setEnabled(true);
    ui->buildGraphButt->setEnabled(true);

    sa.close();
}


void MainWindow::on_infoAnalButt_clicked()
{
    if (analIfnfoW->isHidden())
        analIfnfoW->show();
}


void MainWindow::on_closeDBButt_clicked()
{
    query->clear();
    ui->analTableDB->setModel(0);
    ui->analTablePlayer->setModel(0);
    delete modelDB;
    delete modelPlayer;
    analDB.close();
    analDB.removeDatabase(analDB.connectionName());
    QFile::remove("AnalysisDB.db");
    delete analIfnfoW;

    ui->closeDBButt->setEnabled(false);
    ui->infoAnalButt->setEnabled(false);
    ui->buildGraphButt->setEnabled(false);
}

void MainWindow::stop_analysis()
{
    anal->stop();
    anal->wait();
    anal->on_exit();
    delete anal;
}

