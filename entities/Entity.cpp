//
// Created by siebe on 22/09/2025.
//

#include "Entity.h"
#include <iostream>
#include <cmath>
coord Entity::getPosition() const {
    return position; }
char Entity::getSymbol() const {
    return symbol;
}
void Entity::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}
void Entity::update(float deltaTime) {

}

bool Entity::collidesWith(const Entity& other, float stepW, float stepH) const {
    //std::cout << "entity: Pacman(" << position.x << ", " << position.y << ") vs "
              //<< other.getSymbol() << "(" << other.getPosition().x << ", " << other.getPosition().y << ")\n";
    //std::cout << "Δx = " << std::fabs(position.x - other.getPosition().x)
              //<< ", Δy = " << std::fabs(position.y - other.getPosition().y)
              //<< " | stepW=" << stepW << " stepH=" << stepH << "\n";

    return (std::fabs(position.x - other.getPosition().x) < stepW && std::fabs(position.y - other.getPosition().y) < stepH);
}


bool Entity::isCollectible() const {
    return false;
}

void Entity::onCollect(Pacman& pacman) {

}