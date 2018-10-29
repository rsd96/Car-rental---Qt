#ifndef ASSIGNABLE_H
#define ASSIGNABLE_H

#include <vector>
#include <QDateTime>

#include <string>

#include <assignment.h>

using namespace std;

class Assignent;

class Assignable
{
public:
    Assignable();

    bool isFree(QDateTime from, QDateTime to);
    bool isFree(string fromdate, string fromtime, string todate, string totime);

    void addAssignment(Assignment a);

private:
    vector<Assignment> assignments;
};

#endif // ASSIGNABLE_H
