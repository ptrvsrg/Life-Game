message(STATUS "Creating library \"abstract_mode\"")

add_library(abstract_mode INTERFACE)
target_include_directories(abstract_mode
        INTERFACE include)