#include "universe.h"

Universe::Universe(std::set<Cell> cells,
                   size_t height,
                   size_t width,
                   std::string name,
                   std::set<size_t> birth_rules,
                   std::set<size_t> survival_rules)
    : m_cells(std::move(cells)),
      m_height(height),
      m_width(width),
      m_name(std::move(name)),
      m_birth_rules(std::move(birth_rules)),
      m_survival_rules(std::move(survival_rules)) {}

std::set<Cell> Universe::GetCells() const
{
    return m_cells;
}

std::string Universe::GetName() const
{
    return m_name;
}

size_t Universe::GetHeight() const
{
    return m_height;
}

size_t Universe::GetWidth() const
{
    return m_width;
}

std::set<size_t> Universe::GetBirthRules() const
{
    return m_birth_rules;
}

std::set<size_t> Universe::GetSurvivalRules() const
{
    return m_survival_rules;
}

void Universe::GenerateNextGeneration()
{
    // Set of updated cells
    std::set<Cell> updated_cells = m_cells;

    for (size_t i = 0; i < m_height; ++i)
        for (size_t j = 0; j < m_width; ++j)
        {
            Cell cell = {j, i};

            // Count neighbors
            size_t neighbors = CountNeighbors(cell);

            // Case: cell will die
            if (m_cells.find(cell) != m_cells.end()
                && m_survival_rules.find(neighbors) == m_survival_rules.end())
                updated_cells.erase(cell);

            // Case: cell will be born
            if (m_cells.find(cell) == m_cells.end()
                && m_birth_rules.find(neighbors) != m_birth_rules.end())
                updated_cells.insert(cell);
        }

    m_cells = updated_cells;
}

size_t Universe::CountNeighbors(Cell cell)
{
    size_t neighbors = 0;
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j)
            if (i != 0 || j != 0)
            {
                Cell neighbour_cell = {
                    (cell.m_x + m_width + i) % m_width,
                    (cell.m_y + m_height + j) % m_height,
                };

                if (m_cells.find(neighbour_cell) != m_cells.end())
                    ++neighbors;
            }

    return neighbors;
}
