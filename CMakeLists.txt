cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

PROJECT(2048_N_tuple_networks)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

set(TEST_BOARD_SRC 
    ${PROJECT_SOURCE_DIR}/src/board.cpp
    ${PROJECT_SOURCE_DIR}/src/pattern.cpp
    ${PROJECT_SOURCE_DIR}/src/policy.cpp

    ${PROJECT_SOURCE_DIR}/test/test_board.cpp
    # ${PROJECT_SOURCE_DIR}/test/test_play_games.cpp
    # ${PROJECT_SOURCE_DIR}/test/test_pattern.cpp
    # ${PROJECT_SOURCE_DIR}/test/test_policy.cpp
)

set(TEST_PLAY_GAMES_SRC 
    ${PROJECT_SOURCE_DIR}/src/board.cpp
    ${PROJECT_SOURCE_DIR}/src/pattern.cpp
    ${PROJECT_SOURCE_DIR}/src/policy.cpp

    # ${PROJECT_SOURCE_DIR}/test/test_board.cpp
    ${PROJECT_SOURCE_DIR}/test/test_play_games.cpp
    # ${PROJECT_SOURCE_DIR}/test/test_pattern.cpp
    # ${PROJECT_SOURCE_DIR}/test/test_policy.cpp
)

set(TEST_PATTERN_SRC 
    ${PROJECT_SOURCE_DIR}/src/board.cpp
    ${PROJECT_SOURCE_DIR}/src/pattern.cpp
    ${PROJECT_SOURCE_DIR}/src/policy.cpp

    # ${PROJECT_SOURCE_DIR}/test/test_board.cpp
    # ${PROJECT_SOURCE_DIR}/test/test_play_games.cpp
    ${PROJECT_SOURCE_DIR}/test/test_pattern.cpp
    # ${PROJECT_SOURCE_DIR}/test/test_policy.cpp
)

set(TEST_POLICY_SRC 
    ${PROJECT_SOURCE_DIR}/src/board.cpp
    ${PROJECT_SOURCE_DIR}/src/pattern.cpp
    ${PROJECT_SOURCE_DIR}/src/policy.cpp

    # ${PROJECT_SOURCE_DIR}/test/test_board.cpp
    # ${PROJECT_SOURCE_DIR}/test/test_play_games.cpp
    # ${PROJECT_SOURCE_DIR}/test/test_pattern.cpp
    ${PROJECT_SOURCE_DIR}/test/test_policy.cpp
)

set(TEST_TRAIN_LOOP_SRC 
    ${PROJECT_SOURCE_DIR}/src/board.cpp
    ${PROJECT_SOURCE_DIR}/src/pattern.cpp
    ${PROJECT_SOURCE_DIR}/src/policy.cpp

    # ${PROJECT_SOURCE_DIR}/test/test_board.cpp
    # ${PROJECT_SOURCE_DIR}/test/test_play_games.cpp
    # ${PROJECT_SOURCE_DIR}/test/test_pattern.cpp
    # ${PROJECT_SOURCE_DIR}/test/test_policy.cpp
    ${PROJECT_SOURCE_DIR}/test/test_train_loop.cpp
)

if (CMAKE_GENERATOR MATCHES "Visual Studio")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:268435456")
else ()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,268435456")
endif()

add_executable(test_board ${TEST_BOARD_SRC} ${PROJECT_SOURCE_DIR}/test/test_board.cpp)
add_executable(test_play_games ${TEST_PLAY_GAMES_SRC} ${PROJECT_SOURCE_DIR}/test/test_play_games.cpp)
add_executable(test_pattern ${TEST_PATTERN_SRC} ${PROJECT_SOURCE_DIR}/test/test_pattern.cpp)
add_executable(test_policy ${TEST_POLICY_SRC} ${PROJECT_SOURCE_DIR}/test/test_policy.cpp)
add_executable(test_train_loop ${TEST_TRAIN_LOOP_SRC} ${PROJECT_SOURCE_DIR}/test/test_train_loop.cpp)

