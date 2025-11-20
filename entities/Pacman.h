//
// Created by siebe on 22/09/2025.
//

#ifndef PACMAN_H
#define PACMAN_H

#include <iostream>

#include "Entity.h"
#include "../Stopwatch.h"
class Pacman : public Entity {
private:
    char direction;
    char bufferdirection;
    float moveTimer = 0.0f;
    double speed = 4;
    float lastMoveTime = 0.0f;


public:
    Pacman(float x, float y) : Entity(x, y, 'P'), direction('O') {}


    void update(float deltaTime) override;
    double getSpeed() const;
    void setSpeed(double spd);
    void addMoveTime(float dt);
    bool readyToMove() const;
    void resetMoveTimer();
    bool readyToMove(float currentTime) const;
    void recordMoveTime(float currentTime);
    char getBufferdirection() const;
    void setBufferdirection(char direct);
    void applyBufferdirection();
    char getDirection() const override;
    void setDirection(char direct);
    float getmoveCooldown() const;
};


#endif //PACMAN_H
