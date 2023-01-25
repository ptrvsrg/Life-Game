#ifndef TASK2_LIFE_GAME_H
#define TASK2_LIFE_GAME_H

#include <string>

class Game
{
public:
    explicit Game(std::string input_file = "",
                  std::string output_file = "",
                  int iterations = 1);
    void Launch();

private:
    std::string m_input_file;
    std::string m_output_file;
    int m_iterations;
};

#endif //TASK2_LIFE_GAME_H
