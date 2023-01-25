message(STATUS "Creating library \"life_file_base\"")

add_library(life_file_base STATIC
        src/life_file_base.cpp)
target_include_directories(life_file_base
        PUBLIC include)