#include "vehicledialog.h"
#include "ui_vehicledialog.h"
#include "mainwindow.h"
#include <string>
#include <QStringList>

VehicleDialog::VehicleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VehicleDialog)
{
    ui->setupUi(this);

    QStringList vehicleTypes;
    vehicleTypes.append("Hatchback");
    vehicleTypes.append("Sedan");
    vehicleTypes.append("SUV");
    vehicleTypes.append("Crossover");
    vehicleTypes.append("Coupe");
    vehicleTypes.append("Convertible");
    ui->cbNewType->addItems(vehicleTypes);
    ui->sbNewYear->setMinimum(1879);
    ui->sbNewYear->setMaximum(2017);
    ui->sbNewYear->setValue(2017);
}

VehicleDialog::~VehicleDialog()
{
    delete ui;
}

void VehicleDialog::on_buttonBox_accepted()
{
    ((VehicleWindow *)this->parent())->new_vehicle(ui->etNewPlate->text().toUtf8().constData(), ui->cbNewType->currentIndex(),
                                                   ui->sbNewYear->value(), ui->etNewCountry->text().toUtf8().constData(),
                                                   ui->sbNewMileage->value(), ui->sbNewCapacity->value());
    this->accept();
}
