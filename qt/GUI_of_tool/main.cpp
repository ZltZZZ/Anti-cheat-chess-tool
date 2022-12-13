#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Anti Cheat Chess Tool");
    w.showMaximized();
    return a.exec();
}
