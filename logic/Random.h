//
// Created by Siebe Haché on 14/10/2025.
//

#ifndef RANDOM_H
#define RANDOM_H

#include <array>
#include <chrono>
#include <random>

class Random {
private:
    std::mt19937 engine;

    // Private constructor to enforce singleton
    Random() {
        // Gebruik een random_device om een echte willekeurige seed te verkrijgen
        std::random_device rd;
        std::seed_seq seedSeq{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
        engine.seed(seedSeq);
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
    std::mt19937& getEngine();
};

#endif // RANDOM_H
