message(STATUS "Creating library \"mode_creator\"")

add_library(mode_creator STATIC
        src/mode_creator.cpp)
target_include_directories(mode_creator
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/mode/abstract_mode/include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/mode/online_mode/include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/mode/offline_mode/include)
target_link_directories(mode_creator
        PUBLIC ${CMAKE_BINARY_DIR}/lib/mode/abstract_mode
        PUBLIC ${CMAKE_BINARY_DIR}/lib/mode/online_mode
        PUBLIC ${CMAKE_BINARY_DIR}/lib/mode/offline_mode)
target_link_libraries(mode_creator
        PUBLIC abstract_mode
        PUBLIC online_mode
        PUBLIC offline_mode)