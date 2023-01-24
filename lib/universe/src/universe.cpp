#include "universe.h"

Universe::Universe(Field field,
                   std::string name,
                   std::set<int> birth_count,
                   std::set<int> survival_count)
    : m_field(std::move(field)),
      m_name(std::move(name)),
      m_birth_count(std::move(birth_count)),
      m_survival_count(std::move(survival_count)) {}

Field Universe::GetField() const
{
    return m_field;
}

std::string Universe::GetName() const
{
    return m_name;
}

std::set<int> Universe::GetBirthCount() const
{
    return m_birth_count;
}

std::set<int> Universe::GetSurvivalCount() const
{
    return m_survival_count;
}

void Universe::GenerateNextGeneration()
{
    Field field(m_field.GetWidth(), m_field.GetHeight());
    ++m_generation_num;
    for (int i = 0; i < m_field.GetHeight(); ++i)
        for (int j = 0; j < m_field.GetWidth(); ++j)
        {
            field[i][j] = m_field[i][j];

            int live_neighbors = m_field.CountNeighbors({j, i});
            if (m_field[i][j] && m_survival_count.find(live_neighbors) == m_survival_count.end())
                field[i][j] = false;
            if (!m_field[i][j] && m_birth_count.find(live_neighbors) != m_birth_count.end())
                field[i][j] = true;
        }

    m_field = field;
}

std::ostream & operator<<(std::ostream & os, const Universe & universe)
{
    os << "Name: " << universe.m_name << std::endl;
    os << "Generation: " << universe.m_generation_num << std::endl;
    os << universe.m_field;

    return os;
}
