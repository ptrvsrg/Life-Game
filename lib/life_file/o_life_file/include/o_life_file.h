#ifndef TASK2_LIFE_O_LIFE_FILE_H
#define TASK2_LIFE_O_LIFE_FILE_H

#include <fstream>
#include <string>
#include "life_file_base.h"
#include "universe.h"

class OLifeFile : virtual LifeFileBase
{
public:
    OLifeFile() = default;
    explicit OLifeFile(const std::string & file_name);
    void WriteUniverse(const Universe & universe);

private:
    void WriteHeader();
};

#endif //TASK2_LIFE_O_LIFE_FILE_H
