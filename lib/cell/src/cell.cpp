#include "cell.h"

bool Cell::operator==(const Cell & cell) const
{
    return (m_x == cell.m_x) && (m_y == cell.m_y);
}

bool Cell::operator<(const Cell & cell) const
{
    // Case: x coordinates are equal
    if (m_x == cell.m_x)
        return m_y < cell.m_y;

    return m_x < cell.m_x;
}

std::ostream & operator<<(std::ostream & os, Cell cell)
{
    os << cell.m_x << " " << cell.m_y << std::endl;
    return os;
}

std::istream & operator>>(std::istream & is, Cell & cell)
{
    // Remember previous exception state
    std::ios_base::iostate state = is.exceptions();

    // Enable throwing exceptions on errors
    is.exceptions(std::ios_base::failbit);

    try
    {
        is >> cell.m_x;
        is >> cell.m_y;
    }
    catch (const std::ios_base::failure & ex)
    {
        throw CellCoordinatesError();
    }

    // Set back previous exception state
    is.exceptions(state);

    return is;
}

CellCoordinatesError::CellCoordinatesError()
    : std::runtime_error("Incorrect cell coordinates\n") {}