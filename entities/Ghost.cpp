//
// Created by Siebe Haché on 07/11/2025.
//
#include <iostream>
#include "Ghost.h"

void Ghost::update(float deltaTime, World& world, const Pacman& pacman) {
    timeAlive = deltaTime;

    // Start chasing after delay
    if (!chasing && timeAlive >= chaseDelay) {
        chasing = true;
    }
    if (!chasing) return;

    // Check if ready to move using the same system as Pacman
    if (!readyToMove(timeAlive)) return;

    recordMoveTime(timeAlive);
    moveInDirection(world);
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

// ============================================================================
// RedGhost: Locks to one direction, reconsiders at intersections
// ============================================================================

RedGhost::RedGhost(float x, float y)
    : Ghost(x, y, 'R', 0.0f), lockedDirection('N') {
    lockedDirection = Random::getInstance().getRandomDirection();
    setDirection(lockedDirection);
}

void RedGhost::update(float deltaTime, World& world, const Pacman& pacman) {
    timeAlive = deltaTime;

    if (!chasing && timeAlive >= chaseDelay) {
        chasing = true;
    }
    if (!chasing) return;

    // Use timeAlive instead of moveTimer
    if (!readyToMove(timeAlive)) return;

    // Check if at intersection BEFORE moving
    if (world.isAtIntersection(this)) {
        // With probability 0.5, choose a new random direction
        if (Random::getInstance().getInt(0, 1) == 1) {
            // Get all viable directions
            std::vector<char> viableDirs;
            for (char d : {'N', 'Z', 'W', 'O'}) {
                if (world.canMoveInDirection(this, d)) {
                    viableDirs.push_back(d);
                }
            }

            if (!viableDirs.empty()) {
                int idx = Random::getInstance().getInt(0, (int)viableDirs.size() - 1);
                lockedDirection = viableDirs[idx];
                setDirection(lockedDirection);
            }
        }
    }

    // Try to move in locked direction
    if (!world.tryMoveGhost(this, lockedDirection)) {
        // If blocked, pick a new viable direction immediately
        std::vector<char> viableDirs;
        for (char d : {'N', 'Z', 'W', 'O'}) {
            if (world.canMoveInDirection(this, d)) {
                viableDirs.push_back(d);
            }
        }

        if (!viableDirs.empty()) {
            int idx = Random::getInstance().getInt(0, (int)viableDirs.size() - 1);
            lockedDirection = viableDirs[idx];
            setDirection(lockedDirection);
            world.tryMoveGhost(this, lockedDirection);
        }
    }

    recordMoveTime(timeAlive);
}

void RedGhost::chooseDirection(const Pacman& pacman) {
    direction = lockedDirection;
}

// ============================================================================
// BlueGhost: Moves toward position "in front of" Pacman
// ============================================================================

BlueGhost::BlueGhost(float x, float y, float delay)
    : Ghost(x, y, 'B', delay) {
    setDirection(Random::getInstance().getRandomDirection());
}

void BlueGhost::update(float deltaTime, World& world, const Pacman& pacman) {
    timeAlive = deltaTime;

    if (!chasing && timeAlive >= chaseDelay) {
        chasing = true;
    }
    if (!chasing) return;

    if (!readyToMove(timeAlive)) return;

    recordMoveTime(timeAlive);
    chooseDirection(world, pacman);
    moveInDirection(world);
}

void BlueGhost::chooseDirection(World& world, const Pacman& pacman) {
    // Calculate position "in front of" Pacman
    coord pPos = pacman.getPosition();
    char pDir = pacman.getDirection();

    float targetX = pPos.x;
    float targetY = pPos.y;

    // Move target 4 tiles ahead in Pacman's direction
    float stepW = 2.0f / world.getWidth();
    float stepH = 2.0f / world.getHeight();

    switch (pDir) {
        case 'N': targetY -= 2 * stepH; break;
        case 'Z': targetY += 2 * stepH; break;
        case 'W': targetX -= 2 * stepW; break;
        case 'O': targetX += 2 * stepW; break;
    }

    // Find all viable directions
    std::vector<char> viableDirs;
    for (char d : {'N', 'Z', 'W', 'O'}) {
        if (world.canMoveInDirection(this, d)) {
            viableDirs.push_back(d);
        }
    }

    if (viableDirs.empty()) return;

    // Choose direction that minimizes Manhattan distance to target
    float bestDist = 1e9;
    std::vector<char> bestDirs;

    for (char d : viableDirs) {
        float testX = position.x;
        float testY = position.y;

        switch (d) {
            case 'N': testY -= stepH; break;
            case 'Z': testY += stepH; break;
            case 'W': testX -= stepW; break;
            case 'O': testX += stepW; break;
        }

        float dist = std::fabs(targetX - testX) + std::fabs(targetY - testY);

        if (dist < bestDist) {
            bestDist = dist;
            bestDirs = {d};
        } else if (std::fabs(dist - bestDist) < 0.0001f) { // floating point comparison
            bestDirs.push_back(d);
        }
    }

    if (!bestDirs.empty()) {
        int idx = Random::getInstance().getInt(0, (int)bestDirs.size() - 1);
        direction = bestDirs[idx];
    }
}

// ============================================================================
// PinkGhost: Chases Pacman directly
// ============================================================================

PinkGhost::PinkGhost(float x, float y, float delay)
    : Ghost(x, y, 'G', delay) {
    setDirection(Random::getInstance().getRandomDirection());
}

void PinkGhost::update(float deltaTime, World& world, const Pacman& pacman) {
    timeAlive = deltaTime;

    if (!chasing && timeAlive >= chaseDelay) {
        chasing = true;
    }
    if (!chasing) return;

    if (!readyToMove(timeAlive)) return;

    recordMoveTime(timeAlive);
    chooseDirection(world, pacman);
    moveInDirection(world);
}

void PinkGhost::chooseDirection(World& world, const Pacman& pacman) {
    float targetX = pacman.getPosition().x;
    float targetY = pacman.getPosition().y;

    float stepW = 2.0f / world.getWidth();
    float stepH = 2.0f / world.getHeight();

    // Find all viable directions
    std::vector<char> viableDirs;
    for (char d : {'N', 'Z', 'W', 'O'}) {
        if (world.canMoveInDirection(this, d)) {
            viableDirs.push_back(d);
        }
    }

    if (viableDirs.empty()) return;

    // Choose direction that minimizes Manhattan distance to Pacman
    float bestDist = 1e9;
    std::vector<char> bestDirs;

    for (char d : viableDirs) {
        float testX = position.x;
        float testY = position.y;

        switch (d) {
            case 'N': testY -= stepH; break;
            case 'Z': testY += stepH; break;
            case 'W': testX -= stepW; break;
            case 'O': testX += stepW; break;
        }

        float dist = std::fabs(targetX - testX) + std::fabs(targetY - testY);

        if (dist < bestDist) {
            bestDist = dist;
            bestDirs = {d};
        } else if (std::fabs(dist - bestDist) < 0.0001f) {
            bestDirs.push_back(d);
        }
    }

    if (!bestDirs.empty()) {
        int idx = Random::getInstance().getInt(0, (int)bestDirs.size() - 1);
        direction = bestDirs[idx];
    }
}