#ifndef LIFE_FIELD_H
#define LIFE_FIELD_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include "cell.h"

class Field
{
public:
    explicit Field(int width = 0, int height = 0);
    int GetWidth() const;
    int GetHeight() const;
    std::vector<Cell> GetCells() const;
    int CountNeighbors(Cell cell) const;
    std::vector<bool> & operator[](size_t idx);

    friend std::ostream & operator<<(std::ostream & os, const Field & field);

private:
    std::vector<std::vector<bool>> m_data;
    int m_width;
    int m_height;
};

// Errors

class FieldSizeError : public std::runtime_error
{
public:
    FieldSizeError();
};

#endif //LIFE_FIELD_H
