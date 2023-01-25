message(STATUS "Creating library \"offline_mode\"")

add_library(offline_mode STATIC
        src/offline_mode.cpp)
target_include_directories(offline_mode
        PUBLIC include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/mode/abstract_mode/include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/mode/life_file/i_life_file/include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/mode/life_file/o_life_file/include)
target_link_directories(offline_mode
        PUBLIC ${CMAKE_BINARY_DIR}/lib/mode/abstract_mode
        PUBLIC ${CMAKE_BINARY_DIR}/lib/mode/life_file/i_life_file
        PUBLIC ${CMAKE_BINARY_DIR}/lib/mode/life_file/o_life_file)
target_link_libraries(offline_mode
        PUBLIC abstract_mode
        PUBLIC i_life_file
        PUBLIC o_life_file)

message(STATUS "Creating tests for library \"offline_mode\"")
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

add_executable(tests_offline_mode
        test/tests_offline_mode.cpp)
target_link_libraries(tests_offline_mode
        PUBLIC offline_mode
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_offline_mode
        COMMAND tests_offline_mode
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)
