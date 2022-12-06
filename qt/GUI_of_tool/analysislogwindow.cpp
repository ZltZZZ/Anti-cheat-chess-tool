#include "analysislogwindow.h"
#include "ui_analysislogwindow.h"

AnalysisLogWindow::AnalysisLogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalysisLogWindow)
{
    ui->setupUi(this);
}

AnalysisLogWindow::~AnalysisLogWindow()
{
    delete ui;
}
