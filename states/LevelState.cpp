//
// Created by Siebe Haché on 15/10/2025.
//

#include "LevelState.h"


void LevelState::handleEvent(StateManager& manager, sf::RenderWindow& window, const sf::Event& event) {
    if (event.type == sf::Event::Closed)
        window.close();

    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            manager.pushState(std::make_unique<PausedState>()); // back to menu
        }
#if 1

        auto pacman = world.getPacman();
        if (!pacman) return;

        switch (event.key.code) {
            case sf::Keyboard::Up:    pacman->setBufferdirection('N'); break;
            case sf::Keyboard::Down:  pacman->setBufferdirection('Z'); break;
            case sf::Keyboard::Left:  pacman->setBufferdirection('W'); break;
            case sf::Keyboard::Right: pacman->setBufferdirection('O'); break;
            default: break;
        }
#endif

    }
}

void LevelState::update(StateManager& manager, float deltaTime)  {
    world.update(deltaTime);
}
void LevelState::render(sf::RenderWindow& window, unsigned int windowWidth, unsigned int windowHeight)  {
    renderer.render(world, window, windowWidth, windowHeight);
}

void LevelState::onEnter() {
    Stopwatch::getInstance().restart(); // reset + start timer when entering game
    std::cout << "Level started! Stopwatch running...\n";
}
void LevelState::onExit() {
    Stopwatch::getInstance().stop(); // stop when leaving
    std::cout << "Level ended. Final time: "
              << Stopwatch::getInstance().GetElapsedTime() << "s\n";
}