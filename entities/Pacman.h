//
// Created by siebe on 22/09/2025.
//

#ifndef PACMAN_H
#define PACMAN_H

#include "Entity.h"
#include "../Stopwatch.h"
class Pacman: public Entity {
private:
    char direction;

public:

    public:
    Pacman(float x, float y) : Entity(x, y, 'P') {
        direction = 'O';
    }

    void update(float deltaTime) override;

    char getDirection() const;
    void setDirection(char direct);
};



#endif //PACMAN_H
