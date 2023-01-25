#ifndef TASK2_LIFE_LIFE_FILE_BASE_H
#define TASK2_LIFE_LIFE_FILE_BASE_H

#include <fstream>
#include <stdexcept>

class LifeFileBase
{
protected:
    std::fstream m_fs;
};

class FileOpeningError : public std::runtime_error
{
public:
    FileOpeningError();
};

#endif //TASK2_LIFE_LIFE_FILE_BASE_H
