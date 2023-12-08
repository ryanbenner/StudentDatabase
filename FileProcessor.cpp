

#include "FileProcessor.h"
#include "Database.h"
#include <fstream>

void FileProcessor::writeToFile(Database& database, const std::string& filename) {
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    // Write student information
    outFile << "Student Records:\n";
    database.m_students->printTreeInOrderToFile(outFile);

    // Write faculty information
    outFile << "\nFaculty Records:\n";
    database.m_faculty->printTreeInOrderToFile(outFile);

    outFile.close();
}
