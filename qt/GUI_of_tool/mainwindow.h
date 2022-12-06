#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../src/DEC_module.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    engine engn;
    parser prsr;
    suspect_portrait player;
    suspect_portrait same_rating;

private slots:
    void on_actionQuit_triggered();

    void on_actionNew_analysisi_triggered();

public slots:
    void start_analyze();

signals:

    void close_newAnalWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
