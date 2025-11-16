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

    // AANGEPAST: Basis-update logica verplaatst naar de subklassen
}
bool Ghost::getFearState() const {
    return inFearMode;
}
void Ghost::setFearState(bool state) {
    inFearMode = state;
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
    speedSave = spd;
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
void Ghost::resetFearState() {

    inFearMode = false;
    speed = speedSave;
    reverseDirection();

}
void Ghost::chooseDirectionFear(World& world, const Pacman& pacman) {
    float targetX = pacman.getPosition().x;
    float targetY = pacman.getPosition().y;

    float stepW = 2.0f / world.getWidth();
    float stepH = 2.0f / world.getHeight();

    char oppositeDir;
    switch (direction) {
        case 'N': oppositeDir = 'Z'; break;
        case 'Z': oppositeDir = 'N'; break;
        case 'W': oppositeDir = 'O'; break;
        case 'O': oppositeDir = 'W'; break;
        default:  oppositeDir = '?'; break;
    }

    // ✅ REMOVED THE EARLY RETURN - Always reconsider direction in fear mode!

    // 1️⃣ Find all viable directions except opposite
    std::vector<char> viableDirs;
    for (char d : {'N', 'Z', 'W', 'O'}) {
        if (d == oppositeDir) continue;
        if (world.canMoveInDirection(this, d)) {
            viableDirs.push_back(d);
        }
    }

    // 2️⃣ If stuck, allow reversing
    if (viableDirs.empty() && world.canMoveInDirection(this, oppositeDir)) {
        viableDirs.push_back(oppositeDir);
    }

    // 3️⃣ Choose direction that MAXIMIZES Manhattan distance
    float worstDist = -1.0f;
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

        if (dist > worstDist + 0.0001f) {
            worstDist = dist;
            bestDirs = {d};
        } else if (std::fabs(dist - worstDist) < 0.0001f) {
            bestDirs.push_back(d);
        }
    }

    // 4️⃣ Choose from best candidates
    if (!bestDirs.empty()) {
        int idx = Random::getInstance().getInt(0, (int)bestDirs.size() - 1);
        direction = bestDirs[idx];
    }
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
    if (!readyToMove(timeAlive)) return;
    recordMoveTime(timeAlive); // <-- **FIX DEEL 1: Reset timer ALTIJD**

    if (world.getFearMode() && inFearMode) { // FEAR MODE
        fearTime = world.getFearModeTimer();
        speed = fearSpeed;

        // **FIX DEEL 2: Check VOORDAT je beweegt**
        if (world.isAtIntersection(this) || world.isAtDeadEnd(this) || !world.canMoveInDirection(this, direction)) {
            chooseDirectionFear(world, pacman);
        }
        world.tryMoveGhost(this, direction); // Probeer te bewegen
        return;
    }

    // NORMAL MODE
    speed = speedSave;
    if (!chasing && timeAlive >= chaseDelay) {
        chasing = true;
    }
    if (!chasing) return;

    // Decision logic
    if (world.isAtIntersection(this)) {
        if (Random::getInstance().getInt(0, 1) == 1) {
            std::vector<char> viableDirs;
            for (char d : {'N', 'Z', 'W', 'O'}) {
                if (world.canMoveInDirection(this, d)) {
                    viableDirs.push_back(d);
                }
            }
            if (!viableDirs.empty()) {
                int idx = Random::getInstance().getInt(0, (int)viableDirs.size() - 1);
                lockedDirection = viableDirs[idx];
            }
        }
    }
    // **FIX DEEL 2: Check VOORDAT je beweegt**
    else if (!world.canMoveInDirection(this, lockedDirection)) {
        // Als we vastlopen (niet op kruispunt), vind een nieuwe richting
        std::vector<char> viableDirs;
        for (char d : {'N', 'Z', 'W', 'O'}) {
            if (world.canMoveInDirection(this, d)) {
                viableDirs.push_back(d);
            }
        }
        if (!viableDirs.empty()) {
            int idx = Random::getInstance().getInt(0, (int)viableDirs.size() - 1);
            lockedDirection = viableDirs[idx];
        }
    }

    setDirection(lockedDirection);
    world.tryMoveGhost(this, direction); // Probeer te bewegen
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
    if (!readyToMove(timeAlive)) return;
    recordMoveTime(timeAlive); // <-- **FIX DEEL 1: Reset timer ALTIJD**

    if (world.getFearMode() && inFearMode) { // FEAR MODE
        fearTime = world.getFearModeTimer();
        speed = fearSpeed;

        // **FIX DEEL 2: Check VOORDAT je beweegt**
        if (world.isAtIntersection(this) || world.isAtDeadEnd(this) || !world.canMoveInDirection(this, direction)) {
            chooseDirectionFear(world, pacman);
        }
        world.tryMoveGhost(this, direction); // Probeer te bewegen
        return;
    }

    // NORMAL MODE
    speed = speedSave;
    if (!chasing && timeAlive >= chaseDelay) {
        chasing = true;
    }
    if (!chasing) return;

    // Decision logic
    // **FIX DEEL 2: Check VOORDAT je beweegt**
    if (world.isAtIntersection(this) || world.isAtDeadEnd(this) || !world.canMoveInDirection(this, direction)) {
        chooseDirection(world, pacman);
    }

    world.tryMoveGhost(this, direction); // Probeer te bewegen
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
    char oppositeDir;
    switch (direction) {
        case 'N': oppositeDir = 'Z'; break;
        case 'Z': oppositeDir = 'N'; break;
        case 'W': oppositeDir = 'O'; break;
        case 'O': oppositeDir = 'W'; break;
        default:  oppositeDir = '?'; break;
    }

    // Vind alle mogelijke richtingen, behalve de omgekeerde
    std::vector<char> viableDirs;
    for (char d : {'N', 'Z', 'W', 'O'}) {
        if (d == oppositeDir) continue; // vermijd onmiddellijke omkering
        if (world.canMoveInDirection(this, d)) {
            viableDirs.push_back(d);
        }
    }

    // Als we helemaal vastzitten (of alleen achteruit kunnen), mogen we omkeren
    if (viableDirs.empty() && world.canMoveInDirection(this, oppositeDir)) {
        viableDirs.push_back(oppositeDir);
    }
    // Als we nog steeds niks hebben (zeer zeldzaam, 1x1 box?)
    if (viableDirs.empty()) {
        return; // Geef het op, we kunnen nergens heen
    }


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
    if (!readyToMove(timeAlive)) return;
    recordMoveTime(timeAlive); // <-- **FIX DEEL 1: Reset timer ALTIJD**

    if (world.getFearMode() && inFearMode) { // FEAR MODE
        fearTime = world.getFearModeTimer();
        speed = fearSpeed;

        std::cout << position.x << ", " << position.y << "\n";

        // **FIX DEEL 2: Check VOORDAT je beweegt**
        if (world.isAtIntersection(this) || world.isAtDeadEnd(this) || !world.canMoveInDirection(this, direction)) {
            chooseDirectionFear(world, pacman);
        }
        world.tryMoveGhost(this, direction); // Probeer te bewegen
        return;
    }

    // NORMAL MODE
    speed = speedSave;
    if (!chasing && timeAlive >= chaseDelay) {
        chasing = true;
    }
    if (!chasing) return;

    // Decision logic
    // **FIX DEEL 2: Check VOORDAT je beweegt**
    if (world.isAtIntersection(this)|| world.isAtDeadEnd(this) || !world.canMoveInDirection(this, direction)) {
        chooseDirection(world, pacman);
    }

    world.tryMoveGhost(this, direction); // Probeer te bewegen
}

void PinkGhost::chooseDirection(World& world, const Pacman& pacman) {
    float targetX = pacman.getPosition().x;
    float targetY = pacman.getPosition().y;

    float stepW = 2.0f / world.getWidth();
    float stepH = 2.0f / world.getHeight();

    // Bepaal de omgekeerde richting (waar we vandaan kwamen)
    char oppositeDir;
    switch (direction) {
        case 'N': oppositeDir = 'Z'; break;
        case 'Z': oppositeDir = 'N'; break;
        case 'W': oppositeDir = 'O'; break;
        case 'O': oppositeDir = 'W'; break;
        default:  oppositeDir = '?'; break;
    }

    // Vind alle mogelijke richtingen, behalve de omgekeerde
    std::vector<char> viableDirs;
    for (char d : {'N', 'Z', 'W', 'O'}) {
        if (d == oppositeDir) continue; // vermijd onmiddellijke omkering
        if (world.canMoveInDirection(this, d)) {
            viableDirs.push_back(d);
        }
    }

    // Als we helemaal vastzitten, mogen we omkeren
    if (viableDirs.empty() && world.canMoveInDirection(this, oppositeDir)) {
        viableDirs.push_back(oppositeDir);
    }
    // Als we nog steeds niks hebben (zeer zeldzaam, 1x1 box?)
    if (viableDirs.empty()) {
        return; // Geef het op, we kunnen nergens heen
    }

    // Kies richting die Manhattan-afstand minimaliseert
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

        if (dist < bestDist - 0.0001f) {
            bestDist = dist;
            bestDirs = {d};
        } else if (std::fabs(dist - bestDist) < 0.0001f) {
            bestDirs.push_back(d);
        }
    }

    // Kies een willekeurige richting uit de beste opties
    if (!bestDirs.empty()) {
        int idx = Random::getInstance().getInt(0, (int)bestDirs.size() - 1);
        direction = bestDirs[idx];
    }
}


void Ghost::reverseDirection() {
    switch (direction) {
        case 'N': direction = 'Z'; break;
        case 'Z': direction = 'N'; break;
        case 'W': direction = 'O'; break;
        case 'O': direction = 'W'; break;
    }
}

void Ghost::softSnapToTileCenter(World& world) {
    float stepW = 2.f / world.getWidth();
    float stepH = 2.f / world.getHeight();

    // Bepaal tegel-index
    int tileX = std::floor(position.x / stepW);
    int tileY = std::floor(position.y / stepH);

    // Bovenlinkse hoek van die tegel
    float snapX = tileX * stepW;
    float snapY = tileY * stepH;

    // Drempel voor soft-snap
    float threshold = 0.15f * std::min(stepW, stepH);

    // Alleen snappen als hij al dichtbij genoeg zit
    if (std::fabs(position.x - snapX) < threshold &&
        std::fabs(position.y - snapY) < threshold)
    {
        position.x = snapX;
        position.y = snapY;
    }
}