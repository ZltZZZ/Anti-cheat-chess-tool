#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "new_anal_window.h"

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
    New_anal_window wind;
    wind.setModal(true);
    wind.exec();
}

