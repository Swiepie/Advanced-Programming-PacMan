//
// Created by siebe on 22/09/2025.
//

#ifndef PACMAN_H
#define PACMAN_H

#include "Entity.h"
#include "../Stopwatch.h"
class Pacman: public Entity {
    public:
    Pacman(float x, float y) : Entity(x, y, 'P') {}
};



#endif //PACMAN_H
