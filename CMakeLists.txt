cmake_minimum_required(VERSION 3.10)
project(Advanced_Programming_PacMan)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Platformspecifieke SFML-locatie ---
if(WIN32)
    # Gebruik lokale SFML-directory (bijv. ./SFML)
    set(SFML_ROOT "${CMAKE_SOURCE_DIR}/SFML-2.6.2")
    set(CMAKE_PREFIX_PATH "${SFML_ROOT}")
    message(STATUS "Building on Windows - using local SFML in ${SFML_ROOT}")
else()
    # macOS / Linux (via Homebrew)
    set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sfml@2")
    message(STATUS "Building on macOS - using Homebrew SFML from ${CMAKE_PREFIX_PATH}")
endif()

cmake_policy(SET CMP0074 NEW)
# --- SFML zoeken ---
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# --- Bronnen ---
set(SOURCES
        entities/Entity.cpp
        entities/Pacman.cpp
        entities/Ghost.cpp
        main.cpp
        Game.cpp
        Stopwatch.cpp
        World.cpp
        Score.cpp
        Random.cpp
        entities/Wall.cpp
        entities/Coin.cpp
        renderer/WorldView.cpp
        states/State.cpp
        states/StateManager.cpp
        states/MenuState.cpp
        states/LevelState.cpp
        states/PausedState.cpp
        renderer/GhostView.cpp
        states/FinishState.cpp
        Scoreboard.cpp
)

set(HEADERS
        entities/Entity.h
        entities/Pacman.h
        Game.h
        entities/Wall.h
        entities/Coin.h
        renderer/WorldView.h
        states/State.h
        states/StateManager.h
        states/MenuState.h
        states/LevelState.h
        states/PausedState.h
        renderer/PacmanView.h
        renderer/PacmanView.cpp
        entities/Ghost.h
        entities/Fruit.cpp
        renderer/GhostView.h
        states/FinishState.h
        Scoreboard.h
)

# --- Executable ---
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# --- Link SFML ---
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# --- Kopieer DLL's op Windows ---
if(WIN32)
    # Kopieer automatisch SFML dll's van SFML/bin naar de uitvoermap
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SFML_ROOT}/bin" $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()

# --- Installatie ---
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
