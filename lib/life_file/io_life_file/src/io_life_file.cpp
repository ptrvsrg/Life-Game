#include "io_life_file.h"

LifeFile::LifeFile(const std::string & file_name, LifeFile::Mode mode)
    : ILifeFile(), OLifeFile()
{
    switch (mode)
    {
        case IN:
            this->ILifeFile::Open(file_name);
            break;
        case OUT:
            this->OLifeFile::Open(file_name);
            break;
    }
}
