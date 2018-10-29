#ifndef ASSIGNMENTWINDOW_H
#define ASSIGNMENTWINDOW_H

#include <QDialog>
#include "drivers.h"
#include "vehicles.h"
#include "assignment.h"

namespace Ui {
class AssignmentWindow;
}

class AssignmentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AssignmentWindow(QWidget *parent = 0);
    ~AssignmentWindow();

    void saveAssignmentsToFile();
    void readAssignmentsFromFile();

    void newAssignment(Driver d, Vehicle v,string fromDate, string fromTime, string toDate, string toTime);
    Vehicles getFreeVehicles(QDateTime from, QDateTime to);
    Drivers getFreeDrivers(QDateTime from, QDateTime to);

private slots:
    void on_btnBackAssignment_clicked();

    void on_btnNewAssignment_clicked();

    void on_btnDeleteAssignment_clicked();


    void on_cbFilterDriver_currentIndexChanged(const QString &arg1);

    void on_cbFilterVehicle_currentIndexChanged(const QString &arg1);

private:
    Ui::AssignmentWindow *ui;

    Vehicles m_vehicles;
    Drivers m_drivers;

    vector<Assignment> m_assignments;

    void updateTable(vector<Assignment> m_assignments);

    void filterList();


    const string assignments_txtfile_path = "assignments.txt";
    const string assignments_binfile_path = "assignmentsBin.bin";
    //const string assignments_txtfile_path = "/Users/Ramshad/Documents/QtProjects/CarRental/Database/assignments.txt";
    //const string assignments_binfile_path = "/Users/Ramshad/Documents/QtProjects/CarRental/Database/assignmentsBin.bin";
    //const string assignments_txtfile_path = "/Users/debobroto/Downloads/CarRental-2/Database/assignments.txt";
};

#endif // ASSIGNMENTWINDOW_H
