//
// Created by siebe on 22/09/2025.
//

#ifndef ENTITY_H
#define ENTITY_H



#include <SFML/Graphics.hpp>

#include <string>
#include <memory>

struct coord {
    float x, y;
};

class Entity {
protected:
    coord position;
    char symbol;

public:
    Entity(float x, float y, char sym) : position{x, y}, symbol(sym) {}
    virtual ~Entity() = default;

    coord getPosition() const { return position; }
    char getSymbol() const { return symbol; }

    virtual void update(float deltaTime) {}
};



#endif //ENTITY_H
