message(STATUS "Creating library \"offline_mode\"")

add_library(offline_mode STATIC
        src/offline_mode.cpp)
target_include_directories(offline_mode
        PUBLIC include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/mode/abstract_mode/include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/mode/life_file/io_life_file/include)
target_link_directories(offline_mode
        PUBLIC ${CMAKE_BINARY_DIR}/lib/mode/abstract_mode
        PUBLIC ${CMAKE_BINARY_DIR}/lib/mode/life_file/io_life_file)
target_link_libraries(offline_mode
        PUBLIC abstract_mode
        PUBLIC io_life_file)
