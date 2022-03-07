cmake_minimum_required(VERSION 3.16)
project(blockudokuplusplus CXX)

find_package(SFML 2.5.1 REQUIRED COMPONENTS audio graphics)

add_executable(blockudokuplusplus
    src/audio.cpp
    src/block.cpp
    src/game.cpp
    src/main.cpp
    src/pickupBoard.cpp
    src/score.cpp
    src/table.cpp
    src/utilities.cpp)
target_include_directories(blockudokuplusplus PRIVATE include)
target_link_libraries(blockudokuplusplus PRIVATE sfml-audio sfml-graphics)
target_compile_features(blockudokuplusplus PRIVATE cxx_std_14)