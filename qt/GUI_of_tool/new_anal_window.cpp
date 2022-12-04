#include "new_anal_window.h"
#include "ui_new_anal_window.h"
#include <QFileDialog>
#include <QDir>

New_anal_window::New_anal_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::New_anal_window)
{
    ui->setupUi(this);
}

New_anal_window::~New_anal_window()
{
    delete ui;
}

void New_anal_window::on_toolButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose a file", QDir::homePath(), "PGN (*.pgn)");
    ui->pathDB->setText(fileName);
}


void New_anal_window::on_minRUse_clicked()
{
    ui->minR->setReadOnly(false);
    ui->minR->setStyleSheet("background-color: rgb(255, 255, 255)");
}


void New_anal_window::on_minRDontUse_clicked()
{
    ui->minR->setReadOnly(true);
    ui->minR->setStyleSheet("background-color: rgb(240, 240, 240)");
}


void New_anal_window::on_maxRDontUse_clicked()
{
    ui->maxR->setReadOnly(true);
    ui->maxR->setStyleSheet("background-color: rgb(240, 240, 240)");
}


void New_anal_window::on_maxRUse_clicked()
{
    ui->maxR->setReadOnly(false);
    ui->maxR->setStyleSheet("background-color: rgb(255, 255, 255)");
}


void New_anal_window::on_countMovesUse_clicked()
{
    ui->countMoves->setReadOnly(false);
    ui->countMoves->setStyleSheet("background-color: rgb(255, 255, 255)");
}


void New_anal_window::on_countMovesDontUse_clicked()
{
    ui->countMoves->setReadOnly(true);
    ui->countMoves->setStyleSheet("background-color: rgb(240, 240, 240)");
}


void New_anal_window::on_countGamesUse_clicked()
{
    ui->countGames->setReadOnly(false);
    ui->countGames->setStyleSheet("background-color: rgb(255, 255, 255)");
}


void New_anal_window::on_countGamesDontUse_clicked()
{
    ui->countGames->setReadOnly(true);
    ui->countGames->setStyleSheet("background-color: rgb(240, 240, 240)");
}


void New_anal_window::on_toolButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose a file", QDir::homePath(), "Engine (*.exe)");
    ui->pathEngine->setText(fileName);
}


void New_anal_window::on_countLinesCustom_clicked()
{
    ui->countLines->setReadOnly(false);
    ui->countLines->setStyleSheet("background-color: rgb(255, 255, 255)");
}


void New_anal_window::on_hashSizeCustom_clicked()
{
    ui->hashSize->setReadOnly(false);
    ui->hashSize->setStyleSheet("background-color: rgb(255, 255, 255)");
}


void New_anal_window::on_moveTimeCustom_clicked()
{
    ui->moveTime->setReadOnly(false);
    ui->moveTime->setStyleSheet("background-color: rgb(255, 255, 255)");
}


void New_anal_window::on_countCPUDef_clicked()
{
    ui->countCpu->setReadOnly(true);
    ui->countCpu->setStyleSheet("background-color: rgb(240, 240, 240)");
}


void New_anal_window::on_countLinesDef_clicked()
{
    ui->countLines->setReadOnly(true);
    ui->countLines->setStyleSheet("background-color: rgb(240, 240, 240)");
}


void New_anal_window::on_hashSizeDef_clicked()
{
    ui->hashSize->setReadOnly(true);
    ui->hashSize->setStyleSheet("background-color: rgb(240, 240, 240)");
}


void New_anal_window::on_moveTimeDef_clicked()
{
    ui->moveTime->setReadOnly(true);
    ui->moveTime->setStyleSheet("background-color: rgb(240, 240, 240)");
}


void New_anal_window::on_countCPUCustom_clicked()
{
    ui->countCpu->setReadOnly(false);
    ui->countCpu->setStyleSheet("background-color: rgb(255, 255, 255)");
}

