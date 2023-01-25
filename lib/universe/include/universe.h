#ifndef LIFE_UNIVERSE_H
#define LIFE_UNIVERSE_H

#include <iostream>
#include <string>
#include <set>
#include "cell.h"

class Universe
{
public:
    Universe() = default;
    Universe(std::set<Cell> cells,
             size_t height,
             size_t width,
             std::string name,
             std::set<size_t> birth_rules,
             std::set<size_t> survival_rules);
    std::set<Cell> GetCells() const;
    std::string GetName() const;
    size_t GetHeight() const;
    size_t GetWidth() const;
    std::set<size_t> GetBirthRules() const;
    std::set<size_t> GetSurvivalRules() const;
    void GenerateNextGeneration();

private:
    std::set<Cell> m_cells;
    std::string m_name;
    size_t m_height = 0;
    size_t m_width = 0;
    std::set<size_t> m_birth_rules;
    std::set<size_t> m_survival_rules;

    size_t CountNeighbors(Cell cell);
};

#endif //LIFE_UNIVERSE_H
