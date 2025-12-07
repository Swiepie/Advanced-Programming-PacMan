//
// Created by siebe on 22/09/2025.
//

#include "Entity.h"
#include <iostream>
#include <cmath>
coord Entity::getPosition() const {
    return position;
}

void Entity::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}
void Entity::update(float deltaTime) {

}

bool Entity::collidesWith(const Entity& other, float stepW, float stepH) const {

    return (std::fabs(position.x - other.getPosition().x) < stepW && std::fabs(position.y - other.getPosition().y) < stepH);
}


bool Entity::isCollectible() const {
    return false;
}

void Entity::onCollect(World& world) {

}

double Entity::getSpeed() const {
    return speed;
}

void Entity::setSpeed(double spd) {
    speed = spd;
    speedSave = spd;
}