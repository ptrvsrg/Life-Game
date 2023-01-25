message(STATUS "Creating library \"game\"")

add_library(game STATIC
        src/game.cpp)
target_include_directories(game
        PUBLIC include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/mode/mode_creator/include)
target_link_directories(game
        PUBLIC ${CMAKE_BINARY_DIR}/lib/mode/mode_creator)
target_link_libraries(game
        PUBLIC mode_creator)

#message(STATUS "Creating tests for library \"game\"")
#find_package(GTest)
#if (NOT GTest_FOUND)
#    include(FetchContent)
#
#    FetchContent_Declare(
#            googletest
#            GIT_REPOSITORY https://github.com/google/googletest.git
#            GIT_TAG        release-1.11.0
#    )
#    FetchContent_MakeAvailable(googletest)
#endif ()
#
#add_executable(tests_game
#        test/tests_game.cpp)
#target_link_libraries(tests_game
#        PUBLIC game
#        PUBLIC gtest
#        PUBLIC gtest_main)
#add_test(NAME tests_game
#        COMMAND tests_game
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)