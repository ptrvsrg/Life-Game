#include "life_file.h"
#include <cctype>
#include <iostream>
#include <regex>
#include <sstream>

LifeFile::LifeFile(const std::string & file_name)
{
    // Open file
    m_ifs.open(file_name);

    CheckHeader();
    FillField();
}

Universe LifeFile::InitUniverse()
{
    return {m_field,
            m_name,
            m_birth_count,
            m_survival_count};
}

void LifeFile::CheckHeader()
{
    // Read line from file stream
    std::string info_line;
    std::getline(m_ifs, info_line);

    // Incorrect file format
    if (info_line != "#Life 1.06")
        throw FileFormatError();

    while (true)
    {
        // Clear info line
        info_line.clear();

        // Remember ifstream current position
        size_t pos = m_ifs.tellg();

        // Read line from file stream
        std::getline(m_ifs, info_line);

        if (std::regex_search(info_line, std::regex("#N")))
            // Set universe name
            m_name = std::regex_replace(info_line, std::regex("#N"), "");
        else if (std::regex_search(info_line, std::regex("#S")))
        {
            std::istringstream iss(std::regex_replace(info_line, std::regex("#S"), ""));

            // Enable throwing exceptions on errors
            iss.exceptions(std::stringstream::failbit);

            try
            {
                // Set width or size
                iss >> m_width;

                // Case: only size is set
                if (!iss.eof())
                    iss >> m_height;
                else
                    m_height = m_width;
            }
            catch (const std::ios_base::failure & ex)
            {
                throw FieldError();
            }
        }
        else if (std::regex_search(info_line, std::regex("#R")))
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
                    m_birth_count.insert(digit - '0');
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
                    m_survival_count.insert(digit - '0');
                }
            }
        }
        else
        {
            // Return position before reading
            m_ifs.seekg(pos);
            break;
        }
    }

    // Warnings
    if (m_name.empty())
        std::cout << "Warning: Universe name is missing, it will be set by default \"My Universe\"\n";
    if (m_birth_count.empty())
        std::cout << "Warning: Number of live cells for birth is missing, it will be set by default \"3\"\n";
    if (m_survival_count.empty())
        std::cout << "Warning: Number of live cells for survival is missing, it will be set by default \"23\"\n";
}

void LifeFile::FillField()
{
    // Create field
    m_field = Field(m_width, m_height);

    while (true)
    {
        // Read line from file stream
        std::string info_line;
        std::getline(m_ifs, info_line);

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

        // Enable throwing exceptions on errors
        iss.exceptions(std::stringstream::failbit);

        try
        {
            iss >> cell;
        }
        catch (const std::ios_base::failure & ex)
        {
            throw CellError();
        }

        // Case: negative coordinates
        if (cell.m_x < 0 || cell.m_y < 0)
            throw CellError();

        // Set cell in field
        m_field[cell.m_y][cell.m_x] = true;
    }
}

FileFormatError::FileFormatError()
    : std::runtime_error("Incorrect file format\n") {}

DigitSetError::DigitSetError()
    : std::runtime_error("Incorrect digit set\n") {}
