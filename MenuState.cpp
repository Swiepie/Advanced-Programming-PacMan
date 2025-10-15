//
// Created by Siebe Haché on 15/10/2025.
//

#include "MenuState.h"
#include "StateManager.h"
#include "LevelState.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

void MenuState::handleInput(StateManager& manager, sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            std::cout << "Starting game...\n";
            manager.pushState(std::make_unique<LevelState>());
        }
    }
}
