//
// Created by Siebe Haché on 07/11/2025.
//

#ifndef GHOST_H
#define GHOST_H

#include "../Random.h"
#include "../World.h"
#include "Entity.h"
#include "Pacman.h"

class World;

class Ghost : public Entity {
protected:
    float moveTimer = 0.0f;
    float lastMoveTime = 0.0f;

    bool chasing = false;
    float chaseDelay = 0.0f;
    float ogChaseDelay = 0.0f;

    float timeAlive = 0.0f;

    float fearTime = 0.0f;
    float fearStartTime = 0.0f;
    bool inFearMode = false;

public:
    Ghost(float x, float y, float delay = 0.0f) : Entity(x, y), chaseDelay(delay), ogChaseDelay(delay) {
        speed = 2.5;
        speedSave = 1;
        fearSpeed = 1.5;
    }
    void softSnapToTileCenter(World& world);
    void update(float deltaTime, World& world, const Pacman& pacman) override;

    void setFearState(bool state);
    void resetFearState();
    bool getFearState() const;

    void addMoveTime(float dt);

    virtual char getDirection() const;

    bool getHasBeenEaten() const;
    void setHasBeenEaten(bool eaten);

    bool readyToMove(float currentTime) const;

    void setDirection(char direct);
    bool readyToMove() const;

    float getChaseDelay() const;

    void chooseDirectionFear(World& world, const Pacman& pacman);
    void reverseDirection();
    float getMoveCooldown() const;
    void reset();
};

// RedGhost: Locked direction ghost, reconsiders at intersections
class RedGhost : public Ghost {
private:
    char lockedDirection;

public:
    RedGhost(float x, float y);
    void update(float deltaTime, World& world, const Pacman& pacman) override;
    void chooseDirection(const Pacman& pacman);
    void accept(Visitor& visitor) override;
};

// BlueGhost: Follows position "in front of" Pacman
class BlueGhost : public Ghost {
public:
    BlueGhost(float x, float y, float delay);
    void update(float deltaTime, World& world, const Pacman& pacman) override;
    void chooseDirection(World& world, const Pacman& pacman);
    void accept(Visitor& visitor) override;
};

// PinkGhost: Chases Pacman directly
class PinkGhost : public Ghost {
public:
    PinkGhost(float x, float y, float delay);
    void update(float deltaTime, World& world, const Pacman& pacman) override;
    void chooseDirection(World& world, const Pacman& pacman);
    void accept(Visitor& visitor) override;
};

#endif // GHOST_H