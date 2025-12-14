//
// Created by siebe on 22/09/2025.
//

#include "Entity.h"
#include <cmath>
#include <iostream>
coord Entity::getPosition() const { return position; }

void Entity::setPosition(float x, float y) {
  position.x = x;
  position.y = y;
  notify();
}
void Entity::update(float deltaTime) { notify(); }

bool Entity::collidesWith(const Entity &other, float stepW, float stepH) const {
  float w = stepW;
  float h = stepH;

  float x1 = position.x;
  float y1 = position.y;
  float x2 = other.getPosition().x;
  float y2 = other.getPosition().y;

  bool separated =
      x1 + w <= x2 || // pacman rechts niet voorbij andere links
      x2 + w <= x1 || // andere rechts niet voorbij pacman links
      y1 + h <= y2 || // pacman onderkant niet voorbij andere bovenkant
      y2 + h <= y1;   // andere onderkant niet voorbij pacman bovenkant

  return !separated;
}

bool Entity::isCollectible() const { return false; }

void Entity::onCollect(World &world) {}

float Entity::getSpeed() const { return speed; }

void Entity::setSpeed(double spd) {
  speed = spd;
  speedSave = spd;
}
void Entity::setSpawn(float x, float y) {
  spawn.x = x;
  spawn.y = y;
}
void Entity::resetToSpawn() { setPosition(spawn.x, spawn.y); }