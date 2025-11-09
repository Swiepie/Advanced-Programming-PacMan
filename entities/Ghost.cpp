//
// Created by Siebe Haché on 07/11/2025.
//
#include <iostream>
#include "Ghost.h"
void Ghost::update(float deltaTime, World& world, const Pacman& pacman) {
    timeAlive += deltaTime;

    // Start chasing after delay
    if (!chasing && timeAlive >= chaseDelay) {
        chasing = true;
    }
    if (!chasing) return;

    moveTimer += deltaTime;
    if (!readyToMove()) return;

    moveInDirection(world);
    resetMoveTimer();
}

void Ghost::moveInDirection(World& world) {
    world.tryMoveGhost(this, direction);
}

void Ghost::setDirection(char direct) {
    direction = direct;
}
double Ghost::getSpeed() const {
    return speed;
}
void Ghost::setSpeed(double spd) {
    speed = spd;
}
void Ghost::addMoveTime(float dt) {
    moveTimer += dt;
}
bool Ghost::readyToMove() const {
    return moveTimer >= moveCooldown;
}
void Ghost::resetMoveTimer() {
    moveTimer -= moveCooldown;
}
bool Ghost::readyToMove(float currentTime) const {
    return (currentTime - lastMoveTime) >= moveCooldown;
}

void Ghost::recordMoveTime(float currentTime) {
    lastMoveTime = currentTime;
}



RedGhost::RedGhost(float x, float y)
    : Ghost(x, y, 'R', 0.0f), lockedDirection('N') {
    setDirection(Random::getInstance().getRandomDirection());
}

void RedGhost::update(float deltaTime, World& world, const Pacman& pacman) {
    Ghost::update(deltaTime, world, pacman);

    if (!isChasing()) return;

    // Alleen kies nieuwe richting als op een kruispunt
    if (world.isAtIntersection(this) && Random::getInstance().getInt(0, 1) == 1) {
        setDirection(Random::getInstance().getRandomDirection());
    }
}

void RedGhost::chooseDirection(const Pacman& pacman) {
    direction = lockedDirection;
}

BlueGhost::BlueGhost(float x, float y, float delay)
    : Ghost(x, y, 'B', delay) {
    setDirection(Random::getInstance().getRandomDirection());
}

void BlueGhost::update(float deltaTime, World& world, const Pacman& pacman) {
    if (!isChasing() && timeAlive < chaseDelay) {
        timeAlive += deltaTime;
        return;
    }
    if (!isChasing()) setChasing(true);

    addMoveTime(deltaTime);
    if (!readyToMove()) return;

    chooseDirection(pacman);
    moveInDirection(world);
    resetMoveTimer();
}

void BlueGhost::chooseDirection(const Pacman& pacman) {
    // Kijk waar Pacman naartoe kijkt
    coord pPos = pacman.getPosition();
    char pDir = pacman.getDirection();

    // Locatie "voor Pacman"
    float px = pPos.x;
    float py = pPos.y;

    switch (pDir) {
        case 'N': py -= 0.01; break;
        case 'Z': py += 0.01; break;
        case 'W': px -= 0.01; break;
        case 'O': px += 0.01; break;
    }

    // Kies richting die Manhattan afstand tot (px, py) minimaliseert
    std::vector<char> dirs = {'N', 'Z', 'L', 'R'};
    float bestDist = 1e9;
    std::vector<char> bestDirs;

    for (char d : dirs) {
        float nx = position.x, ny = position.y;
        if (d == 'N') ny -= 0.01;
        if (d == 'Z') ny += 0.01;
        if (d == 'W') nx -= 0.01;
        if (d == 'O') nx += 0.01;
        float dist = std::fabs(px - nx) + std::fabs(py - ny);
        if (dist < bestDist) {
            bestDist = dist;
            bestDirs = {d};
        } else if (dist == bestDist) {
            bestDirs.push_back(d);
        }
    }

    direction = bestDirs[Random::getInstance().getInt(0, (int)bestDirs.size() - 1)];
}


PinkGhost::PinkGhost(float x, float y, float delay)
    : Ghost(x, y, 'G', delay) {
    setDirection(Random::getInstance().getRandomDirection());
}

void PinkGhost::update(float deltaTime, World& world, const Pacman& pacman) {
    Ghost::update(deltaTime, world, pacman);

    if (!isChasing()) return;

    addMoveTime(deltaTime);
    if (!readyToMove()) return;

    // bepaal target voor Pacman
    coord target = pacman.getPosition();
    switch (pacman.getDirection()) {
        case 'N': target.y -= 0.01f; break;
        case 'Z': target.y += 0.01f; break;
        case 'W': target.x -= 0.01f; break;
        case 'O': target.x += 0.01f; break;
    }

    chooseDirection(pacman);
    moveInDirection(world);
    resetMoveTimer();
}

void PinkGhost::chooseDirection(const Pacman& pacman) {
    float px = pacman.getPosition().x;
    float py = pacman.getPosition().y;
    float gx = position.x;
    float gy = position.y;

    // Kies richting die Manhattan afstand minimaliseert
    std::vector<char> dirs = {'Z', 'N', 'W', 'O'};
    float bestDist = 1e9;
    std::vector<char> bestDirs;

    for (char d : dirs) {
        float nx = gx, ny = gy;
        if (d == 'N') ny -= 0.01;
        if (d == 'Z') ny += 0.01;
        if (d == 'W') nx -= 0.01;
        if (d == 'O') nx += 0.01;
        float dist = std::fabs(px - nx) + std::fabs(py - ny);
        if (dist < bestDist) {
            bestDist = dist;
            bestDirs = {d};
        } else if (dist == bestDist) {
            bestDirs.push_back(d);
        }
    }

    direction = bestDirs[Random::getInstance().getInt(0, (int)bestDirs.size() - 1)];
}