#ifndef ANALYSISLOGWINDOW_H
#define ANALYSISLOGWINDOW_H

#include <QDialog>

namespace Ui {
class AnalysisLogWindow;
}

class AnalysisLogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AnalysisLogWindow(QWidget *parent = nullptr);
    ~AnalysisLogWindow();

private:
    Ui::AnalysisLogWindow *ui;
};

#endif // ANALYSISLOGWINDOW_H
