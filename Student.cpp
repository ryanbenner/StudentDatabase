

#include "Student.h"
#include <string>
#include <iostream>

using namespace std;

Student::Student() {
    m_major = "Computer Science";
    m_gpa = 3.0;
    m_advisor;
    m_id;
}

Student::Student(string name, string level, string major, double gpa, int id) {
    m_name = name;
    m_level = level;
    m_major = major;
    m_gpa = gpa;
    m_id = id;
}

Student::~Student() {

}

bool operator > (const Student &s1, const Student &s2) {

    return s1.m_id > s2.m_id;
}

bool operator < (const Student &s1, const Student &s2) {

    return s1.m_id < s2.m_id;
}

bool operator == (const Student &s1, const Student &s2) {

    return s1.m_id == s2.m_id;
}

std::ostream& operator << (std::ostream& output, const Student& s1) {
    output << "\nName: " << s1.m_name << "\nMajor: " << s1.m_major << "\nLevel: " << s1.m_level << "\nGPA: " << s1.m_gpa << "\nAdvisor ID: " << s1.m_advisor << "\nID: " << s1.m_id << endl;
}