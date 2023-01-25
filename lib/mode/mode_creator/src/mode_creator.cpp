#include "abstract_mode.h"
#include "online_mode.h"
#include "offline_mode.h"

ModePtr AbstractMode::CreateMode(const std::string & input_file,
                                 const std::string & output_file,
                                 int iterations)
{
    if (!input_file.empty() && !output_file.empty() && iterations != -1)
        return std::make_unique<OfflineMode>(input_file, output_file, iterations);
    else
    {
        // Warnings
        if (!output_file.empty() || iterations != -1)
            std::clog << "Warnings: There are not enough parameters to start offline mode\n";

        return std::make_unique<OnlineMode>(input_file);
    }
}
