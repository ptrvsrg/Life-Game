#include <gtest/gtest.h>
#include "universe.h"

TEST(tests_universe, check_generate_next_generation)
{
    std::set<Cell> cells{ {0, 1},
                          {1, 1}, {1, 2},
                          {2, 0} };
    Universe universe(cells,
                      10,
                      10,
                      "My universe",
                      std::set<size_t>{ 3 },
                      std::set<size_t>{ 2, 3 });
    universe.GenerateNextGeneration();

    std::set<Cell> check_cells{ {0, 1}, {0, 2},
                                {1, 0}, {1, 1}, {1, 2},
                                {2, 1} };

    EXPECT_EQ(check_cells,
              universe.GetCells());
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}