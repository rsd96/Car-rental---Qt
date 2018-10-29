#include "assignmentdialog.h"
#include "ui_assignmentdialog.h"
#include <QListWidgetItem>
#include <QString>
#include <string>
#include "assignmentwindow.h"

AssignmentDialog::AssignmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AssignmentDialog)
{
    ui->setupUi(this);

    m_vehicles = Vehicles::readFromFile();
    m_drivers = Drivers::readFromFile();

    ui->dtFrom->setDate(QDate::currentDate());
    ui->dtFrom->setTime(QTime::currentTime());
    ui->dtTo->setDate(QDate::currentDate());
    ui->dtTo->setTime(QTime::currentTime());
}

AssignmentDialog::~AssignmentDialog()
{
    delete ui;
}

void AssignmentDialog::on_buttonBox_accepted()
{
    QDate fromD = ui->dtFrom->date();
    QTime fromT = ui->dtFrom->time();
    QDate toD = ui->dtTo->date();
    QTime toF = ui->dtTo->time();
    //QDateTime t = ui->dtFrom->dateTime();
    string fromDatetmp = fromD.toString("yyyy-MM-dd").toUtf8().constData();
    string fromTimetmp2 = fromT.toString("HH:mm:ss").toUtf8().constData();
    string toDatetmp = toD.toString("yyyy-MM-dd").toUtf8().constData();
    string toTimetmp2 = toF.toString("HH:mm:ss").toUtf8().constData();
    //QDate FromDate = QDate::fromString(fromDatetmp,"yyyy-MM-dd");
    //QTime FromTime = QTime::fromString(fromTimetmp2,"HH:mm:ss");
    //QDate toDate = QDate::fromString(toDatetmp,"yyyy-MM-dd");
    //QTime toTime = QTime::fromString(toTimetmp2,"HH:mm:ss");
    //ui->dtTo->setDate(Date);
    //ui->dtTo->setTime(Time);
    int driverIndex = ui->lvAssignDrivers->currentRow();
    cout << "Driver index : " << driverIndex << endl;
    int vehicleIndex = ui->lvAssignVehicles->currentRow();
    int driverId = m_drivers.at(driverIndex+1).getID();
    cout << "Driver id : " << driverId << endl;
    string vehiclePlate = ui->lvAssignVehicles->currentItem()->text().toUtf8().constData();
    ((AssignmentWindow *)this->parent())->newAssignment(m_drivers[driverId], m_vehicles[vehiclePlate], fromDatetmp,fromTimetmp2,toDatetmp,toTimetmp2);

   // m_assignments.push_back(Assignment(&m_drivers[34], &m_vehicles["L123"], 50, 90));

}
// shows list of all free drivers and vehicles (update as time changes)
void AssignmentDialog::loadFree() {

    Drivers free_drivers = ((AssignmentWindow *)this->parent())->getFreeDrivers(m_fromdatetime, m_todatetime);
    Vehicles free_vehicles = ((AssignmentWindow *)this->parent())->getFreeVehicles(m_fromdatetime, m_todatetime);

    ui->lvAssignDrivers->clear();
    ui->lvAssignVehicles->clear();

    // Load all driver names to assign
    Drivers::iterator drivers_iter;
    for (drivers_iter = free_drivers.begin(); drivers_iter != free_drivers.end(); ++drivers_iter) {
        Driver driver = drivers_iter->second;
        ui->lvAssignDrivers->addItem(QString::fromStdString(driver.getName()));
    }


    Vehicles::iterator vehicle_iter;
    for (vehicle_iter = free_vehicles.begin(); vehicle_iter != free_vehicles.end(); ++vehicle_iter) {
        Vehicle vehicle = vehicle_iter->second;
        ui->lvAssignVehicles->addItem(QString::fromStdString(vehicle.getPlate()));
    }

}

void AssignmentDialog::on_dtFrom_dateTimeChanged(const QDateTime &dateTime)
{
    this->m_fromdatetime = dateTime;
    ui->dtTo->setMinimumDateTime(dateTime);
    loadFree();
}

void AssignmentDialog::on_dtTo_dateTimeChanged(const QDateTime &dateTime)
{
    this->m_todatetime = dateTime;
    ui->dtFrom->setMaximumDateTime(dateTime);
    loadFree();
}
