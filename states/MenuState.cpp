//
// Created by Siebe Haché on 15/10/2025.
//

#include "MenuState.h"

void MenuState::handleEvent(StateManager& manager, sf::RenderWindow& window, const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        manager.pushState(std::make_unique<LevelState>()); // go to the level
    } else if (event.type == sf::Event::Closed) {
        window.close();
    }
}
void MenuState::render(sf::RenderWindow& window,unsigned int windowWidth, unsigned int windowHeight) {
    window.draw(title);
}