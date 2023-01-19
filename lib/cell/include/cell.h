#ifndef LIFE_CELL_H
#define LIFE_CELL_H

#include <iostream>
#include <stdexcept>

struct Cell
{
    int m_x = 0;
    int m_y = 0;

    friend std::ostream & operator<<(std::ostream & os, Cell cell);
    friend std::istream & operator>>(std::istream & is, Cell & cell);
};

// Errors

class CellError : public std::runtime_error
{
public:
    CellError();
};

#endif // LIFE_CELL_H
