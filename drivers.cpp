#include "drivers.h"

#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QTextStream>

// for adam, pls dont chnge it, just comment it
//string Drivers::txt_file_name = "drivers.txt";

// for debo and ramshad

string Drivers::txt_file_name = "drivers.txt";
string Drivers::bin_file_name = "driversBin.bin";
//string Drivers::txt_file_name = "/Users/Ramshad/Documents/QtProjects/CarRental/Database/drivers.txt";
//string Drivers::bin_file_name = "/Users/Ramshad/Documents/QtProjects/CarRental/Database/driversBin.bin";

Drivers Drivers::readFromFile()
{
    Drivers drivers;
    fstream drivers_file(txt_file_name, ios::in);
    if(!drivers_file.is_open())
    {
        cout << "Could not open file"<< endl;
    }
    else
    {
        while(!drivers_file.eof())
        {
            Driver driver;
            drivers_file >> driver;
            if(driver.getID() != 0) {
                drivers[driver.getID()] = driver;
            }
            drivers_file.flush();
        }
    }

    drivers_file.close();

    return drivers;
}

void Drivers::saveToFile()
{
    cout << QDir::currentPath().toStdString() << endl;
    ofstream file(txt_file_name, ios::out);
    if (!file) {
        cout << "Error opening file for write !" << endl;
    } else {
        cout << "Writing a new driver to file " << endl;
        map<int, Driver>::iterator drivers_iter;
        for (drivers_iter = this->begin(); drivers_iter != this->end(); ++drivers_iter) {
            Driver driver = drivers_iter->second;
            //QTextStream name = (QTextStream) driver.getName();
            file << driver.getID() << "," << driver.getName() << "," << driver.getYOE() << endl;
        }

        file.flush();
        file.close();
    }

    fstream drivers_bin(bin_file_name, ios::out | ios::binary);
    if(!drivers_bin.is_open())
    {
        cout << "Could not open file";
    }
    else
    {
        map<int, Driver>::iterator v_iter;
        for (v_iter = this->begin(); v_iter != this->end(); ++v_iter)
        {
            drivers_bin.write( (char*)&v_iter->second , sizeof(Driver));
        }
    }

    drivers_bin.close();
}
