//
// Created by Siebe Haché on 14/10/2025.
//

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "StateManager.h"

class Game {
private:
    sf::RenderWindow window;
    StateManager stateManager;
    sf::Clock clock;

public:
    Game();
    void run();
};



#endif //GAME_H
