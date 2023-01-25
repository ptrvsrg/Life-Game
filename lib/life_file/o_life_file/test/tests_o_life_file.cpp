#include <gtest/gtest.h>
#include "o_life_file.h"
#include <sstream>

TEST(test_o_life_file, check)
{
    Universe universe({ {0, 0}, {1, 1}, {2, 2} },
                      10,
                      10,
                      "Check",
                      {1, 2, 3},
                      {4, 5, 6});

    // Create output life file
    {
        OLifeFile o_life_file("files/output.life");
        o_life_file.WriteUniverse(universe);
    }

    // Read life file to string stream
    std::ostringstream oss;
    std::ifstream ifs;
    ifs.open("files/output.life");

    while (!ifs.eof())
    {
        char sym;
        ifs.read(&sym, 1);
        oss << sym;
    }

    EXPECT_EQ(oss.str(),
              "#Life 1.06\n"
              "#N Check\n"
              "#S 10 10\n"
              "#R B123 S456\n"
              "0 0\n"
              "1 1\n"
              "2 2\n\n");
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}