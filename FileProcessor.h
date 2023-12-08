

#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H
#include "Database.h"

class Database;

class FileProcessor {
public:
    static void writeToFile(Database& database, const std::string& filename); // writes output to file upon exiting
};

#endif
