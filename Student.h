

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>

using namespace std;

class Student {
    public:
        Student();
        Student(string name, string level, string major, double gpa, int id);
        ~Student();

        void setName(string name) { m_name = name; };
        void setLevel(string level) { m_level = level; };
        void setMajor(string major) { m_major = major; };
        void setGPA(double gpa) { m_gpa = gpa; };
        void setAdvisor(int advisor) { m_advisor = advisor; };
        void setID(int id) { m_id = id; };

        string getName() { return m_name; };
        string getLevel() { return m_level; };
        string getMajor() { return m_major; };
        double getGPA() { return m_gpa; };
        int getAdvisor() { return m_advisor; };
        int getID() { return m_id; };

        friend bool operator< (const Student& s1, const Student& s2); // overloaded operators
        friend bool operator> (const Student& s1, const Student& s2);
        friend bool operator== (const Student& s1, const Student& s2);
        friend std::ostream& operator << (std::ostream& output, const Student& s1);
    private:
        string m_name;
        string m_level;
        string m_major;
        double m_gpa;
        int m_advisor;
        int m_id;

};

#endif