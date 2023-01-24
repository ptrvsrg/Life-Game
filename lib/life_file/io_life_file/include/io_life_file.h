#ifndef LIFE_LIFE_FILE_H
#define LIFE_LIFE_FILE_H

#include "i_life_file.h"
#include "o_life_file.h"

class LifeFile : public ILifeFile,
                 public OLifeFile
{
public:
    enum Mode
    {
        IN,
        OUT
    };

    explicit LifeFile(const std::string & file_name,
                      Mode mode);
};

#endif // LIFE_LIFE_FILE_H
