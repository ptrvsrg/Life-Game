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
        FieldError
    );
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}