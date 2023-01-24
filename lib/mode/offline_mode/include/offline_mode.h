#ifndef TASK2_LIFE_OFFLINE_MODE_H
#define TASK2_LIFE_OFFLINE_MODE_H

#include <string>
#include "abstract_mode.h"
//#include "life_file.h"

class OfflineMode : public AbstractMode
{
public:
    explicit OfflineMode(std::string input_file);
    void Launch() override;

private:
    std::string m_input_file;

    void SetInputFile();
//    Universe CreateUniverse();
//    void PrintGeneration(Universe & universe);
    void PrintHelp();
    void PrintWarning();
    void SaveToFile();
};

#endif //TASK2_LIFE_OFFLINE_MODE_H
