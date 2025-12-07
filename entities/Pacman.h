//
// Created by siebe on 22/09/2025.
//

#ifndef PACMAN_H
#define PACMAN_H

#include <iostream>

#include "Entity.h"
#include "../Stopwatch.h"
#include "../Visitor.h"
class Pacman : public Entity {
private:
    char direction;
    char bufferdirection;
    float moveTimer = 0.0f;
    float lastMoveTime = 0.0f;


public:
    Pacman(float x, float y) : Entity(x, y), direction(' ') {
        speed = 4;
    }


    void update(float deltaTime) override;
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
    void accept(Visitor& visitor) override;
};


#endif //PACMAN_H
