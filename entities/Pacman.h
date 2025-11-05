//
// Created by siebe on 22/09/2025.
//

#ifndef PACMAN_H
#define PACMAN_H

#include "Entity.h"
#include "../Stopwatch.h"
class Pacman : public Entity {
private:
    char direction;
    char bufferdirection;
    double moveCooldown = 1.0/120;
    float moveTimer = 0.0f;
    double speed = 1.2;


public:
    Pacman(float x, float y) : Entity(x, y, 'P'), direction('O') {}

    void addMoveTime(float dt) { moveTimer += dt; }
    bool readyToMove() const { return moveTimer >= moveCooldown; }
    void resetMoveTimer() { moveTimer = 0.0f; }
    void update(float deltaTime) override;

    double getSpeed() const;
    void setSpeed(double spd);

    char getBufferdirection() const;
    void setBufferdirection(char direct);
    void applyBufferdirection();
    char getDirection() const;
    void setDirection(char direct);
};


#endif //PACMAN_H
