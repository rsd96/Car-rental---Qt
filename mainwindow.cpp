#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "driverdialog.h"
#include <QEasingCurve>
#include <QAbstractAnimation>
#include <QStringListModel>
#include <QPropertyAnimation>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // set dark stylesheet


    QFile f(":qdarkstyle/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }


    //this->setStyleSheet("background-color: #1e1b18;");
    //this->setStyleSheet("font-color : white;");
    //ui->label->setStyleSheet("QLabel {color : white; }");
    //QPushbutton *button = new QPushbutton;

    // to chnage background

//    QPixmap bkgnd(":/res/mainBG.jpg");
//    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
//    QPalette palette;
//    palette.setBrush(QPalette::Background, bkgnd);
//    this->setPalette(palette);

    ui->btnDriver->setIcon(QIcon(":/new/res/driver_green.png"));
    ui->btnDriver->setIconSize(QSize(65,65));
    ui->btnVehicle->setIcon(QIcon(":/new/res/car_green.png"));
    ui->btnVehicle->setIconSize(QSize(65,65));
    ui->btnAssignment->setIcon(QIcon(":/new/res/assign_green.png"));
    ui->btnAssignment->setIconSize(QSize(65,65));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnDriver_clicked()
{
    driverWindow = new DriverWindow(this);
    hide();
    driverWindow->show();
}

void MainWindow::on_btnVehicle_clicked()
{
    vehicleWindow = new VehicleWindow(this);
    hide();
    vehicleWindow->show();
}

void MainWindow::on_btnAssignment_clicked()
{
    assignmentWindow = new AssignmentWindow(this);
    hide();
    assignmentWindow->show();
}
