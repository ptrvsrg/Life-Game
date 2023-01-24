message(STATUS "Creating library \"universe\"")

add_library(universe STATIC
        src/universe.cpp)
target_include_directories(universe
        PUBLIC include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/field/include)
target_link_directories(universe
        PUBLIC ${CMAKE_BINARY_DIR}/lib/field)
target_link_libraries(universe
        PUBLIC field)

message(STATUS "Creating tests for library \"universe\"")
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

add_executable(tests_universe
        test/tests_universe.cpp)
target_link_libraries(tests_universe
        PUBLIC universe
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_universe
        COMMAND tests_universe
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)