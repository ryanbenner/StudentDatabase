

#ifndef FACULTY_H
#define FACULTY_H

#include <string>
#include "DblList.h"

using namespace std;

class Faculty {
    public:
        Faculty();
        Faculty(string name, string level, int i);
        ~Faculty();
        void setName(string name) { m_name = name; };
        void setLevel(string level) { m_level = level; };
        void setID(int id) { m_id = id; };
        string getName() { return m_name; };
        string getLevel() { return m_level; };
        DblList<int>* getStudentList() { return m_students; };
        int getID() { return m_id; };
        void addStu(int id);

        friend bool operator< (const Faculty& s1, const Faculty& s2); // overloaded operators
        friend bool operator> (const Faculty& s1, const Faculty& s2);
        friend bool operator== (const Faculty& s1, const Faculty& s2);
        friend std::ostream& operator << (std::ostream& output, const Faculty& s1);
    private:
        int m_id;
        string m_name;
        string m_level;
        DblList<int>* m_students;
};

#endif