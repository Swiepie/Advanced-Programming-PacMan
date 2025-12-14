//
// Created by Siebe Haché on 14/10/2025.
//

#ifndef GAME_H
#define GAME_H

#include "logic/Stopwatch.h"
#include "logic/entities/EntityFactory.h"
#include "states/StateManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
struct FileDimensions {
  std::size_t width;
  std::size_t height;
};

class Game {
private:
  std::shared_ptr<sf::RenderWindow> window;
  std::shared_ptr<StateManager> stateManager;
  int framerate = 60;

public:
  static FileDimensions getFileDimensions(const std::string &filename);
  Game();
  void run() const;
};

#endif // GAME_H
