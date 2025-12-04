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
class Visitor;
class Pacman;
class World;
class Entity {
protected:
    double speed = 2.5;
    double speedSave = 1;
    double fearSpeed = 1.5;
    float moveCooldown;
    coord position;
    char symbol;
    char direction;
    bool hasBeenEaten = false;
    coord spawn;
    bool frozen = false;
    float respawnTimer;
public:

    Entity(float x, float y, char sym) : position{x, y}, symbol(sym) {}
    virtual ~Entity() = default;

    virtual void accept(Visitor& visitor) = 0;
    coord getPosition() const;
    char getSymbol() const;
    void setPosition(float x, float y);
    virtual void update(float deltaTime);

    bool collidesWith(const Entity& other, float stepW = 0.05f, float stepH = 0.05f) const;

    virtual bool isCollectible() const;
    virtual void onCollect(World& world);

    virtual char getDirection() const { return direction; }

    bool getHasBeenEaten() const { return hasBeenEaten; }
    void setHasBeenEaten(bool val) { hasBeenEaten = val; }

    virtual void update(float deltaTime, World& world, const Pacman& pacman) {}
    virtual void resetFearState() {}
    virtual void setFearState(bool state)  {}
    virtual bool getFearState() const { return false; }
    virtual void softSnapToTileCenter(World& world) {}
    virtual void setMoveCooldown(float cooldown) {
        moveCooldown = cooldown;
    }
    void setSpawn(float x, float y) { spawn.x = x; spawn.y = y; }
    void resetToSpawn() { setPosition( spawn.x, spawn.y); }
    virtual void reset() {
    }
    void setFrozen(bool f) { frozen = f; }
    bool isFrozen() const { return frozen; }

    void setRespawnTimer(float t) { respawnTimer = t; setFrozen(t > 0.f); }
    void tickRespawnTimer(float dt) { if (respawnTimer > 0.f) { respawnTimer -= dt; if (respawnTimer <= 0.f) { respawnTimer = 0.f; setFrozen(false); } } }
    double getSpeed() const;
    void setSpeed(double spd);

};



#endif //ENTITY_H
