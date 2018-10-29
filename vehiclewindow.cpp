#include "vehiclewindow.h"
#include "ui_vehiclewindow.h"
#include "vehicledialog.h"
#include <string>
#include <QStringList>
#include <QStandardItemModel>
#include <QMessageBox>

VehicleWindow::VehicleWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VehicleWindow)
{
    ui->setupUi(this);
    this->showMaximized();
    m_vehicles = Vehicles::readFromFile();
    updateTable(m_vehicles);
}

VehicleWindow::~VehicleWindow()
{
    delete ui;
}

void VehicleWindow::new_vehicle(string plate, int type, int year, string country, int mileage, int capacity)
{
    cout << "Inserting new Vehicle" << endl;
    m_vehicles[plate] = Vehicle(plate, type, year, country, mileage, capacity);
    m_vehicles.saveToFile();
}

void VehicleWindow::on_btnBackVehicles_clicked()
{
    hide();
    parentWidget()->show();
}

void VehicleWindow::on_btnNewVehicle_clicked()
{
    VehicleDialog vehicleDialog(this);
    vehicleDialog.setModal(true);
    vehicleDialog.exec();
    if(vehicleDialog.isHidden()){
        updateTable(Vehicles::readFromFile());
    }
}

void VehicleWindow::on_btnDeleteVehicle_clicked()
{
    QItemSelectionModel *selectionModel = ui->tableVehicles->selectionModel();
    QModelIndexList selection = selectionModel->selectedRows();
    QSet<int> rows;
    const QModelIndexList list = ui->tableVehicles->selectionModel()->selection().indexes();
    for (int i = 0; i < list.count(); i++)
    {
        QModelIndex index = list.at(i);
        rows.insert(index.row());
    }
    for (int x : rows.values()) {
        cout << "Rows : " << x <<endl;
        //int row = ui->tableDrivers->selectionModel()->currentIndex().row();
        string plate = ui->tableVehicles->model()->data(ui->tableVehicles->model()->index(x,0)).toString().toUtf8().constData();
        cout << " ID : " << plate << endl;
        map<string,Vehicle>::iterator it;
        it = m_vehicles.find(plate);
        m_vehicles.erase(it);
    }
    m_vehicles.saveToFile();
    updateTable(m_vehicles);
}

void VehicleWindow::updateTable(Vehicles m_vehicles) {
    QStandardItemModel *model = new QStandardItemModel(0,5,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Number Plate")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Type")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Year")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Country")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Mileage")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Capacity")));

    ui->tableVehicles->setModel(model);

    for (int c = 0; c < ui->tableVehicles->horizontalHeader()->count(); ++c)
    {
        ui->tableVehicles->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }

    QStringList vehicleTypes;
    vehicleTypes.append("Hatchback");
    vehicleTypes.append("Sedan");
    vehicleTypes.append("SUV");
    vehicleTypes.append("Crossover");
    vehicleTypes.append("Coupe");
    vehicleTypes.append("Convertible");

    map<string, Vehicle>::iterator vehicle_iter;
    int i;
    for (i = 0, vehicle_iter = m_vehicles.begin(); vehicle_iter != m_vehicles.end(); ++vehicle_iter, i++) {
        Vehicle vehicle = vehicle_iter->second;
        //QString idItem = QString::fromStdString("ID : " + to_string(driver.getID()) + " | Name : " + driver.getName());

        QStandardItem *plateItem = new QStandardItem(QString::fromStdString(vehicle.getPltNo()));
        model->setItem(i,0,plateItem);
        QStandardItem *typeItem = new QStandardItem(vehicleTypes[vehicle.getType()]);
        model->setItem(i,1,typeItem);
        QStandardItem *yrsItem = new QStandardItem(QString::fromStdString(to_string(vehicle.getYear())));
        model->setItem(i,2,yrsItem);
        QStandardItem *countryItem = new QStandardItem(QString::fromStdString(vehicle.getCountry()));
        model->setItem(i,3,countryItem);
        QStandardItem *mileageItem = new QStandardItem(QString::fromStdString(to_string(vehicle.getMileage())));
        model->setItem(i,4,mileageItem);
        QStandardItem *capacityItem = new QStandardItem(QString::fromStdString(to_string(vehicle.getCapacity())));
        model->setItem(i,5,capacityItem);
        //ui->lvDriver->addItem(idItem);
    }
}
