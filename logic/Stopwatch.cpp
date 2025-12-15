//
// Created by Siebe Haché on 14/10/2025.
//

#include "Stopwatch.h"

void Stopwatch::start() {
    if (!running) {
        startTime = std::chrono::steady_clock::now();
        running = true;
        paused = false;
    }
}
void Stopwatch::stop() {
    if (running) {
        elapsed += std::chrono::steady_clock::now() - startTime;
        running = false;
        paused = false;
    }
}
void Stopwatch::pause() {
    if (running && !paused) {
        elapsed += std::chrono::steady_clock::now() - startTime;
        paused = true;
    }
}
void Stopwatch::reset() {
    running = false;
    elapsed = std::chrono::steady_clock::duration::zero();
}
void Stopwatch::restart() {
    reset();
    start();
}
float Stopwatch::GetElapsedTime() const {
    auto total = elapsed;
    if (running) {
        total += std::chrono::steady_clock::now() - startTime;
    }
    return std::chrono::duration<float>(total).count();
}