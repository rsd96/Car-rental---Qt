#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "driverwindow.h"
#include "vehiclewindow.h"
#include "drivers.h"
#include "vehicles.h"
#include "assignmentwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:

    void on_btnDriver_clicked();

    void on_btnVehicle_clicked();

    void on_btnAssignment_clicked();

private:
    Ui::MainWindow *ui;
    DriverWindow *driverWindow;
    VehicleWindow *vehicleWindow;
    AssignmentWindow *assignmentWindow;


    Vehicles m_vehicles;

    //void back_to_main_page();
};

#endif // MAINWINDOW_H
