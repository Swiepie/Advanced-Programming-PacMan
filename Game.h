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
class Game {
private:
    sf::RenderWindow window;
    StateManager stateManager;
    int framerate = 20;
public:
    Game();
    void run();
};



#endif //GAME_H
