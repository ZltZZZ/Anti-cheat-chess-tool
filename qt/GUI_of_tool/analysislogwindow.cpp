#include "analysislogwindow.h"
#include "ui_analysislogwindow.h"

AnalysisLogWindow::AnalysisLogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalysisLogWindow)
{
    ui->setupUi(this);
    sec = 0;
    minutes = 0;
    hours = 0;
    days = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    timer->start(1000);
}

AnalysisLogWindow::~AnalysisLogWindow()
{
    delete ui;
    delete timer;
}

void AnalysisLogWindow::onTimeOut()
{
    sec++;
    if (sec == 60){
        sec = 0;
        minutes++;
    }
    if (minutes == 60){
        minutes = 0;
        hours++;
    }
    if (hours == 24){
        hours = 0;
        days++;
    }

    ui->time_all->setText(QString::number(days) + ":" + QString::number(hours) + ":" + QString::number(minutes) + ":" + QString::number(sec));
}

void AnalysisLogWindow::on_stopButt_clicked()
{
    timer->stop();
    emit some_sign();
    ui->stopButt->setEnabled(false);
    ui->closeButt->setEnabled(true);
    ui->pauseButt->setEnabled(false);
}

