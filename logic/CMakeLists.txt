cmake_minimum_required(VERSION 3.10)
project(Logic)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0074 NEW)


# --- Bronnen ---
set(SOURCES
        entities/Entity.cpp
        entities/Pacman.cpp
        entities/Ghost.cpp
        entities/Fruit.cpp
        Stopwatch.cpp
        World.cpp
        Score.cpp
        Random.cpp
        entities/Wall.cpp
        entities/Coin.cpp
        Scoreboard.cpp
        Visitor.cpp
        entities/Subject.cpp
)

set(HEADERS
        entities/Entity.h
        entities/Pacman.h
        entities/Wall.h
        entities/Coin.h
        entities/Fruit.h
        entities/Ghost.h
        Scoreboard.h
        entities/EntityFactory.h
        Visitor.h
        entities/Subject.h
        Observer.h

)

add_library(Logic STATIC
        ${SOURCES}
        ${HEADERS}
)


# --- Installatie ---
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
