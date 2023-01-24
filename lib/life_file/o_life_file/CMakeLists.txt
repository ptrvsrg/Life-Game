message(STATUS "Creating library \"o_life_file\"")

add_library(o_life_file STATIC
        src/o_life_file.cpp)
target_include_directories(o_life_file
        PUBLIC include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/life_file/life_file_base/include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/universe/include)
target_link_directories(o_life_file
        PUBLIC ${CMAKE_BINARY_DIR}/lib/life_file/life_file_base
        PUBLIC ${CMAKE_BINARY_DIR}/lib/universe)
target_link_libraries(o_life_file
        PUBLIC life_file_base
        PUBLIC universe)

message(STATUS "Creating tests for library \"o_life_file\"")
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

add_executable(tests_o_life_file
        test/tests_o_life_file.cpp)
target_link_libraries(tests_o_life_file
        PUBLIC o_life_file
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_o_life_file
        COMMAND tests_o_life_file
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)