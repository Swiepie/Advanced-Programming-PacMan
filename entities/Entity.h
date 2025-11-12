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

class Pacman;
class World;
class Entity {
protected:
    coord position;
    char symbol;
    char direction;
public:
    Entity(float x, float y, char sym) : position{x, y}, symbol(sym) {}
    virtual ~Entity() = default;

    coord getPosition() const;
    char getSymbol() const;
    void setPosition(float x, float y);
    virtual void update(float deltaTime);

    bool collidesWith(const Entity& other, float stepW = 0.05f, float stepH = 0.05f) const;

    virtual bool isCollectible() const;
    virtual void onCollect(World& world);

    virtual char getDirection() const { return direction; }

    virtual void update(float deltaTime, World& world, const Pacman& pacman) {}

};



#endif //ENTITY_H
