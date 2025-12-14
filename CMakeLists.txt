cmake_minimum_required(VERSION 3.10)
project(Advanced_Programming_PacMan)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0074 NEW)

if(WIN32)
    set(SFML_ROOT "${CMAKE_SOURCE_DIR}/SFML-2.6.2")
    set(CMAKE_PREFIX_PATH "${SFML_ROOT}")
    message(STATUS "Building on Windows - using local SFML in ${SFML_ROOT}")
else()
    set(CMAKE_PREFIX_PATH "/opt/homebrew/opt/sfml@2")
    message(STATUS "Building on macOS - using Homebrew SFML")
endif()

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_library(Logic STATIC
        logic/entities/Entity.cpp
        logic/entities/Pacman.cpp
        logic/entities/Ghost.cpp
        logic/entities/Fruit.cpp
        logic/entities/Wall.cpp
        logic/entities/Coin.cpp
        logic/entities/Subject.cpp
        logic/Stopwatch.cpp
        logic/World.cpp
        logic/Score.cpp
        logic/Random.cpp
        logic/Scoreboard.cpp
        logic/Visitor.cpp
)

target_include_directories(Logic PUBLIC
        ${CMAKE_SOURCE_DIR}/logic
)

add_executable(${PROJECT_NAME}
        main.cpp
        Game.cpp
        ConcreteFactory.cpp

        renderer/WorldView.cpp
        renderer/PacmanView.cpp
        renderer/GhostView.cpp
        renderer/EntityView.cpp
        renderer/CollectibleView.cpp
        renderer/WallView.cpp

        states/State.cpp
        states/StateManager.cpp
        states/MenuState.cpp
        states/LevelState.cpp
        states/PausedState.cpp
        states/FinishState.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
        Logic
        sfml-graphics
        sfml-window
        sfml-system
        sfml-main
)

if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${SFML_ROOT}/bin"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
