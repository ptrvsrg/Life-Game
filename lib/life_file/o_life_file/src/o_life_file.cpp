#include "o_life_file.h"

static std::ostream & operator<<(std::ostream & os, const std::set<size_t> & set)
{
    for (size_t value : set)
        os << value;

    return os;
}

OLifeFile::OLifeFile(const std::string & file_name)
{
    // Open file
    m_fs.open(file_name, std::fstream::out);
    if (!m_fs.is_open())
        throw FileOpeningError();

    // Write file header
    WriteHeader();
}

void OLifeFile::WriteUniverse(const Universe & universe)
{
    // Write name
    m_fs << "#N " << universe.GetName() << std::endl;

    // Write size
    m_fs << "#S " << universe.GetHeight() << ' ' << universe.GetWidth() << std::endl;

    // Write rules
    m_fs << "#R B" << universe.GetBirthRules() << " S" << universe.GetSurvivalRules() << std::endl;

    // Write cells
    for (auto cell : universe.GetCells())
        m_fs << cell;
}

void OLifeFile::WriteHeader()
{
    m_fs << "#Life 1.06" << std::endl;
}
