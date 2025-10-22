cmake_minimum_required(VERSION 3.28.3)
project(Advanced_Programming_PacMan)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sfml@2")
find_package(SFML 2.6.2 REQUIRED COMPONENTS graphics window system)


add_executable(Advanced_Programming_PacMan
        entity.cpp
        entity.h
        pacman.cpp
        pacman.h
        main.cpp
        StateManager.h
        Game.h
        MenuState.h
        Game.cpp
        MenuState.cpp
        State.cpp
        StateManager.cpp
        Stopwatch.cpp
        World.cpp
        Score.cpp
        Random.cpp
        LevelState.h
        LevelState.cpp
        Wall.h
        Wall.cpp
        renderer/View.cpp
        renderer/View.h
        Coin.h
        Coin.cpp
        renderer/WorldView.h
        renderer/WorldView.cpp
)

# Koppel de benodigde SFML-libraries
target_link_libraries(Advanced_Programming_PacMan sfml-graphics sfml-window sfml-system)
