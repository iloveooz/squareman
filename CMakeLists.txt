cmake_minimum_required(VERSION 2.6)
project ("SquareMan")

add_definitions("-std=c++11")

set(SRC src/main.cpp)

add_executable(sqman.exe ${SRC})

target_link_libraries( sqman sfml-sfml)
target_link_libraries( sqman sfml-window)
target_link_libraries( sqman sfml-graphics)
target_link_libraries( sqman sfml-audio)
target_link_libraries( sqman sfml-network)
