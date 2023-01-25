#ifndef LIFE_CELL_H
#define LIFE_CELL_H

#include <iostream>
#include <stdexcept>

struct Cell
{
    size_t m_x;
    size_t m_y;

    bool operator==(const Cell & cell) const;
    bool operator<(const Cell & cell) const;

    friend std::ostream & operator<<(std::ostream & os, Cell cell);
    friend std::istream & operator>>(std::istream & is, Cell & cell);
};

// Errors

class CellCoordinatesError : public std::runtime_error
{
public:
    CellCoordinatesError();
};

#endif // LIFE_CELL_H
