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

void MainWindow::start_analyze(){
    AnalysisLogWindow* logW = new AnalysisLogWindow;
    //qDebug() << "Started!";
    emit close_newAnalWindow();

    logW->setModal(true);
    logW->setWindowTitle("Analysis in progress");
    logW->setAttribute(Qt::WA_DeleteOnClose, true);
    logW->show();

    this->alalysis = new AnalysisHandler("1", &this->prsr, &this->engn, &this->player, &this->same_rating, logW);
    QThread::currentThread()->setPriority(QThread::LowestPriority);
    this->alalysis->start(QThread::InheritPriority);
    //qDebug() << "Started!";
}
