#ifndef VEHICLES_H
#define VEHICLES_H

#include "vehicle.h"
#include <map>
#include <fstream>
#include <QString>

using namespace std;

class Vehicles : public map<string, Vehicle>
{

public:
    static string txt_file_name;
    static string bin_file_name;

    Vehicles() {}

    static Vehicles readFromFile();
    void saveToFile();

    Vehicles getFreeOnes(QDateTime from, QDateTime to);

};

#endif // VEHICLES_H
