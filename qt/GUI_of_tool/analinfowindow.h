#ifndef ANALINFOWINDOW_H
#define ANALINFOWINDOW_H

#include <QDialog>

namespace Ui {
class AnalInfoWindow;
}

class AnalInfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AnalInfoWindow(QWidget *parent = nullptr);
    ~AnalInfoWindow();
    Ui::AnalInfoWindow *ui;
};

#endif // ANALINFOWINDOW_H
