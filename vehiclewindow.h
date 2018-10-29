#ifndef VEHICLEWINDOW_H
#define VEHICLEWINDOW_H

#include <QDialog>
#include "vehicles.h"

namespace Ui {
class VehicleWindow;
}

class VehicleWindow : public QDialog
{
    Q_OBJECT

public:
    explicit VehicleWindow(QWidget *parent = 0);
    void new_vehicle(string plate, int type, int year, string country, int mileage, int capacity);
    ~VehicleWindow();

private slots:
    void on_btnBackVehicles_clicked();

    void on_btnNewVehicle_clicked();

    void on_btnDeleteVehicle_clicked();

private:
    Ui::VehicleWindow *ui;

    Vehicles m_vehicles;
    void updateTable(Vehicles m_vehicles);
};

#endif // VEHICLEWINDOW_H
