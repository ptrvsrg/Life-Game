message(STATUS "Creating library \"life_file_base\"")

add_library(life_file_base INTERFACE)
target_include_directories(life_file_base
        INTERFACE include)