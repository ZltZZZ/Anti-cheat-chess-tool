#include "mainwindow.h"
#include "../src/DEC_module.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    engine engn;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
