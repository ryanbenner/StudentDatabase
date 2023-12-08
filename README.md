# StudentDatabase
This project is a mock database utilizing a self-balancing Binary Search Tree to compare and organize Student and Faculty objects, by their respective ID numbers. Referential Integrity is ensured (i.e. a Student cannot have an Advisor that does not exist).

## Identifying Info:
    a. Ryan Benner
    b. rdbenner4@gmail.com

## Source Files Submitted:
    - ListNode.h
    - DblList.h
    - PQueue.h
    - LazyBST.h
    - Database.h
    - Database.cpp
    - Student.h
    - Student.cpp
    - Faculty.h
    - Faculty.cpp
    - FileProcessor.h
    - FileProcessor.cpp
    - main.cpp
    - output.txt

## Limitations/Errors:
    cannot put a space in between Name field when creating student
    nothing to handle if a faculty has maximum students in dblList

## Compilation Instructions:
    g++ -o test *.cpp
    ./test


