#include "assignable.h"

#include <QDebug>

Assignable::Assignable()
{

}

bool Assignable::isFree(string fromdate, string fromtime, string todate, string totime)
{
    QDateTime fromdatetime = QDateTime::fromString(QString::fromStdString(fromdate + " " + fromtime), "yyyy-MM-dd hh:mm:ss");
    QDateTime todatetime = QDateTime::fromString(QString::fromStdString(todate + " " + totime), "yyyy-MM-dd hh:mm:ss");

    return isFree(fromdatetime,  todatetime);
}

bool Assignable::isFree(QDateTime fromdatetime, QDateTime todatetime)
{
    cout << "checking time " << fromdatetime.toString("yyyy-MM-dd hh:mm:ss").toStdString()
         << " " <<  todatetime.toString("yyyy-MM-dd hh:mm:ss").toStdString() << endl;
    bool is_free = true;
    for(int i=0; i < assignments.size(); i++)
    {
        cout << "Checking assignment " << i
             << " " << assignments.at(i).getFromDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString()
             << " " << assignments.at(i).getToDateTime().toString("yyyy-MM-dd hh:mm:ss").toStdString()
             <<  endl;

        // if from and to is greater than the assignment from and to
        if(fromdatetime <= assignments.at(i).getFromDateTime() && todatetime >= assignments.at(i).getToDateTime())
        {
            is_free = false;
            break;
        }

        // if from lies inside assignment from and to
        if(fromdatetime >= assignments.at(i).getFromDateTime() && fromdatetime <= assignments.at(i).getToDateTime())
        {
            is_free = false;
            break;
        }

        // if to lies inside assignment from and to
        if(todatetime >= assignments.at(i).getFromDateTime() && todatetime <= assignments.at(i).getToDateTime())
        {
            is_free = false;
            break;
        }

    }


    return is_free;
}

void Assignable::addAssignment(Assignment a)
{
    this->assignments.push_back(a);
}
