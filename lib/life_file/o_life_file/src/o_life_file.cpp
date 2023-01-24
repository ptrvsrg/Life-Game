#include "o_life_file.h"

static std::ostream & operator<<(std::ostream & os, const std::set<int> & set)
{
    for (int value : set)
        os << value;

    return os;
}

OLifeFile::OLifeFile(const std::string & file_name)
{
    this->Open(file_name);
}

void OLifeFile::Open(const std::string & file_name)
{
    // Open file
    m_fs.open(file_name, std::fstream::out);

    // Write file header
    WriteHeader();
}

void OLifeFile::WriteUniverse(const Universe & universe)
{
    // Write name
    m_fs << "#N " << universe.GetName() << std::endl;

    // Write rules
    m_fs << "#R B" << universe.GetBirthCount() << " S" << universe.GetSurvivalCount() << std::endl;

    // Write size
    Field field = universe.GetField();
    m_fs << "#S " << field.GetWidth() << " " << field.GetHeight() << std::endl;

    // Write cells
    for (auto cell : field.GetCells())
        m_fs << cell;
}

void OLifeFile::WriteHeader()
{
    m_fs << "#Life 1.06" << std::endl;
}
