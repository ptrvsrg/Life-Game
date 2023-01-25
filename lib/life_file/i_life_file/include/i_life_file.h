#ifndef TASK2_LIFE_I_LIFE_FILE_H
#define TASK2_LIFE_I_LIFE_FILE_H

#include <fstream>
#include <stdexcept>
#include <string>
#include "life_file_base.h"
#include "universe.h"

class ILifeFile : virtual LifeFileBase
{
public:
    ILifeFile() = default;
    explicit ILifeFile(const std::string & file_name);
    Universe ReadUniverse();

private:
    void CheckHeader();
    std::set<Cell> ReadCells();
};

// Errors

class FileFormatError : public std::runtime_error
{
public:
    FileFormatError();
};

class FieldSizeError : public std::runtime_error
{
public:
    FieldSizeError();
};

class DigitSetError : public std::runtime_error
{
public:
    DigitSetError();
};

#endif //TASK2_LIFE_I_LIFE_FILE_H
