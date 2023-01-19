#ifndef LIFE_LIFE_FILE_H
#define LIFE_LIFE_FILE_H

#include <fstream>
#include <set>
#include <stdexcept>
#include <string>
#include "cell.h"
#include "field.h"
#include "universe.h"

class LifeFile
{
public:
    explicit LifeFile(const std::string & file_name);
    Universe InitUniverse();

private:
    std::ifstream m_ifs;
    std::string m_name;
    int m_width = -1;
    int m_height = -1;
    std::set<int> m_birth_count;
    std::set<int> m_survival_count;
    Field m_field;

    void CheckHeader();
    void FillField();
};

// Errors

class FileFormatError : public std::runtime_error
{
public:
    FileFormatError();
};

class DigitSetError : public std::runtime_error
{
public:
    DigitSetError();
};

#endif // LIFE_LIFE_FILE_H
