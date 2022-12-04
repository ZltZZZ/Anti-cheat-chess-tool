#ifndef NEW_ANAL_WINDOW_H
#define NEW_ANAL_WINDOW_H

#include <QDialog>

namespace Ui {
class New_anal_window;
}

class New_anal_window : public QDialog
{
    Q_OBJECT

public:
    explicit New_anal_window(QWidget *parent = nullptr);
    ~New_anal_window();

private slots:
    void on_toolButton_clicked();

    void on_minRUse_clicked();

    void on_minRDontUse_clicked();

    void on_maxRDontUse_clicked();

    void on_maxRUse_clicked();

    void on_countMovesUse_clicked();

    void on_countMovesDontUse_clicked();

    void on_countGamesUse_clicked();

    void on_countGamesDontUse_clicked();

    void on_toolButton_2_clicked();

    void on_countLinesCustom_clicked();

    void on_hashSizeCustom_clicked();

    void on_moveTimeCustom_clicked();

    void on_countCPUDef_clicked();

    void on_countLinesDef_clicked();

    void on_hashSizeDef_clicked();

    void on_moveTimeDef_clicked();

    void on_countCPUCustom_clicked();

private:
    Ui::New_anal_window *ui;
};

#endif // NEW_ANAL_WINDOW_H
