//
// Created by Siebe Haché on 14/10/2025.
//

#include "Random.h"
Random& Random::getInstance() {
    static Random instance;
    return instance;
}
int Random::getInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(engine);
}
float Random::getFloat(float min, float max) {
    std::uniform_real_distribution<float> dist(min, max);
    return dist(engine);
}
char Random::getRandomDirection() {
    static const std::array<char, 4> directions = { 'N', 'Z', 'O', 'W' };
    std::uniform_int_distribution<int> dist(0, 3);
    return directions[dist(engine)];
}

std::mt19937& Random::getEngine() {
    return engine;
}