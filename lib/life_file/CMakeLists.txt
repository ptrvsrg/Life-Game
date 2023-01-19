message(STATUS "Creating library \"life_file\"")

add_library(life_file STATIC
        src/life_file.cpp)
target_include_directories(life_file
        PUBLIC include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/cell/include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/field/include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/universe/include)
target_link_directories(life_file
        PUBLIC ${CMAKE_BINARY_DIR}/lib/cell
        PUBLIC ${CMAKE_BINARY_DIR}/lib/field
        PUBLIC ${CMAKE_BINARY_DIR}/lib/universe)
target_link_libraries(life_file
        PUBLIC cell
        PUBLIC field
        PUBLIC universe)

message(STATUS "Creating tests for library \"life_file\"")
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

add_executable(tests_life_file
        test/tests_life_file.cpp)
target_link_libraries(tests_life_file
        PUBLIC life_file
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_life_file
        COMMAND tests_life_file
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)