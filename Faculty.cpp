

#include "Faculty.h"
#include "DblList.h"
#include <string>

using namespace std;

Faculty::Faculty() {
    m_name = "John Doe";
    m_level = "Professor";
    m_id = 1;
    m_students = new DblList<int>();
}

Faculty::Faculty(string name, string level, int id) {
    m_name = name;
    m_level = level;
    m_id = id;
    m_students = new DblList<int>();
}

Faculty::~Faculty() {
    delete m_students;
}

bool operator > (const Faculty &f1, const Faculty &f2) {

    return f1.m_id > f2.m_id;
}

bool operator < (const Faculty &f1, const Faculty &f2) {

    return f1.m_id < f2.m_id;
}

bool operator == (const Faculty &f1, const Faculty &f2) {
    return f1.m_id == f2.m_id;
}

std::ostream& operator << (std::ostream& output, const Faculty& f1) {
    output << "\nName: " << f1.m_name << "\nLevel: " << f1.m_level << "\nID: " << f1.m_id << endl;
}

void Faculty::addStu(int id) {
    m_students->addBack(id);
}