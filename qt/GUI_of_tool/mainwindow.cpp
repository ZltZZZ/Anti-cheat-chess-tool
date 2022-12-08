#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "new_anal_window.h"
#include "analysislogwindow.h"

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
