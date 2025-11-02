//
// Created by Siebe Haché on 15/10/2025.
//

#ifndef WALL_H
#define WALL_H



#include "Entity.h"

class Wall : public Entity {
public:
    Wall(float x, float y) : Entity(x, y, '#') {}
};


#endif //WALL_H
