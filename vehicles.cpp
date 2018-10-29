#include "vehicles.h"

// for adam, pls dont chnge it, just comment it
//string Vehicles::txt_file_name = "vehicles.txt";

string Vehicles::txt_file_name = "vehicles.txt";
string Vehicles::bin_file_name = "vehiclesBin.bin";
// for debo and ramshad
//string Vehicles::txt_file_name = "/Users/Ramshad/Documents/QtProjects/CarRental/Database/vehicles.txt";
//string Vehicles::bin_file_name = "/Users/Ramshad/Documents/QtProjects/CarRental/Database/vehiclesBin.bin";


Vehicles Vehicles::readFromFile()
{
    Vehicles vehicles;
    fstream vehicles_file(txt_file_name, ios::in);
    if(!vehicles_file.is_open())
    {
        cout << "Could not open file";
    }
    else
    {
        while(!vehicles_file.eof())
        {
            Vehicle v;
            vehicles_file >> v;
            if(v.getPltNo() != "")
            {
                vehicles[v.getPltNo()] = v;
            }


        }
    }

    vehicles_file.close();

    return vehicles;
}

void Vehicles::saveToFile()
{
    fstream vehicles_file(txt_file_name, ios::out);
    if(!vehicles_file.is_open())
    {
        cout << "Could not open file";
    }
    else
    {
        map<string, Vehicle>::iterator v_iter;
        for (v_iter = this->begin(); v_iter != this->end(); ++v_iter)
        {
            vehicles_file << v_iter->second << endl;
        }
    }

    vehicles_file.close();

    fstream vehicles_bin(bin_file_name, ios::out | ios::binary);
    if(!vehicles_bin.is_open())
    {
        cout << "Could not open file";
    }
    else
    {
        map<string, Vehicle>::iterator v_iter;
        for (v_iter = this->begin(); v_iter != this->end(); ++v_iter)
        {
            vehicles_bin.write( (char*)&v_iter->second , sizeof(Vehicle));
        }
    }

    vehicles_bin.close();
}
