#include <gtest/gtest.h>
#include "cell.h"

TEST(tests_cell, check_output)
{
    std::ostringstream oss;
    Cell cell = {
        10,
        20
    };

    oss << cell;

    EXPECT_EQ(oss.str(), "10 20\n");
}

TEST(tests_cell, check_input)
{
    {
        std::istringstream iss("10 20");
        Cell cell;

        iss >> cell;

        EXPECT_EQ(cell.m_x, 10);
        EXPECT_EQ(cell.m_y, 20);
    }

    {
        std::istringstream iss("10 a");
        Cell cell;

        EXPECT_THROW
        (
            {
                iss >> cell;
            },
            CellCoordinatesError
        );
    }
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}