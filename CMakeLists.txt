cmake_minimum_required(VERSION 3.22.1)

set(SUBDIR
        lib/cell
        lib/cl_parser
        lib/game
        lib/life_file
        lib/mode
        lib/universe)
set(LIBRARY
        cl_parser
        game)

project(Task2-Life CXX)

enable_testing()
foreach(SUBDIR ${SUBDIR})
    add_subdirectory(${SUBDIR})
endforeach(SUBDIR)

# Example

add_executable(example
        example/main.cpp)
target_link_libraries(example
        PUBLIC ${LIBRARY})