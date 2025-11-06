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
double Pacman::getSpeed() const {
    return speed;
}
void Pacman::setSpeed(double spd) {
    speed = spd;
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