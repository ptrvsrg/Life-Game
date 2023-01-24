#include "abstract_mode.h"
#include "online_mode.h"
#include "offline_mode.h"

ModePtr AbstractMode::CreateMode(const std::string & input_file,
                                 const std::string & output_file,
                                 unsigned int iterations)
{
    if (!input_file.empty() && !output_file.empty() && iterations != -1)
        return ;
    else
        return ;
}
