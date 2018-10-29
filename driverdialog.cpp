#include "driverdialog.h"
#include "ui_driverdialog.h"
#include "mainwindow.h"

DriverDialog::DriverDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DriverDialog)
{
    ui->setupUi(this);

    QRegExp rx("[A-z ]+");
        QRegExpValidator  *valid = new QRegExpValidator(rx,this);
        ui->txt_name->setValidator(valid);

}

DriverDialog::~DriverDialog()
{
    delete ui;
}

void DriverDialog::on_btn_insert_clicked()
{
    ((DriverWindow *)this->parent())->new_driver(ui->spinBox_id->value(), ui->txt_name->text(), ui->spinBox_yoe->value());
    this->accept();
}
