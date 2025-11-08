//
// Created by Siebe Haché on 07/11/2025.
//

#include "Ghost.h"
void Ghost::update(float deltaTime) {

}
char Ghost::getDirection() const {
    return direction;
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
void Ghost::moveInDirection() {
    switch (direction) {
        case 'U': position.y -= speed; break;
        case 'D': position.y += speed; break;
        case 'L': position.x -= speed; break;
        case 'R': position.x += speed; break;
    }
}


RedGhost::RedGhost(float x, float y)
    : Ghost(x, y, 'L', 0.0f), lockedDirection('U') {}

void RedGhost::update(float deltaTime, const Pacman& pacman) {
    addMoveTime(deltaTime);
    if (!readyToMove()) return;
    moveInDirection();
    resetMoveTimer();

    // met kans 0.5 kies een nieuwe richting
    if (Random::getInstance().getFloat(0.0f, 1.0f) < 0.5f) {

        lockedDirection = Random::getInstance().getRandomDirection();
    }
}

void RedGhost::chooseDirection(const Pacman& pacman) {
    direction = lockedDirection;
}

BlueGhost::BlueGhost(float x, float y, float delay)
    : Ghost(x, y, 'F', delay) {}

void BlueGhost::update(float deltaTime, const Pacman& pacman) {
    addMoveTime(deltaTime);
    if (!readyToMove()) return;
    chooseDirection(pacman);
    moveInDirection();
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
        case 'U': py -= 0.01; break;
        case 'D': py += 0.01; break;
        case 'L': px -= 0.01; break;
        case 'R': px += 0.01; break;
    }

    // Kies richting die Manhattan afstand tot (px, py) minimaliseert
    std::vector<char> dirs = {'U', 'D', 'L', 'R'};
    float bestDist = 1e9;
    std::vector<char> bestDirs;

    for (char d : dirs) {
        float nx = position.x, ny = position.y;
        if (d == 'U') ny -= 0.01;
        if (d == 'D') ny += 0.01;
        if (d == 'L') nx -= 0.01;
        if (d == 'R') nx += 0.01;
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
    : Ghost(x, y, 'C', delay) {}

void PinkGhost::update(float deltaTime, const Pacman& pacman) {
    addMoveTime(deltaTime);
    if (!readyToMove()) return;
    chooseDirection(pacman);
    moveInDirection();
    resetMoveTimer();
}

void PinkGhost::chooseDirection(const Pacman& pacman) {
    float px = pacman.getPosition().x;
    float py = pacman.getPosition().y;
    float gx = position.x;
    float gy = position.y;

    // Kies richting die Manhattan afstand minimaliseert
    std::vector<char> dirs = {'U', 'D', 'L', 'R'};
    float bestDist = 1e9;
    std::vector<char> bestDirs;

    for (char d : dirs) {
        float nx = gx, ny = gy;
        if (d == 'U') ny -= 0.01;
        if (d == 'D') ny += 0.01;
        if (d == 'L') nx -= 0.01;
        if (d == 'R') nx += 0.01;
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