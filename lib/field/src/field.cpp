#include "field.h"

Field::Field(int width, int height)
{
    if (width < 0 || height < 0)
        throw FieldError();

    m_field.resize(height);
    for (auto & row : m_field)
    {
        row.resize(width);
        std::fill(row.begin(), row.end(), false);
    }
}

std::vector<bool> & Field::operator[](int index)
{
    return m_field[index];
}

FieldError::FieldError()
    : std::runtime_error("Incorrect field size\n") {}
