#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../src/DEC_module.h"
#include "analinfowindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

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

    void on_actionOpen_analysis_triggered();

    void on_infoAnalButt_clicked();

    void on_closeDBButt_clicked();

public slots:
    void stop_analysis();

signals:

    void close_newAnalWindow();

private:
    Ui::MainWindow *ui;
    QSqlDatabase analDB;
    QSqlQuery* query;
    QSqlTableModel* modelPlayer;
    QSqlTableModel* modelDB;
    AnalInfoWindow* analIfnfoW;
    AnalysisHandler* anal;
};
#endif // MAINWINDOW_H
