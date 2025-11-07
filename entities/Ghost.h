//
// Created by Siebe Haché on 07/11/2025.
//

#ifndef GHOST_H
#define GHOST_H

#include "Entity.h"

class Ghost : public Entity{
private:
    char direction;
    char bufferdirection;
    double moveCooldown = 1.0/30;
    float moveTimer = 0.0f;
    double speed = 1;
    float lastMoveTime = 0.0f;
public:
    Ghost(float x, float y) : Entity(x, y, 'g') {

    }
    
};

class RedGhost : public Ghost {
    public:

};
class BlueGhost : public Ghost {

    public:

};


#endif //GHOST_H
