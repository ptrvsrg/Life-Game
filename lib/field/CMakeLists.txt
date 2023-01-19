message(STATUS "Creating library \"field\"")

add_library(field STATIC
        src/field.cpp)
target_include_directories(field
        PUBLIC include)

message(STATUS "Creating tests for library \"field\"")
find_package(GTest)
if (NOT GTest_FOUND)
    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        release-1.11.0
    )
    FetchContent_MakeAvailable(googletest)
endif ()

add_executable(tests_field
        test/tests_field.cpp)
target_link_libraries(tests_field
        PUBLIC field
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_field
        COMMAND tests_field
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)