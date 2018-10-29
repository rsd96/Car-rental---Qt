#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <QDateTime>
#include <iostream>

using namespace std;

class Assignment
{
//    Driver *m_driver;
//    Vehicle *m_vehicle;
    int m_driver_id;
    string m_plt_no;
    string m_from_time;
    string m_from_date;
    string m_to_time;
    string m_to_date;

public:
    Assignment();
    //Assignment(Driver *driver, Vehicle *vehicle,string from_date, string from_time, string to_date, string to_time);
    Assignment(int driver, string plt_no,string from_date, string from_time, string to_date, string to_time);

    //Driver * getDriver() const { return m_driver; }
    //Vehicle * getVehicle() const { return m_vehicle; }
    int getDriverID() const { return m_driver_id; }
    string getPltNo() const { return m_plt_no; }
    string getFromTime() const { return m_from_time; }
    string getFromDate() const { return m_from_date; }
    string getToTime() const { return m_to_time; }
    string getToDate() const { return m_to_date; }

    QDateTime getFromDateTime () const { return QDateTime::fromString(QString::fromStdString(m_from_date + " " + m_from_time), "yyyy-MM-dd hh:mm:ss");  }
    QDateTime getToDateTime () const { return QDateTime::fromString(QString::fromStdString(m_to_date + " " + m_to_time), "yyyy-MM-dd hh:mm:ss");  }

    friend ostream& operator << (ostream & out, const Assignment & a);
};

#endif // ASSIGNMENT_H
