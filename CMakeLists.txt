cmake_minimum_required(VERSION 2.6)
project ("SquareMan")

add_definitions("-std=c++11")

set(SRC src/main.cpp
		src/animator/Animator.cpp
		src/bonus/Bonus.cpp
		src/character/Character.cpp
		src/dot/Dot.cpp
		src/game/Game.cpp
		src/game/GameState.cpp
		src/character/Ghost.cpp
		src/character/Squareman.cpp
		src/maze/Maze.cpp)

add_executable(sqman.exe ${SRC})

target_link_libraries(sqman.exe sfml-system)
target_link_libraries(sqman.exe sfml-window)
target_link_libraries(sqman.exe sfml-graphics)
target_link_libraries(sqman.exe sfml-audio)
target_link_libraries(sqman.exe sfml-network)
