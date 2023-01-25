#include <iostream>
#include "cl_parser.h"
#include "game.h"

int main(int argc, char ** argv)
{
    try
    {
        Options opts;
        GetOptions(argc, argv, opts);

        Game game(opts.m_input_file,
                  opts.m_output_file,
                  opts.m_iterations);
        game.Launch();
    }
    catch (const std::exception & ex)
    {
        std::cerr << ex.what();
    }

    return EXIT_SUCCESS;
}