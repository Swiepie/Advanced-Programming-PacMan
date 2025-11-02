cmake_minimum_required(VERSION 3.5)
project(Advanced_Programming_PacMan)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sfml@2")
find_package(SFML 2.6.1 REQUIRED COMPONENTS graphics window system)


add_executable(Advanced_Programming_PacMan
        Entity.cpp
        Entity.h
        Pacman.cpp
        Pacman.h
        main.cpp
        states/StateManager.h
        Game.h
        states/MenuState.h
        Game.cpp
        states/MenuState.cpp
        states/State.cpp
        states/StateManager.cpp
        Stopwatch.cpp
        World.cpp
        Score.cpp
        Random.cpp
        states/LevelState.h
        states/LevelState.cpp
        Wall.h
        Wall.cpp
        renderer/View.cpp
        renderer/View.h
        Coin.h
        Coin.cpp
        renderer/WorldView.h
        renderer/WorldView.cpp
        states/PausedState.h
        states/PausedState.cpp
)

# Koppel de benodigde SFML-libraries
target_link_libraries(Advanced_Programming_PacMan sfml-graphics sfml-window sfml-system)

INSTALL(TARGETS Advanced_Programming_PacMan DESTINATION bin)
