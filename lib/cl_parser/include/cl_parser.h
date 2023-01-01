#ifndef LIFE_CL_PARSER_H
#define LIFE_CL_PARSER_H

#include <string>

struct Options
{
    std::string m_input_file;
    std::string m_output_file;
    int m_iterations = 0;

    Options() = default;
};

bool GetOptions(int argc,
                char ** argv,
                Options & opts);

#endif // LIFE_CL_PARSER_H
