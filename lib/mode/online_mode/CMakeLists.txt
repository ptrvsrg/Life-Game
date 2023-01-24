message(STATUS "Creating library \"online_mode\"")

add_library(online_mode STATIC
        src/online_mode.cpp)
target_include_directories(online_mode
        PUBLIC include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/mode/abstract_mode/include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/mode/life_file/io_life_file/include)
target_link_directories(online_mode
        PUBLIC ${CMAKE_BINARY_DIR}/lib/mode/abstract_mode
        PUBLIC ${CMAKE_BINARY_DIR}/lib/mode/life_file/io_life_file)
target_link_libraries(online_mode
        PUBLIC abstract_mode
        PUBLIC io_life_file)

message(STATUS "Creating tests for library \"online_mode\"")
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

add_executable(tests_online_mode
        test/tests_online_mode.cpp)
target_link_libraries(tests_online_mode
        PUBLIC online_mode
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_online_mode
        COMMAND tests_online_mode
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)
