cmake_minimum_required(VERSION 3.16)
project(blockudokuplusplus CXX)

find_package(SFML 2.5.1 REQUIRED COMPONENTS audio graphics)
find_package(OpenGL REQUIRED)

add_executable(blockudokuplusplus
    src/audio.cpp
    src/block.cpp
    src/bot.cpp
    src/cellMatrix.cpp
    src/game.cpp
    src/imguiInterface.cpp
    src/main.cpp
    src/pickupBoard.cpp
    src/score.cpp
    src/settings.cpp
    src/table.cpp
    src/utilities.cpp
    libraries/imgui/imgui.cpp
    libraries/imgui/imgui_demo.cpp
    libraries/imgui/imgui_draw.cpp
    libraries/imgui/imgui_tables.cpp
    libraries/imgui/imgui_widgets.cpp
    libraries/imgui/imgui-SFML.cpp)
target_include_directories(blockudokuplusplus PRIVATE include libraries/imgui)
target_link_libraries(blockudokuplusplus PRIVATE sfml-audio sfml-graphics sfml-window ${OPENGL_LIBRARIES})
target_compile_features(blockudokuplusplus PRIVATE cxx_std_14)