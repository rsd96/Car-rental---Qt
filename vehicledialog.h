#ifndef VEHICLEDIALOG_H
#define VEHICLEDIALOG_H

#include <QDialog>

namespace Ui {
class VehicleDialog;
}

class VehicleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VehicleDialog(QWidget *parent = 0);
    ~VehicleDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::VehicleDialog *ui;
};

#endif // VEHICLEDIALOG_H
