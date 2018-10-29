#ifndef DRIVERWINDOW_H
#define DRIVERWINDOW_H

#include <QDialog>
#include "drivers.h"
namespace Ui {
class DriverWindow;
}

class DriverWindow : public QDialog
{
    Q_OBJECT


public:
    explicit DriverWindow(QWidget *parent = 0);
    ~DriverWindow();
    void new_driver(int id, QString name, int yoe);
    void updateTable(Drivers);

private slots:


    void on_btnBackDriver_clicked();

    void on_btnNewDriver_clicked();

    void on_btnDeleteDriver_clicked();

private:
    Ui::DriverWindow *ui;

    Drivers m_drivers;

};

#endif // DRIVERWINDOW_H
