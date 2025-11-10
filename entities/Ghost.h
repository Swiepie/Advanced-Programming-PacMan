//
// Created by Siebe Haché on 07/11/2025.
//

#ifndef GHOST_H
#define GHOST_H

#include "Entity.h"
#include "../Random.h"
#include "../World.h"
#include "Pacman.h"

class World;

class Ghost : public Entity {
protected:
    double moveCooldown = 1.0/60;
    float moveTimer = 0.0f;
    double speed = 1.0;
    float lastMoveTime = 0.0f;

    bool chasing = false;
    float chaseDelay = 0.0f;
    float timeAlive = 0.0f;

public:
    Ghost(float x, float y, char sym = 'G', float delay = 0.0f)
        : Entity(x, y, sym), chaseDelay(delay) {}

    void update(float deltaTime, World& world, const Pacman& pacman) override;
    double getSpeed() const;
    void setSpeed(double spd);
    void addMoveTime(float dt);
    bool readyToMove() const;
    void resetMoveTimer();
    bool readyToMove(float currentTime) const;

    void setDirection(char direct);
    void recordMoveTime(float currentTime);

    bool isChasing() const { return chasing; }
    void setChasing(bool value) { chasing = value; }
    float getChaseDelay() const { return chaseDelay; }

    void moveInDirection(World& world);
};

// RedGhost: Locked direction ghost, reconsiders at intersections
class RedGhost : public Ghost {
private:
    char lockedDirection;

public:
    RedGhost(float x, float y);
    void update(float deltaTime, World& world, const Pacman& pacman) override;
    void chooseDirection(const Pacman& pacman);
};

// BlueGhost: Follows position "in front of" Pacman
class BlueGhost : public Ghost {
public:
    BlueGhost(float x, float y, float delay);
    void update(float deltaTime, World& world, const Pacman& pacman) override;
    void chooseDirection(World& world, const Pacman& pacman);
};

// PinkGhost: Chases Pacman directly
class PinkGhost : public Ghost {
public:
    PinkGhost(float x, float y, float delay);
    void update(float deltaTime, World& world, const Pacman& pacman) override;
    void chooseDirection(World& world, const Pacman& pacman);
};

#endif //GHOST_H