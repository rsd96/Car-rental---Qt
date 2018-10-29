#ifndef ASSIGNMENTDIALOG_H
#define ASSIGNMENTDIALOG_H

#include <QDialog>
#include "drivers.h"
#include "vehicles.h"

namespace Ui {
class AssignmentDialog;
}

class AssignmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AssignmentDialog(QWidget *parent = 0);
    ~AssignmentDialog();
    Vehicles m_vehicles;
    Drivers m_drivers;

private slots:
    void on_buttonBox_accepted();
    void on_dtFrom_dateTimeChanged(const QDateTime &dateTime);

    void on_dtTo_dateTimeChanged(const QDateTime &dateTime);

private:
    Ui::AssignmentDialog *ui;
    QDateTime m_fromdatetime;
    QDateTime m_todatetime;
    void loadFree();
};

#endif // ASSIGNMENTDIALOG_H
