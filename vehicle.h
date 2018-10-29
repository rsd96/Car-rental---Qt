#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>
#include <QStringList>

#include "assignable.h"

using namespace std;

class Vehicle : public Assignable
{
    string plt_no;
    int type;
    int year;
    string country;
    int mileage;
    int capacity;

public:
    Vehicle();
    Vehicle(string p, int t, int y, string cntry, int m, int cap);

    string getPltNo() const { return plt_no; }

    friend ostream& operator<<(ostream& out, const Vehicle& v);
    friend istream& operator>>(istream& in, Vehicle &v);

    string getPlate()   const   { return plt_no; }
    int getType()       const   { return type; }
    int getYear()       const   { return year; }
    string getCountry() const   { return country; }
    int getMileage()    const   { return mileage; }
    int getCapacity()   const   { return capacity; }
};

#endif // VEHICLE_H
