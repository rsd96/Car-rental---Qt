#ifndef DRIVERS_H
#define DRIVERS_H

#include "driver.h"
#include <fstream>
#include <map>

using namespace std;

class Drivers : public map<int, Driver>
{
public:
    Drivers() {}

    static string txt_file_name;
    static string bin_file_name;

    static Drivers readFromFile();
    void saveToFile();

};


#endif // DRIVERS_H
