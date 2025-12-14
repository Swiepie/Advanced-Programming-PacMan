//
// Created by Siebe Haché on 14/10/2025.
//

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

class Stopwatch {
private:
  Stopwatch() : running(false), paused(false) {}
  bool running;
  bool paused;
  std::chrono::steady_clock::time_point startTime;
  std::chrono::steady_clock::duration elapsed{};

public:
  static Stopwatch &getInstance() {
    static Stopwatch instance; // één instantie in het hele programma
    return instance;
  }
  Stopwatch(const Stopwatch &) = delete;
  Stopwatch &operator=(const Stopwatch &) = delete;
  void start();
  void stop();
  void pause();
  void reset();
  void restart();
  float GetElapsedTime() const;
};

#endif // STOPWATCH_H
