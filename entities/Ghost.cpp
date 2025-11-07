//
// Created by Siebe Haché on 07/11/2025.
//

#include "Ghost.h"
void Ghost::update(float deltaTime) {

}
char Ghost::getDirection() const {
    return direction;
}
void Ghost::setDirection(char direct) {
    direction = direct;
}
double Ghost::getSpeed() const {
    return speed;
}
void Ghost::setSpeed(double spd) {
    speed = spd;
}