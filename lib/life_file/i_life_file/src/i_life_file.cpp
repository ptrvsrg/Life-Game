#include "i_life_file.h"
#include <iostream>
#include <regex>
#include <set>
#include <sstream>

ILifeFile::ILifeFile(const std::string & file_name)
{
    // Open file
    m_fs.open(file_name, std::fstream::in);
    if (!m_fs.is_open())
        throw FileOpeningError();

    // Check file header
    CheckHeader();
}

Universe ILifeFile::ReadUniverse()
{
    // Default values
    std::string name = "My Universe";
    size_t height = 0;
    size_t width = 0;
    std::set<size_t> birth_rules{ 3 };
    std::set<size_t> survival_rules{ 2, 3 };

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
        else if (std::regex_search(info_line, std::regex("#S")))
        {
            std::istringstream iss(std::regex_replace(info_line, std::regex("#S "), ""));

            // Enable throwing exceptions on errors
            iss.exceptions(std::stringstream::failbit);

            try
            {
                // Set width or size
                iss >> height;
                iss >> width;
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
                    birth_rules.insert(digit - '0');
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
                    survival_rules.insert(digit - '0');
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
    if (birth_rules.empty())
        std::clog << "Warning: Number of live cells for birth is missing, "
                     "it will be set by default \"3\"\n";
    if (survival_rules.empty())
        std::clog << "Warning: Number of live cells for survival is missing, "
                     "it will be set by default \"23\"\n";

    return Universe(ReadCells(),
                    height,
                    width,
                    name,
                    birth_rules,
                    survival_rules);
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

std::set<Cell> ILifeFile::ReadCells()
{
    std::set<Cell> cells;
    while (true)
    {
        // Read line from file stream
        std::string info_line;
        std::getline(m_fs, info_line);

        // End of file
        if (info_line.empty() && m_fs.eof())
            break;

        // Only comment
        if (std::regex_match(info_line, std::regex("^#.*")))
            continue;

        // Remove comment
        std::smatch smatch;
        if (std::regex_search(info_line, smatch, std::regex("^[^#]*")))
            info_line = smatch[0].str();

        // Read cell
        std::istringstream iss(info_line);
        Cell cell{};
        iss >> cell;

        // Warning
        if (cells.find(cell) != cells.end())
            std::clog << "Warning: Duplicate coordinate detected, "
                         "it will be deleted\n";

        // Insert cell
        cells.insert(cell);
    }

    return cells;
}

FileFormatError::FileFormatError()
    : std::runtime_error("Incorrect file format\n") {}

FieldSizeError::FieldSizeError()
    : std::runtime_error("Incorrect field size\n") {}

DigitSetError::DigitSetError()
    : std::runtime_error("Incorrect digit set\n") {}
