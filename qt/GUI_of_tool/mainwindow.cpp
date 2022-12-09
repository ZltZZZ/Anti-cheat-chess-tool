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
    AnalysisHandler* anal;
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

    free(prsrCpy);
    free(engnCpy);
    free(playerCpy);
    free(dbCpy);

}

void MainWindow::on_actionOpen_analysis_triggered()
{
    QString str;
    QString fileName = QFileDialog::getOpenFileName(this, "Open analysis", QDir::homePath(), "Saved analysis (*.sa)");
    QFile sa(fileName);
    if (!sa.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(this, "Error", "Can't open that file, please try again");
        return;
    }
    QTextStream in (&sa);

    analDB = QSqlDatabase::addDatabase("QSQLITE");
    analDB.setDatabaseName("AnalysisDB.db");
    if (!analDB.open()){
        QMessageBox::critical(this, "Error", "Can't create database, please try again");
        return;
    }

    query = new QSqlQuery(analDB);
    query->exec("CREATE TABLE Analysis(P TINYINT, N TINYINT, B TINYINT, R TINYINT, Q TINYINT, "
                "AC_suspect TINYINT, Moves_suspect BIGINT, AC_database TINYINT, Moves_database BIGINT);");

    model = new QSqlTableModel(this, analDB);
    model->setTable("Analysis");
    model->select();

    ui->analTable->setModel(model);

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
    while (!in.atEnd()) {
        str = in.readLine();

        if (str.isEmpty()){
            break;
        }else{

        }
    }

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

