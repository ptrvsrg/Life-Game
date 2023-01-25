#ifndef TASK2_LIFE_MODE_INTERFACE_H
#define TASK2_LIFE_MODE_INTERFACE_H

#include <memory>
#include <string>

class AbstractMode;
using ModePtr = std::unique_ptr<AbstractMode>;

class AbstractMode
{
public:
    virtual void Launch() = 0;
    static ModePtr CreateMode(const std::string & input_file,
                              const std::string & output_file,
                              int iterations);
};

#endif //TASK2_LIFE_MODE_INTERFACE_H