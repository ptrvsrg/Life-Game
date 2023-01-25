#ifndef TASK2_LIFE_OFFLINE_MODE_H
#define TASK2_LIFE_OFFLINE_MODE_H

#include <string>
#include "abstract_mode.h"
#include "i_life_file.h"
#include "o_life_file.h"

class OfflineMode : public AbstractMode
{
public:
    explicit OfflineMode(std::string input_file,
                         std::string output_file,
                         size_t iterations);
    void Launch() override;

private:
    std::string m_input_file;
    std::string m_output_file;
    size_t m_iterations;
    Universe m_universe;

    void InitUniverse();
    void SaveToFile();
};

#endif //TASK2_LIFE_OFFLINE_MODE_H
