#include "cell.h"

std::ostream & operator<<(std::ostream & os, Cell cell)
{
    os << cell.m_x << " " << cell.m_y;
    return os;
}

std::istream & operator>>(std::istream & is, Cell & cell)
{
    is >> cell.m_x;
    is >> cell.m_y;

    return is;
}

CellError::CellError()
    : std::runtime_error("Incorrect cell coordinates\n") {}