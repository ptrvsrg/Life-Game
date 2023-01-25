message(STATUS "Creating library \"online_mode\"")

add_library(online_mode STATIC
        src/online_mode.cpp)
target_include_directories(online_mode
        PUBLIC include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/mode/abstract_mode/include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/mode/life_file/i_life_file/include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/mode/life_file/o_life_file/include)
target_link_directories(online_mode
        PUBLIC ${CMAKE_BINARY_DIR}/lib/mode/abstract_mode
        PUBLIC ${CMAKE_BINARY_DIR}/lib/mode/life_file/i_life_file
        PUBLIC ${CMAKE_BINARY_DIR}/lib/mode/life_file/o_life_file)
target_link_libraries(online_mode
        PUBLIC abstract_mode
        PUBLIC i_life_file
        PUBLIC o_life_file)

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
