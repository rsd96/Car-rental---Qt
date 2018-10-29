#include "driver.h"

Driver::Driver()
{

}

Driver::Driver(int id, string name, int yoe)
{
    this->id = id;
    this->name = name;
    this->yoe = yoe;
}


ostream& operator << (ostream & out, const Driver & d)
{
    out << d.id << "," << d.name << "," << d.yoe;
    return out;
}

istream & operator>> (istream & in, Driver &d)
{
    string id;
    string yoe;
    getline(in, id, ',');
    d.id = atoi(id.c_str());

    getline(in, d.name, ',');
    getline(in, yoe);
    d.yoe = atoi(yoe.c_str());
    return in;
}
