cmake_minimum_required(VERSION 2.6)
project ("SquareMan")

add_definitions("-std=c++11")

set(SRC src/main.cpp
		src/Animator.cpp
		src/Bonus.cpp
		src/Character.cpp
		src/Dot.cpp
		src/Game.cpp
		src/GameState.cpp
		src/Ghost.cpp
		src/Squareman.cpp
		src/Maze.cpp)

add_executable(sqman.exe ${SRC})

target_link_libraries(sqman.exe sfml-system)
target_link_libraries(sqman.exe sfml-window)
target_link_libraries(sqman.exe sfml-graphics)
target_link_libraries(sqman.exe sfml-audio)
target_link_libraries(sqman.exe sfml-network)
