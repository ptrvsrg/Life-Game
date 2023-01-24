#include "i_life_file.h"
#include <iostream>
#include <regex>
#include <set>
#include <sstream>

ILifeFile::ILifeFile(const std::string & file_name)
{
    this->Open(file_name);
}

void ILifeFile::Open(const std::string & file_name)
{
    // Open file
    m_fs.open(file_name, std::fstream::in);

    // Check file header
    CheckHeader();
}

Universe ILifeFile::ReadUniverse()
{
    std::string name;
    int width = -1;
    int height = -1;
    std::set<int> birth_count;
    std::set<int> survival_count;

    while (true)
    {
        // Remember ifstream current position
        size_t pos = m_fs.tellg();

        // Read line from file stream
        std::string info_line;
        std::getline(m_fs, info_line);

        if (std::regex_search(info_line, std::regex("#N ")))
            // Set universe name
            name = std::regex_replace(info_line, std::regex("#N "), "");
        else if (std::regex_search(info_line, std::regex("#S ")))
        {
            std::istringstream iss(std::regex_replace(info_line, std::regex("#S "), ""));

            // Enable throwing exceptions on errors
            iss.exceptions(std::stringstream::failbit);

            try
            {
                // Set width or size
                iss >> width;

                // Case: only size is set
                if (iss.eof())
                    height = width;
                else
                    iss >> height;
            }
            catch (const std::ios_base::failure & ex)
            {
                throw FieldSizeError();
            }
        }
        else if (std::regex_search(info_line, std::regex("#R ")))
        {
            std::string digit_sequence;
            std::smatch smatch;

            // Set birth count
            if (std::regex_search(info_line, smatch, std::regex("(B)(\\S*)")))
            {
                digit_sequence = std::regex_replace(smatch[0].str(), std::regex("B"), "");
                for (char digit : digit_sequence)
                {
                    if (!std::isdigit(digit))
                        throw DigitSetError();
                    birth_count.insert(digit - '0');
                }
            }

            // Set survival count
            if (std::regex_search(info_line, smatch, std::regex("(S)(\\S*)")))
            {
                digit_sequence = std::regex_replace(smatch[0].str(), std::regex("S"), "");
                for (char digit : digit_sequence)
                {
                    if (!std::isdigit(digit))
                        throw DigitSetError();
                    survival_count.insert(digit - '0');
                }
            }
        }
        else
        {
            // Return position before reading
            m_fs.seekg(pos);
            break;
        }
    }

    // Print warnings
    if (name.empty())
        std::clog << "Warning: Universe name is missing, "
                     "it will be set by default \"My Universe\"\n";
    if (birth_count.empty())
        std::clog << "Warning: Number of live cells for birth is missing, "
                     "it will be set by default \"3\"\n";
    if (survival_count.empty())
        std::clog << "Warning: Number of live cells for survival is missing, "
                     "it will be set by default \"23\"\n";

    Field field = ReadField(width, height);
    Universe universe(field,
                      name,
                      birth_count,
                      survival_count);
    return universe;
}

void ILifeFile::CheckHeader()
{
    // Read line from file stream
    std::string info_line;
    std::getline(m_fs, info_line);

    // Incorrect file format
    if (info_line != "#Life 1.06")
        throw FileFormatError();
}

Field ILifeFile::ReadField(int width, int height)
{
    // Create field
    Field field(width, height);

    while (true)
    {
        // Read line from file stream
        std::string info_line;
        std::getline(m_fs, info_line);

        // End of file
        if (info_line.empty())
            break;

        // Only comment
        if (std::regex_match(info_line, std::regex("^#.*")))
            continue;

        // Remove comment
        std::smatch smatch;
        if (std::regex_search(info_line, smatch, std::regex("^[^#]*")))
            info_line = smatch[0].str();

        std::istringstream iss(info_line);
        Cell cell;
        iss >> cell;

        // Case: negative coordinates
        if (cell.m_x < 0 || cell.m_y < 0)
            throw CellCoordinatesError();

        // Set cell in field
        field[cell.m_y][cell.m_x] = true;
    }

    return field;
}

FileFormatError::FileFormatError()
    : std::runtime_error("Incorrect file format\n") {}

DigitSetError::DigitSetError()
    : std::runtime_error("Incorrect digit set\n") {}