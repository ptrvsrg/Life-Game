#ifndef TASK2_LIFE_ONLINE_MODE_H
#define TASK2_LIFE_ONLINE_MODE_H

#include <string>
#include "abstract_mode.h"
#include "i_life_file.h"
#include "o_life_file.h"

class OnlineMode : public AbstractMode
{
public:
    explicit OnlineMode(std::string input_file);
    void Launch() override;

private:
    std::string m_input_file;
    Universe m_universe;

    void SetInputFile();
    void InitUniverse();
    void PrintGeneration();
    void SaveToFile(const std::string & output_file);
};

#endif //TASK2_LIFE_ONLINE_MODE_H
