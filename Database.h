

#ifndef DATABASE_H
#define DATABASE_H
#include "Student.h"
#include "Faculty.h"
#include "FileProcessor.h"
#include "PQueue.h"
#include "LazyBST.h"

class Student;
class Faculty;

template<typename T>
class LazyBST;

class Database {
    public:
        Database(); //constructor
        ~Database(); // destrucotr

        void displayMenu(); // displays switch case

        void addStudent(Student* stu); // adds student to BST
        void addFaculty(Faculty* fac); // adds faculty to BST
        void printStudents(); // prints students
        void printFaculty(); // prints faculty
        Student* findStudent(int id); // finds a student in BST based on ID
        Faculty* findFaculty(int id); // finds a faculty in BST based on ID
        Student* deleteStudent(int id); // deletes a student from BST based on ID
        Faculty* deleteFaculty(int id); // deletes a faculty from BST based on ID
        void changeStuAdvisor(int studentID, int facultyID); // changes a student advisor based on student ID and fac ID
        void removeAdvisee(int studentID, int facultyID); // removes an advisee, if that stu ID is in facID's list
        void exit(); // exits, prints students and faculty to file
        void printStudentsToFile(std::ostream& os) const; // prints students to file
        void printFacultyToFile(std::ostream& os) const; // prints faculty to file
        

    private:
        LazyBST<Student*>* m_students; // holds student objects
        LazyBST<Faculty*>* m_faculty; // holds faculty objects
        PQueue<int>* m_allStudentIDs; // holds student ids
        PQueue<int>* m_allFacultyIDs; // holds faculty ids

        friend class FileProcessor;
};

#endif