#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>

#include "assignable.h"

using namespace std;

class Driver : public Assignable
{
    int id;
    string name;
    int yoe;
public:
    Driver();
    Driver(int id, string name, int yoe);

    int getID() const { return id; }
    string getName() const {return name; }
    int getYOE() const { return yoe; }

    friend ostream& operator<<(ostream& out, const Driver& d);
    friend istream& operator>>(istream& in, Driver &d);


};


#endif // DRIVER_H
