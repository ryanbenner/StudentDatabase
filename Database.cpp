

#include "Database.h"
#include "Student.h"
#include "Faculty.h"
#include "FileProcessor.h"
#include "PQueue.h"
#include "LazyBST.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Database::Database() {
    m_students = new LazyBST<Student*>();
    m_faculty = new LazyBST<Faculty*>();
    m_allStudentIDs = new PQueue<int>(true);
    m_allFacultyIDs = new PQueue<int>(true);
}

Database::~Database() {
    delete m_students;
    delete m_faculty;
    delete m_allFacultyIDs;
    delete m_allStudentIDs;
}

void Database::exit() {
    // Fill this out
    // Create a fileprocessor.h
    // create a fileprocessor.cpp
    // this should print both printStudents() and printFaculty() to an output file
    FileProcessor fp;
    fp.writeToFile(*this, std::string("output.txt"));
}

void Database::displayMenu() {
    bool run = true;
    while (run) {
        cout << "1.	Print all students and their information (sorted by ascending id #)\n" <<
                "2.	Print all faculty and their information (sorted by ascending id #)\n" <<
                "3.	Find and display student information given the student id\n" <<
                "4.	Find and display faculty information given the faculty id\n" <<
                "5.	Add a new student\n" <<
                "6.	Delete a student given the id\n" <<
                "7.	Add a new faculty member\n" <<
                "8.	Delete a faculty member given the id.\n" <<
                "9.	Change a student's advisor given the student id and the new faculty id.\n" <<
                "10. Remove an advisee from a faculty member given the ids\n" <<
                "11. Exit" << endl;

        int input_selection;
        cin >> input_selection;
        while(std::cin.fail()) {
        std::cout << "Error, must input int" << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> input_selection;
    }
        switch (input_selection) {
            case 1: // done, theoretically
            {
                printStudents();
                break;
            }
            case 2: // done, theoretically
            {
                printFaculty();
                break;
            }
            case 3: // done
            {
                int stuID;
                cout << "\nPlease enter a student ID: ";
                cin >> stuID;
                Student* foundNode = findStudent(stuID);
                if (foundNode == NULL) {
                    cout << "Student not found!" << endl;
                    break;
                } else {
                    cout << "Student records found: " <<
                    "\nName: " << foundNode->getName() << 
                    "\nMajor: " << foundNode->getMajor() << 
                    "\nLevel: " << foundNode->getLevel() <<
                    "\nGPA: " << foundNode->getGPA() << 
                    "\nAdvisor ID: " << foundNode->getAdvisor() <<
                    "\nID Number: " << foundNode->getID() << endl;

                    break;
                }
            }
            case 4: // done
            {
                int facID;
                cout << "\nPlease enter a faculty ID: ";
                cin >> facID;
                Faculty* foundNode = findFaculty(facID);
                if (foundNode == NULL) {
                    break;
                } else {
                    cout << "Faculty records found: " <<
                    "\nName: " << foundNode->getName() << 
                    "\nLevel: " << foundNode->getLevel() <<
                    "\nID Number: " << foundNode->getID() << endl;
                    
                    break;
                }
            }
            case 5: // done
            {
                string name;
                cout << "\nPlease enter a name: ";
                cin >> name;

                string level;
                cout << "\nPlease enter a level: ";
                cin >> level;

                string major;
                cout << "\nPlease enter a major: ";
                cin >> major;

                double gpa;
                cout << "\nPlease enter a GPA: ";
                cin >> gpa;

                int id;
                cout << "\nPlease enter an id: ";
                cin >> id;
                if (m_faculty->getSize() != 0) {
                    m_allStudentIDs->add(id);
                    Student* tempStu = new Student(name, level, major, gpa, id);
                    addStudent(tempStu);
                    int facID = m_allFacultyIDs->get(rand() % m_allFacultyIDs->size());
                    tempStu->setAdvisor(facID);
                    Faculty* faculty = findFaculty(facID);
                    faculty->addStu(id);
                } else {
                    cout << "Error: Cannot add student, there are no faculty!" << endl << endl;
                }
                
                break;
            }
            case 6: // done
            {
                int id;
                cout << "\nPlease enter an id: ";
                cin >> id;
                Student* deletedStudent = deleteStudent(id);
                if (deletedStudent == NULL) {
                    break;
                } else {
                    cout << "\nStudent deleted!" << endl;
                    break;
                }
            }
            case 7:
            {
                string name;
                cout << "\nPlease enter a name: ";
                cin >> name;

                string level;
                cout << "\nPlease enter a level: ";
                cin >> level;

                int id;
                cout << "\nPlease enter an id: ";
                cin >> id;
                m_allFacultyIDs->add(id); // handle if student not found
                Faculty* tempFac = new Faculty(name, level, id);
                addFaculty(tempFac);
                break;
            }
            case 8: 
            {
                int id;
                cout << "\nPlease enter an id: " << endl;
                cin >> id;

                Faculty* deletedFaculty = deleteFaculty(id);
                if (deletedFaculty == NULL) {
                    cout << "\nFaculty not found!" << endl;
                    break;
                } else {
                    cout << "\nFaculty deleted!" << endl;
                    break;
                }
            }

            case 9:
            {
                int stuID;
                cout << "\nPlease enter a student ID: ";
                cin >> stuID;
                int facID;
                cout << "\nPlease enter a faculty ID: ";
                cin >> facID;
                changeStuAdvisor(stuID, facID);
                break;
            }

            case 10:
            {
                int stuID;
                cout << "\nPlease enter a student ID: ";
                cin >> stuID;
                int facID;
                cout << "\nPlease enter a faculty ID: ";
                cin >> facID;
                removeAdvisee(stuID, facID);
                break;
            }
            case 11:
                exit();
                run = false;
                break;
        }
    }
}

void Database::addFaculty(Faculty* fac) {
    m_faculty->insert(fac);
    // cout << "Faculty " << fac->getName() << " added!" << endl;
}

void Database::addStudent(Student* stu) {
    m_students->insert(stu);
}
Student* Database::deleteStudent(int id) {
    Student* targetStudent = new Student("", "", "", 0.0, id);
    Student* foundStudent = m_students->find(targetStudent);

    if (foundStudent != NULL) {
        m_students->remove(foundStudent);
        Faculty* targetFaculty = new Faculty("", "", foundStudent->getAdvisor());
        Faculty* foundFaculty = m_faculty->find(targetFaculty);
        targetFaculty->getStudentList()->remove(id);
        return foundStudent;
    } else {
        // Student not found
        return NULL;
    }
}

Faculty* Database::deleteFaculty(int id) {
    Faculty* targetFaculty = new Faculty("", "", id);
    Faculty* foundFaculty = m_faculty->find(targetFaculty);

    if (foundFaculty != NULL) {
        m_faculty->remove(foundFaculty);
        m_allFacultyIDs->removeData(id);
        for (int i = 0; i < foundFaculty->getStudentList()->getSize(); i++) {
            int stuID = foundFaculty->getStudentList()->get(i);
            Student* student = findStudent(stuID);
            student->setAdvisor(m_allFacultyIDs->get(rand() % m_allFacultyIDs->size()));
        }
        // need to move students
        return foundFaculty;
    } else {
        // Faculty not found
        return NULL;
    }
}

Student* Database::findStudent(int id) {
    Student* dummyStudent = new Student("", "", "", 0, id);
    Student* foundStudent= m_students->find(dummyStudent);

    if (foundStudent != NULL) {
        return foundStudent;
    } else {
        // Student not found
        cout << "Error: Student not found." << endl;
        return NULL;
    }
}

Faculty* Database::findFaculty(int id) {
    Faculty* targetFaculty = new Faculty("", "", id);
   Faculty* foundFaculty = m_faculty->find(targetFaculty);
    if (foundFaculty != NULL) {
        return foundFaculty;
    } else {
        // Faculty not found
        cout << "Error: Faculty not found." << endl;
        return NULL;
    }

}

void Database::changeStuAdvisor(int stuID, int facID) {
    Student* foundStudent = findStudent(stuID);
    Faculty* newFaculty = findFaculty(facID);
    if (foundStudent != NULL && newFaculty != NULL) {
        removeAdvisee(stuID, foundStudent->getAdvisor());
        foundStudent->setAdvisor(facID);
        newFaculty->addStu(stuID);
        cout << foundStudent->getName() << "'s advisor has been changed to " << newFaculty->getName() << ". " << endl;
    } else {
        cout << "Failed to change student advisor! Please check Student and Faculty IDs." << endl;
    }
}

void Database::removeAdvisee(int stuID, int facID) {
    Student* foundStudent = findStudent(stuID);
    Faculty* foundfaculty = findFaculty(facID);
    if (foundfaculty != NULL && foundStudent != NULL) {
        foundfaculty->getStudentList()->removeData(stuID);
        cout << "\nRemoved advisee. Warning: Student " <<  foundStudent->getName() << " does not have an advisor now." << endl;
    } else {
        cout << "Operation failed! Please check student and faculty ID numbers." << endl;
    }
}

void Database::printStudents() {
    cout << "\nStudent records found: " << endl;
    m_students->printTreeInOrder();
}

void Database::printFaculty() {
    cout << "\nFaculty records found: " << endl;
    m_faculty->printTreeInOrder();
}
