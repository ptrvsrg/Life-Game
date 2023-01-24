#include "cl_parser.h"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

bool GetOptions(int argc,
                char ** argv,
                Options & opts)
{
    // add necessary options
    po::options_description opts_desc("General options");
    opts_desc.add_options()
        ("help,h",
         "Show options description")
        ("input,I",
         po::value<std::string>(&opts.m_input_file),
         "Input files")
        ("output,o",
         po::value<std::string>(&opts.m_output_file),
         "Output file")
        ("iterations,i",
         po::value<int>(&opts.m_iterations)->notifier(
             [](int x)
             {
                 if (x < 0)
                     throw po::validation_error(po::validation_error::invalid_option_value);
             }
         ),
         "Iteration count");

    // parse command line arguments
    po::variables_map vm;
    po::parsed_options pars_opts = po::command_line_parser(argc,
                                                           argv)
        .options(opts_desc)
        .run();
    store(pars_opts,
          vm);

    // print help
    if (vm.count("help"))
    {
        std::cout << opts_desc << std::endl;
        return false;
    }

    notify(vm);
    return true;
}