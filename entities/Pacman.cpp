//
// Created by siebe on 22/09/2025.
//

#include "Pacman.h"
void Pacman::update(float deltaTime) {

}
char Pacman::getDirection() const {
    return direction;
}
void Pacman::setDirection(char direct) {
    direction = direct;
}
char Pacman::getBufferdirection() const {
    return bufferdirection;
}
void Pacman::setBufferdirection(char direct) {
    bufferdirection = direct;
}
void Pacman::applyBufferdirection() {
    direction = bufferdirection;
}
void Pacman::addMoveTime(float dt) {
    moveTimer += dt;
}
bool Pacman::readyToMove() const {
    return moveTimer >= moveCooldown;
}
void Pacman::resetMoveTimer() {
    moveTimer -= moveCooldown;
}
bool Pacman::readyToMove(float currentTime) const {
    return (currentTime - lastMoveTime) >= moveCooldown;
}

void Pacman::recordMoveTime(float currentTime) {
    lastMoveTime = currentTime;
}

float Pacman::getmoveCooldown() const {
    return moveCooldown;
}
void Pacman::accept(Visitor& visitor) {
    visitor.visit(*this);
}
