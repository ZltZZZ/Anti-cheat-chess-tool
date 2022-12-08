#ifndef ANALYSISLOGWINDOW_H
#define ANALYSISLOGWINDOW_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class AnalysisLogWindow;
}

class AnalysisLogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AnalysisLogWindow(QWidget *parent = nullptr);
    ~AnalysisLogWindow();
    Ui::AnalysisLogWindow *ui;
    QTimer* timer;
    int sec, minutes, hours, days;

public slots:
    void onTimeOut();
};

#endif // ANALYSISLOGWINDOW_H
