#include "vehicle.h"
#include <iostream>

Vehicle::Vehicle()
{

}

Vehicle::Vehicle(string p, int t, int y, string cntry, int m, int cap){
    plt_no = p;
    type = t;
    year = y;
    country = cntry;
    mileage = m;
    capacity = cap;
};

ostream& operator<<(ostream& out, const Vehicle& v)
{
    out << v.plt_no << ' ' << v.type << ' ' << v.year << ' ' << v.country << ' ' << v.mileage << ' ' << v.capacity;
    return out;
}

istream& operator>>(istream& in, Vehicle &v) {
    in >> v.plt_no >> v.type >> v.year >> v.country >> v.mileage >> v.capacity;
    return in;
}
