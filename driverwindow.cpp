#include "driverwindow.h"
#include "ui_driverwindow.h"
#include "driverdialog.h"
#include <string>
#include <QStringList>
#include <QStandardItemModel>
#include <QMessageBox>


DriverWindow::DriverWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DriverWindow)
{
    ui->setupUi(this);
    this->showMaximized();

    //this->setStyleSheet("background-color: #ffffff;");

    m_drivers = Drivers::readFromFile();

    updateTable(m_drivers);

}

DriverWindow::~DriverWindow()
{
    delete ui;
}

void DriverWindow::new_driver(int id, QString name, int yoe)
{
    cout << "Inserting new driver" << endl;
    m_drivers[id] = Driver(id, name.toStdString(), yoe);
    m_drivers.saveToFile();
}

void DriverWindow::on_btnBackDriver_clicked()
{
    hide();
    parentWidget()->show();
}

void DriverWindow::on_btnNewDriver_clicked()
{

    DriverDialog driverDialog(this);
    driverDialog.setModal(true);
    driverDialog.exec();
    if(driverDialog.isHidden()){
        updateTable(Drivers::readFromFile());
    }
}

void DriverWindow::on_btnDeleteDriver_clicked()
{

    QItemSelectionModel *selectionModel = ui->tableDrivers->selectionModel();
    QModelIndexList selection = selectionModel->selectedRows();
    QSet<int> rows;
    const QModelIndexList list = ui->tableDrivers->selectionModel()->selection().indexes();
    for (int i = 0; i < list.count(); i++)
    {
        QModelIndex index = list.at(i);
        rows.insert(index.row());
    }
    for (int x : rows.values()) {
        cout << "Rows : " << x <<endl;
        //int row = ui->tableDrivers->selectionModel()->currentIndex().row();
        int id = ui->tableDrivers->model()->data(ui->tableDrivers->model()->index(x,0)).toInt();
        cout << " ID : " << id << endl;
        map<int,Driver>::iterator it;
        it = m_drivers.find(id);
        m_drivers.erase(it);
    }
    m_drivers.saveToFile();
    updateTable(m_drivers);
}


void DriverWindow::updateTable(Drivers m_drivers) {
    QStandardItemModel *model = new QStandardItemModel(0,3,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Years of Experience")));


    ui->tableDrivers->setModel(model);

    for (int c = 0; c < ui->tableDrivers->horizontalHeader()->count(); ++c)
    {
        ui->tableDrivers->horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::Stretch);
    }

    map<int, Driver>::iterator drivers_iter;
    int i;
    for (i = 0, drivers_iter = m_drivers.begin(); drivers_iter != m_drivers.end(); ++drivers_iter, i++) {
        Driver driver = drivers_iter->second;
        //QString idItem = QString::fromStdString("ID : " + to_string(driver.getID()) + " | Name : " + driver.getName());

        QStandardItem *idItem = new QStandardItem(QString::fromStdString(to_string(driver.getID())));
        model->setItem(i,0,idItem);
        QStandardItem *nameItem = new QStandardItem(QString::fromStdString(driver.getName()));
        model->setItem(i,1,nameItem);
        QStandardItem *yrsItem = new QStandardItem(QString::fromStdString(to_string(driver.getYOE())));
        model->setItem(i,2,yrsItem);
        //ui->lvDriver->addItem(idItem);
    }
}


