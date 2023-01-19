#include <gtest/gtest.h>
#include "life_file.h"

struct LifeFileArgs
{
    std::string m_name;
    enum ExceptionType
    {
        NO_EXCEPTION,
        CELL_ERROR,
        DIGIT_SET_ERROR,
        FIELD_ERROR,
        FILE_FORMAT_ERROR
    } m_exception_type;

    explicit LifeFileArgs(std::string name, ExceptionType exception_type)
        : m_name(std::move(name)),
          m_exception_type(exception_type) {}
};

class LifeFileTest : public ::testing::TestWithParam<LifeFileArgs> {};

INSTANTIATE_TEST_SUITE_P
(
    test_life_file,
    LifeFileTest,
    ::testing::Values
    (
        LifeFileArgs("files/file_format.life", LifeFileArgs::FILE_FORMAT_ERROR),
        LifeFileArgs("files/without_field_size_1.life", LifeFileArgs::FIELD_ERROR),
        LifeFileArgs("files/without_field_size_2.life", LifeFileArgs::FIELD_ERROR),
        LifeFileArgs("files/without_field_size_3.life", LifeFileArgs::FIELD_ERROR),
        LifeFileArgs("files/incorrect_rules_1.life", LifeFileArgs::DIGIT_SET_ERROR),
        LifeFileArgs("files/incorrect_rules_2.life", LifeFileArgs::DIGIT_SET_ERROR),
        LifeFileArgs("files/negative_coordinates.life", LifeFileArgs::CELL_ERROR),
        LifeFileArgs("files/incorrect_coordinates.life", LifeFileArgs::CELL_ERROR),
        LifeFileArgs("files/comments.life", LifeFileArgs::NO_EXCEPTION)
    )
);

TEST_P(LifeFileTest, check_exception)
{
    LifeFileArgs params = GetParam();

    switch (params.m_exception_type)
    {
        case LifeFileArgs::CELL_ERROR:
            EXPECT_THROW(
                {
                    LifeFile life_file(params.m_name);
                },
                CellError
            );
            break;
        case LifeFileArgs::DIGIT_SET_ERROR:
            EXPECT_THROW(
                {
                    LifeFile life_file(params.m_name);
                },
                DigitSetError
            );
            break;
        case LifeFileArgs::FIELD_ERROR:
            EXPECT_THROW(
                {
                    LifeFile life_file(params.m_name);
                },
                FieldError
            );
            break;
        case LifeFileArgs::FILE_FORMAT_ERROR:
            EXPECT_THROW(
                {
                    LifeFile life_file(params.m_name);
                },
                FileFormatError
            );
            break;
        case LifeFileArgs::NO_EXCEPTION:
            EXPECT_NO_THROW
            (
                LifeFile life_file(params.m_name);
            );
            break;
    }
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}