//
// Created by Siebe Haché on 15/10/2025.
//

#include "LevelState.h"
#include "MenuState.h"
#include <SFML/Window/Event.hpp>

void LevelState::handleInput(StateManager& manager, sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            manager.popState(); // terug naar vorige state (menu)
        }
    }
}