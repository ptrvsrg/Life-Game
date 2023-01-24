#include "field.h"

Field::Field(int width, int height)
    : m_width(width),
      m_height(height)
{
    if (width < 0 || height < 0)
        throw FieldSizeError();

    m_data.resize(height);
    for (auto & row : m_data)
    {
        row.resize(width);
        std::fill(row.begin(), row.end(), false);
    }
}

int Field::GetWidth() const
{
    return m_width;
}

int Field::GetHeight() const
{
    return m_height;
}

std::vector<Cell> Field::GetCells() const
{
    std::vector<Cell> cells;
    for (int i = 0; i < m_height; ++i)
        for (int j = 0; j < m_width; ++j)
            if (m_data[i][j])
                cells.push_back({i, j});

    return cells;
}

int Field::CountNeighbors(Cell cell) const
{
    int neighbors = 0;
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (cell.m_y + i >= 0 && cell.m_y + i < m_height &&
                cell.m_x + j >= 0 && cell.m_x + j < m_width &&
                (i != 0 || j != 0))
                neighbors += m_data[cell.m_y + i][cell.m_x + j];

    return neighbors;
}

std::vector<bool> & Field::operator[](size_t idx)
{
    return m_data[idx];
}

std::ostream & operator<<(std::ostream & os, const Field & field)
{
    for (const auto & row : field.m_data)
    {
        for (bool cell : row)
            os << (cell ? '@' : '.') << ' ';

        os << std::endl;
    }

    return os;
}

FieldSizeError::FieldSizeError()
    : std::runtime_error("Incorrect field size\n") {}
