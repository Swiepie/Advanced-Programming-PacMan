//
// Created by Siebe Haché on 15/10/2025.
//

#include "MenuState.h"
#include "StateManager.h"
#include "LevelState.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

void MenuState::handleEvent(StateManager& manager, sf::RenderWindow& window, const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        manager.pushState(std::make_unique<LevelState>()); // go to the level
    } else if (event.type == sf::Event::Closed) {
        window.close();
    }
}
void MenuState::render(sf::RenderWindow& window,unsigned int windowWidth, unsigned int windowHeight) {
    window.draw(title);
}