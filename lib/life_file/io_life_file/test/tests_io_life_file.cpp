#include <gtest/gtest.h>
#include "io_life_file.h"

TEST(test_io_life_file, check_input_output)
{
    {
        LifeFile i_life_file("files/example.life", LifeFile::Mode::IN);
        Universe universe = i_life_file.ReadUniverse();

        LifeFile o_life_file("files/copy_example.life", LifeFile::Mode::OUT);
        o_life_file.WriteUniverse(universe);
    }

    std::fstream example_ifs("files/example.life");
    std::fstream copy_ifs("files/copy_example.life");

    while (!example_ifs.eof() || !copy_ifs.eof())
    {
        std::string example_line;
        std::string copy_line;

        std::getline(example_ifs, example_line);
        std::getline(copy_ifs, copy_line);

        EXPECT_EQ(example_line,
                  copy_line);
    }
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}