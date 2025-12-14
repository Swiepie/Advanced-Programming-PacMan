//
// Created by siebe on 22/09/2025.
//

#ifndef ENTITY_H
#define ENTITY_H




#include <string>
#include <memory>
#include "Subject.h"
struct coord {
    float x, y;
};
class Visitor;
class Pacman;
class World;
class Entity : public Subject{
protected:
    double speed = 2.5;
    double speedSave = 1;
    double fearSpeed = 1.5;
    float moveCooldown;
    coord position;
    char direction;
    bool hasBeenEaten = false;
    coord spawn;
    bool frozen = false;
    float respawnTimer;
public:
    virtual ~Entity() = default;
    Entity(float x, float y) : position{x, y} {}


    virtual void accept(Visitor& visitor) = 0;
    coord getPosition() const;
    void setPosition(float x, float y);
    virtual void update(float deltaTime);

    bool collidesWith(const Entity& other, float stepW = 0.05f, float stepH = 0.05f) const;

    virtual bool isCollectible() const;
    virtual void onCollect(World& world);

    virtual void update(float deltaTime, World& world, const Pacman& pacman) {}

    void setSpawn(float x, float y);
    void resetToSpawn();

    double getSpeed() const;
    void setSpeed(double spd);

};



#endif //ENTITY_H
