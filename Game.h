//
// Created by Siebe Haché on 14/10/2025.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "states/StateManager.h"
#include "Stopwatch.h"
#include <iostream>
#include <memory>
#include "entities/EntityFactory.h"
class Game {
private:
    sf::RenderWindow window;
    StateManager stateManager;
    int framerate = 60;
public:
    Game();
    void run();
};



#endif //GAME_H
