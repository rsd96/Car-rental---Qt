#ifndef DRIVERDIALOG_H
#define DRIVERDIALOG_H

#include <QDialog>

namespace Ui {
class DriverDialog;
}

class DriverDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DriverDialog(QWidget *parent = 0);
    ~DriverDialog();

private slots:
    void on_btn_insert_clicked();

private:
    Ui::DriverDialog *ui;
};

#endif // DRIVERDIALOG_H
