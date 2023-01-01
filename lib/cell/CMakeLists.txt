message(STATUS "Creating library \"cell\"")

add_library(cell INTERFACE)
target_include_directories(cell
        INTERFACE include)

message(STATUS "Creating tests for library \"cell\"")
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

add_executable(tests_cell
        test/tests_cell.cpp)
target_link_libraries(tests_cell
        PUBLIC cell
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_cell
        COMMAND tests_cell
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)