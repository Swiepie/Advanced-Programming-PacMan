//
// Created by Siebe Haché on 15/10/2025.
//

#include "LevelState.h"
#include "MenuState.h"
#include <SFML/Window/Event.hpp>

void LevelState::handleEvent(StateManager& manager, sf::RenderWindow& window, const sf::Event& event) {
        if (event.type == sf::Event::Closed)
            window.close();
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            manager.popState(); // back to menu
}

void LevelState::update(StateManager& manager, float deltaTime)  {
    world.update(deltaTime);
}
void LevelState::render(sf::RenderWindow& window, unsigned int windowWidth, unsigned int windowHeight)  {
    renderer.render(world, window, windowWidth, windowHeight);
}