#include <gtest/gtest.h>
#include "cl_parser.h"

struct CommandLineParserArgs
{
    int m_argc;
    char ** m_argv;
    Options m_options;
    bool m_exception;
    bool m_return_value;

    CommandLineParserArgs(std::initializer_list<std::string> args,
                          Options options,
                          bool exception,
                          bool return_value)
    :   m_argc(static_cast<int>(args.size())),
        m_options(std::move(options)),
        m_exception(exception),
        m_return_value(return_value)
    {
        m_argv = new char * [m_argc];
        for (int i = 0; i < m_argc; ++i)
        {
            m_argv[i] = new char [(args.begin() + i)->size()];
            strcpy(m_argv[i],
                   (args.begin() + i)->data());
        }
    }
};

class CommandLineParserTest : public ::testing::TestWithParam<CommandLineParserArgs> {};
INSTANTIATE_TEST_SUITE_P
(
    test_parser,
    CommandLineParserTest,
    ::testing::Values
        (
            CommandLineParserArgs({"./main"},
                                  {"", "", -1},
                                  false,
                                  true),
            CommandLineParserArgs({"./main", "--input", "input_file"},
                                  {"input_file", "", -1},
                                  false,
                                  true),
            CommandLineParserArgs({"./main", "-I", "input_file"},
                                  {"input_file", "", -1},
                                  false,
                                  true),
            CommandLineParserArgs({"./main", "--output", "output_file"},
                                  {"", "output_file", -1},
                                  false,
                                  true),
            CommandLineParserArgs({"./main", "-o", "output_file"},
                                  {"", "output_file", -1},
                                  false,
                                  true),
            CommandLineParserArgs({"./main", "--iterations", "10"},
                                  {"", "", 10},
                                  false,
                                  true),
            CommandLineParserArgs({"./main", "--iterations", "-10"},
                                  {"", "", -10},
                                  true,
                                  false),
            CommandLineParserArgs({"./main", "--iterations", "0"},
                                  {"", "", 0},
                                  false,
                                  true),
            CommandLineParserArgs({"./main", "-i", "10"},
                                  {"", "", 10},
                                  false,
                                  true),
            CommandLineParserArgs({"./main", "--help"},
                                  {"", "", -1},
                                  false,
                                  false),
            CommandLineParserArgs({"./main", "-h"},
                                  {"", "", -1},
                                  false,
                                  false),
            CommandLineParserArgs({"./main", "-r"},
                                  {"", "", -1},
                                  true,
                                  false),
            CommandLineParserArgs({"./main", "--config"},
                                  {"", "", -1},
                                  true,
                                  false)
        )
);

TEST_P(CommandLineParserTest,
       check_options)
{
    CommandLineParserArgs params = GetParam();
    Options opts;

    if (params.m_exception)
    {
        EXPECT_ANY_THROW
        (
            {
                GetOptions(params.m_argc,
                           params.m_argv,
                           opts);
            }
        );
    }
    else
    {
        EXPECT_EQ(GetOptions(params.m_argc,
                             params.m_argv,
                             opts),
                  params.m_return_value);
        EXPECT_EQ(opts.m_input_file,
                  params.m_options.m_input_file);
        EXPECT_EQ(opts.m_output_file,
                  params.m_options.m_output_file);
        EXPECT_EQ(opts.m_iterations,
                  params.m_options.m_iterations);
    }
}

int main(int argc,
         char** argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}