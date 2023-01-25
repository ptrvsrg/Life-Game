#include <gtest/gtest.h>
#include "i_life_file.h"
#include "cell.h"

struct LifeFileArgs
{
    std::string m_name;
    enum ExceptionType
    {
        DIGIT_SET_ERROR,
        FILE_FORMAT_ERROR,
        FILE_OPENING_ERROR,
        FIELD_SIZE_ERROR,
        NO_EXCEPTION
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
        LifeFileArgs("files/comments.life", LifeFileArgs::NO_EXCEPTION),
        LifeFileArgs("files/duplicate_coordinates.life", LifeFileArgs::NO_EXCEPTION),
        LifeFileArgs("files/file_format.life", LifeFileArgs::FILE_FORMAT_ERROR),
        LifeFileArgs("files/incorrect_field_size_1.life", LifeFileArgs::FIELD_SIZE_ERROR),
        LifeFileArgs("files/incorrect_field_size_2.life", LifeFileArgs::FIELD_SIZE_ERROR),
        LifeFileArgs("files/incorrect_field_size_3.life", LifeFileArgs::FIELD_SIZE_ERROR),
        LifeFileArgs("files/incorrect_rules_1.life", LifeFileArgs::DIGIT_SET_ERROR),
        LifeFileArgs("files/incorrect_rules_2.life", LifeFileArgs::DIGIT_SET_ERROR),
        LifeFileArgs("files/non_exist.life", LifeFileArgs::FILE_OPENING_ERROR),
        LifeFileArgs("files/without_birth_rules.life", LifeFileArgs::NO_EXCEPTION),
        LifeFileArgs("files/without_name.life", LifeFileArgs::NO_EXCEPTION),
        LifeFileArgs("files/without_survival_rules.life", LifeFileArgs::NO_EXCEPTION)
    )
);

TEST_P(LifeFileTest, check_exception)
{
    LifeFileArgs params = GetParam();

    switch (params.m_exception_type)
    {
        case LifeFileArgs::DIGIT_SET_ERROR:
            EXPECT_THROW
            (
                {
                    ILifeFile life_file(params.m_name);
                    Universe universe = life_file.ReadUniverse();
                },
                DigitSetError
            );
            break;
        case LifeFileArgs::FILE_FORMAT_ERROR:
            EXPECT_THROW
            (
                {
                    ILifeFile life_file(params.m_name);
                },
                FileFormatError
            );
            break;
        case LifeFileArgs::FILE_OPENING_ERROR:
            EXPECT_THROW
            (
                {
                    ILifeFile life_file(params.m_name);
                },
                FileOpeningError
            );
            break;
        case LifeFileArgs::FIELD_SIZE_ERROR:
            EXPECT_THROW
            (
                {
                    ILifeFile life_file(params.m_name);
                    Universe universe = life_file.ReadUniverse();
                },
                FieldSizeError
            );
            break;
        case LifeFileArgs::NO_EXCEPTION:
            EXPECT_NO_THROW
            (
                ILifeFile life_file(params.m_name);
                Universe universe = life_file.ReadUniverse();
            );
            break;
    }
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}