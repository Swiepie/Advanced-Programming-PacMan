//
// Created by Siebe Haché on 28/10/2025.
//

#include "PausedState.h"

//
// Created by Siebe Haché on 15/10/2025.
//



void PausedState::handleEvent(StateManager& manager, sf::RenderWindow& window, const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        manager.popState(); // go to the level
    } else if (event.type == sf::Event::Closed) {
        window.close();
    }
}
void PausedState::render(sf::RenderWindow& window,unsigned int windowWidth, unsigned int windowHeight) {
    window.draw(title);
}
void PausedState::onEnter() {
    Stopwatch::getInstance().pause(); // reset + start timer when entering game
    std::cout << "paused\n";
}
void PausedState::onExit() {
    Stopwatch::getInstance().start(); // stop when leaving
    std::cout << "Level paused. Final time: "
              << Stopwatch::getInstance().GetElapsedTime() << "s\n";
}