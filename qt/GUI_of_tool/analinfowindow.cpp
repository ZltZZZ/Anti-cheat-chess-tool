#include "analinfowindow.h"
#include "ui_analinfowindow.h"

AnalInfoWindow::AnalInfoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnalInfoWindow)
{
    ui->setupUi(this);
}

AnalInfoWindow::~AnalInfoWindow()
{
    delete ui;
}
