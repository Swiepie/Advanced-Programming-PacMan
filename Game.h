//
// Created by Siebe Haché on 14/10/2025.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "states/StateManager.h"
#include "logic/Stopwatch.h"
#include <iostream>
#include <memory>
#include "logic/entities/EntityFactory.h"
struct FileDimensions {
    std::size_t width;
    std::size_t height;
};

class Game {
private:
    std::shared_ptr<sf::RenderWindow> window;
    StateManager stateManager;
    int framerate = 60;
public:
    static FileDimensions getFileDimensions(const std::string& filename);
    Game();
    void run();
};



#endif //GAME_H
