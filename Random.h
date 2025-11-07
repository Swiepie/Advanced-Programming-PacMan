//
// Created by Siebe Haché on 14/10/2025.
//

#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <chrono>
#include <array>

class Random {
private:
    std::mt19937 engine;

    // Private constructor to enforce singleton
    Random() {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        engine.seed(static_cast<unsigned long>(seed));
    }

public:
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;

    static Random& getInstance();

    // Integer in range [min, max]
    int getInt(int min, int max);

    // Float in range [min, max]
    float getFloat(float min, float max);

    // Random direction for Pac-Man / Ghosts
    char getRandomDirection();

    // Optional: expose the engine if needed
    std::mt19937& getEngine() { return engine; }
};

#endif // RANDOM_H

