#include "assignmentwindow.h"
#include "ui_assignmentwindow.h"
#include "assignmentdialog.h"
#include <QStandardItemModel>
#include <string>


AssignmentWindow::AssignmentWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AssignmentWindow)
{
    ui->setupUi(this);
    this->showMaximized();

    m_vehicles = Vehicles::readFromFile();
    m_drivers = Drivers::readFromFile();

    readAssignmentsFromFile();



    if(m_drivers[1].isFree("2017-12-20", "01:01:01", "2017-12-20", "18:59:31"))
        cout << "is free" << endl;
    else
        cout << "is not free" << endl;

    updateTable(m_assignments);

    QStringList drivers;
    drivers.append("All");
    map<int, Driver>::iterator drivers_iter;
    for (drivers_iter = m_drivers.begin(); drivers_iter != m_drivers.end(); ++drivers_iter) {
        Driver driver = drivers_iter->second;
        drivers.append(QString::fromStdString(driver.getName()));
    }
    ui->cbFilterDriver->addItems(drivers);


    QStringList vehicles;
    vehicles.append("All");
    map<string, Vehicle>::iterator vehicle_iter;
    for (vehicle_iter = m_vehicles.begin(); vehicle_iter != m_vehicles.end(); ++vehicle_iter) {
        Vehicle vehicle = vehicle_iter->second;
        vehicles.append(QString::fromStdString(vehicle.getPlate()));
    }
    ui->cbFilterVehicle->addItems(vehicles);
}

void AssignmentWindow::newAssignment(Driver d, Vehicle v ,string fromDate, string fromTime, string toDate, string toTime) {
    Assignment new_assign(d.getID(), v.getPltNo(), fromDate, fromTime, toDate, toTime);
    m_assignments.push_back(new_assign);
    m_drivers[d.getID()].addAssignment(new_assign);
    m_vehicles[v.getPltNo()].addAssignment(new_assign);

    saveAssignmentsToFile();
    updateTable(m_assignments);
}

AssignmentWindow::~AssignmentWindow()
{
    delete ui;
}

void AssignmentWindow::saveAssignmentsToFile()
{
    ofstream file(assignments_txtfile_path);
    if (!file) {
        cout << "Error opening assignments file for write !" << endl;
    } else {
        vector<Assignment>::iterator a_iter;
        for (a_iter = m_assignments.begin(); a_iter != m_assignments.end(); ++a_iter) {
            file << *a_iter << endl;
            cout << *a_iter;
        }
        file.flush();
        file.close();
    }

    ofstream file1(assignments_binfile_path, ios::out | ios::binary);
    if (!file1) {
        cout << "Error opening assignments file for write !" << endl;
    } else {
        vector<Assignment>::iterator a_iter;
        for (a_iter = m_assignments.begin(); a_iter != m_assignments.end(); ++a_iter) {
            file1.write((char *)&(*a_iter), sizeof(Assignment));
            cout << *a_iter;
        }

        file.close();
    }


}

void AssignmentWindow::readAssignmentsFromFile()
{
    m_assignments.clear();
    ifstream infile(assignments_txtfile_path);

    if (!infile) {

        cout << "Error opening assignments file for write !" << endl;
    } else {
        while(infile.good())
        {

            int driver_id = 0;
            string plt_no;
            string from_date;
            string from_time;
            string to_date;
            string to_time;
            infile >> driver_id;
            if(driver_id == 0)
            {
                break;
            }
            infile >> plt_no;
            infile >> from_date;
            infile >> from_time;
            infile >> to_date;
            infile >> to_time;

            if (m_drivers.find(driver_id) != m_drivers.end() && m_vehicles.find(plt_no) != m_vehicles.end()) {
                //cout << plt_no << endl;
                //Assignment newAssignment(&m_drivers[driver_id], &m_vehicles[plt_no], from_date ,from_time, from_date, to_time);
                Assignment newAssignment(driver_id, plt_no, from_date ,from_time, to_date, to_time);
                m_drivers[driver_id].addAssignment(newAssignment);
                m_vehicles[plt_no].addAssignment(newAssignment);
                m_assignments.push_back(newAssignment);
            }

        }
        infile.close();
    }
}

void AssignmentWindow::on_btnBackAssignment_clicked()
{
    hide();
    parentWidget()->show();
}



void AssignmentWindow::on_btnNewAssignment_clicked()
{
    AssignmentDialog assignDialog(this);
    assignDialog.setModal(true);
    assignDialog.exec();
//    if(assignDialog.isHidden()){
//        updateTable();
//    }

}

void AssignmentWindow::on_btnDeleteAssignment_clicked()
{
    m_assignments.erase(m_assignments.begin() + ui->tableAssignment->currentIndex().row());
    saveAssignmentsToFile();
    updateTable(m_assignments);
}


void AssignmentWindow::updateTable(vector<Assignment> m_assignments) {
    QStandardItemModel *model = new QStandardItemModel(0,4,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Driver")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Assigned to")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("From time")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("To time")));


    ui->tableAssignment->setModel(model);

    for (int c = 0; c < ui->tableAssignment->horizontalHeader()->count(); ++c)
    {
        ui->tableAssignment->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }

    vector<Assignment>::iterator a_iter;
    int i;
    for (i = 0, a_iter = m_assignments.begin(); a_iter != m_assignments.end(); ++a_iter, i++) {
        Assignment assignment = *a_iter;
        //QString idItem = QString::fromStdString("ID : " + to_string(driver.getID()) + " | Name : " + driver.getName());
        string fromDateTime = assignment.getFromDate() + " " + assignment.getFromTime();
        string toDateTime = assignment.getToDate() + " " + assignment.getToTime();
        QStandardItem *driverItem = new QStandardItem(QString::fromStdString(m_drivers[assignment.getDriverID()].getName()));
        model->setItem(i,0,driverItem);
        QStandardItem *vehicleItem = new QStandardItem(QString::fromStdString(m_vehicles[assignment.getPltNo()].getPlate()));
        model->setItem(i,1,vehicleItem);
        QStandardItem *fromItem = new QStandardItem(QString::fromStdString(fromDateTime));
        model->setItem(i,2,fromItem);
        QStandardItem *toItem = new QStandardItem(QString::fromStdString(toDateTime));
        model->setItem(i,3,toItem);
        //ui->lvDriver->addItem(idItem);
    }
}

// Return list of only free vehicles
Vehicles AssignmentWindow::getFreeVehicles(QDateTime from, QDateTime to)
{
    Vehicles vehicles;
    Vehicles::iterator v_iter;
    for (v_iter = m_vehicles.begin(); v_iter != m_vehicles.end(); ++v_iter)
    {
        if(v_iter->second.isFree(from, to))
        {
            vehicles[v_iter->first] = v_iter->second;
        }
    }
    return vehicles;
}


// Return list of only free drivers
Drivers AssignmentWindow::getFreeDrivers(QDateTime from, QDateTime to)
{
    Drivers drivers;
    Drivers::iterator v_iter;
    for (v_iter = m_drivers.begin(); v_iter != m_drivers.end(); ++v_iter)
    {
        if(v_iter->second.isFree(from, to))
        {
            drivers[v_iter->first] = v_iter->second;
        }
    }
    return drivers;
}

void AssignmentWindow::on_cbFilterDriver_currentIndexChanged(const QString &cText)
{
    filterList();
}

void AssignmentWindow::on_cbFilterVehicle_currentIndexChanged(const QString &cText)
{
     filterList();
}

void AssignmentWindow::filterList() {
    string val = ui->cbFilterDriver->currentText().toUtf8().constData();
    string vehicleVal = ui->cbFilterVehicle->currentText().toUtf8().constData();
    if (val.compare("All") == 0 && vehicleVal.compare("All") == 0) {
        cout << "all triggered" << endl;
        readAssignmentsFromFile();
        updateTable(m_assignments);
    } else if (val.compare("All") != 0 && vehicleVal.compare("All") == 0) {
        vector<Assignment> driverFilteredList;
        for (int i = 0; i < m_assignments.size(); i++) {
            if (m_drivers[m_assignments[i].getDriverID()].getName() == val) {
                driverFilteredList.push_back(m_assignments[i]);
            }
        }
        updateTable(driverFilteredList);

    } else if (val.compare("All") == 0 && vehicleVal.compare("All") != 0) {

        vector<Assignment> vehicleFilteredList;
        for (int i = 0; i < m_assignments.size(); i++) {
            if (m_vehicles[m_assignments[i].getPltNo()].getPltNo() == vehicleVal) {
                vehicleFilteredList.push_back(m_assignments[i]);
            }
        }
        updateTable(vehicleFilteredList);
    } else {
        vector<Assignment> bothFilterList;
        for (int i = 0; i < m_assignments.size(); i++) {
            if (m_drivers[m_assignments[i].getDriverID()].getName() == val &&  m_vehicles[m_assignments[i].getPltNo()].getPltNo() == vehicleVal) {
                bothFilterList.push_back(m_assignments[i]);
            }
        }
        updateTable(bothFilterList);
    }

}
