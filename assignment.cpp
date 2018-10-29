#include <assignment.h>

//Assignment::Assignment(Driver *driver, Vehicle *vehicle, string from_date, string from_time, string to_date, string to_time) {
//    m_driver = driver;
//    m_vehicle = vehicle;
//    m_from_date = from_date;
//    m_from_time = from_time;
//    m_to_date = to_date;
//    m_to_time = to_time;
//}

Assignment::Assignment(int driver_id, string plt_no, string from_date, string from_time, string to_date, string to_time) {
    m_driver_id = driver_id;
    m_plt_no = plt_no;
    m_from_date = from_date;
    m_from_time = from_time;
    m_to_date = to_date;
    m_to_time = to_time;
}

ostream& operator << (ostream & out, const Assignment & a) {
       out << a.m_driver_id << " " << a.m_plt_no << " " <<a.m_from_date << " " << a.m_from_time << " " << a.m_to_date << " " << a.m_to_time;
       return out;
}
