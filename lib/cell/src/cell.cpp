#include "cell.h"

std::ostream & operator<<(std::ostream & os, Cell cell)
{
    os << cell.m_x << " " << cell.m_y << std::endl;
    return os;
}

std::istream & operator>>(std::istream & is, Cell & cell)
{
    std::ios_base::iostate state = is.exceptions();
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

    is.exceptions(state);

    return is;
}

CellCoordinatesError::CellCoordinatesError()
    : std::runtime_error("Incorrect cell coordinates\n") {}