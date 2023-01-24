#include <gtest/gtest.h>
#include "universe.h"

TEST(tests_universe, check_print)
{
    Field field(3, 3);
    Universe universe(field);

    std::ostringstream oss;
    oss << universe;

    EXPECT_EQ(oss.str(),
              "Name: My Universe\n"
              "Generation: 1\n"
              ". . . \n"
              ". . . \n"
              ". . . \n");
}

TEST(tests_universe, check_generate_next_generation)
{
    Field field(3, 3);
    field[0][1] = true;
    field[1][1] = true;
    field[1][2] = true;
    field[2][0] = true;

    Universe universe(field);
    universe.GenerateNextGeneration();

    std::ostringstream oss;
    oss << universe;

    EXPECT_EQ(oss.str(),
              "Name: My Universe\n"
              "Generation: 2\n"
              ". @ @ \n"
              "@ @ @ \n"
              ". @ . \n");
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}