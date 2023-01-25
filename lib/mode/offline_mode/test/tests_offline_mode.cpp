#include <gtest/gtest.h>
#include "offline_mode.h"

TEST(test_offline_mode, check)
{
    OfflineMode offline_mode("files/input.life",
                             "files/output.life",
                             11);
    offline_mode.Launch();

    std::set<Cell> check_cells = { {2, 1},
                                   {2, 2},
                                   {2, 3} };
    ILifeFile i_life_file("files/output.life");

    EXPECT_EQ(check_cells,
              i_life_file.ReadUniverse().GetCells());
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}