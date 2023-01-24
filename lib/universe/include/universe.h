#ifndef LIFE_UNIVERSE_H
#define LIFE_UNIVERSE_H

#include <iostream>
#include <string>
#include <set>
#include "field.h"

class Universe
{
public:
    Universe() = default;
    explicit Universe(Field field,
                      std::string name = "My Universe",
                      std::set<int> birth_count = std::set<int>({ 3 }),
                      std::set<int> survival_count = std::set<int>({ 2, 3 }));
    Field GetField() const;
    std::string GetName() const;
    std::set<int> GetBirthCount() const;
    std::set<int> GetSurvivalCount() const;
    void GenerateNextGeneration();

    friend std::ostream & operator<<(std::ostream & os, const Universe & universe);

private:
    Field m_field;
    std::string m_name;
    std::set<int> m_birth_count;
    std::set<int> m_survival_count;
    int m_generation_num = 1;
};

#endif //LIFE_UNIVERSE_H
