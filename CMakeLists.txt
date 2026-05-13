cmake_minimum_required(VERSION 3.20)

project(tic_tac_toe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(tictactoe
    tic_tac_toe.cpp
)

target_include_directories(tictactoe PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tests
    tests/ParseStrategyTaskTests.cpp
    tests/SolveTests.cpp
    tests/EvaluatePositionTests.cpp
    tests/EvaluateMoveTests.cpp
    tests/BuildOptimalTree.cpp
)

target_link_libraries(tests PRIVATE
    tictactoe
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)