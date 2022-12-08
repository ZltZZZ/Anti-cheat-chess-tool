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
    AnalysisHandler* alalysis;
    void start_analyze(parser* prsr, engine* engn, suspect_portrait* player, suspect_portrait* db);

private slots:
    void on_actionQuit_triggered();

    void on_actionNew_analysisi_triggered();

signals:

    void close_newAnalWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
