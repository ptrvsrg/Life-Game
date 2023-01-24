message(STATUS "Creating library \"io_life_file\"")

add_library(io_life_file STATIC
        src/io_life_file.cpp)
target_include_directories(io_life_file
        PUBLIC include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/life_file/i_life_file/include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/life_file/o_life_file/include)
target_link_directories(io_life_file
        PUBLIC ${CMAKE_BINARY_DIR}/lib/life_file/i_life_file
        PUBLIC ${CMAKE_BINARY_DIR}/lib/life_file/o_life_file)
target_link_libraries(io_life_file
        PUBLIC i_life_file
        PUBLIC o_life_file)

message(STATUS "Creating tests for library \"io_life_file\"")
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

add_executable(tests_io_life_file
        test/tests_io_life_file.cpp)
target_link_libraries(tests_io_life_file
        PUBLIC io_life_file
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_io_life_file
        COMMAND tests_io_life_file
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)