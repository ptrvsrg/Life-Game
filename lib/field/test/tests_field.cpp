#include <gtest/gtest.h>
#include "field.h"

TEST(tests_field, check_index_operator)
{
    Field field(3, 3);
    field[1][1] = true;

    std::vector<std::vector<bool>> check_field({
        {false, false, false},
        {false, true, false},
        {false, false, false}
    });

    for (int i = 0; i < 3; ++i)
        EXPECT_EQ(field[i], check_field[i]);
}

TEST(tests_field, check_exception)
{
    EXPECT_THROW
    (
    {
            Field field(-1, -2);
        },
    FieldSizeError
    );
}

TEST(tests_field, check_print)
{
    Field field(3, 3);
    field[1][1] = true;
    std::string check = ". . . \n"
                        ". @ . \n"
                        ". . . \n";
    std::ostringstream oss;
    oss << field;

    EXPECT_EQ(oss.str(), check);
}

TEST(tests_field, check_count_live_neighbors)
{
    Field field(3, 3);
    field[0][1] = true;
    field[1][1] = true;
    field[1][2] = true;

    EXPECT_EQ(field.CountNeighbors({2, 0}), 3);
}

TEST(tests_field, check_get_cells)
{
    Field field(3, 3);
    field[0][1] = true;
    field[1][1] = true;
    field[1][2] = true;

    std::vector<Cell> cells = field.GetCells();
    std::vector<Cell> check_cells({ {0, 1}, {1, 1}, {1, 2} });

    for (int i = 0; i < std::max(cells.size(), check_cells.size()); ++i)
    {
        EXPECT_EQ(cells[i].m_x,
                  check_cells[i].m_x);
        EXPECT_EQ(cells[i].m_y,
                  check_cells[i].m_y);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}