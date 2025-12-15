//
// Created by Siebe Haché on 28/10/2025.
//

#include "PausedState.h"

void PausedState::handleEvent(std::shared_ptr<StateManager> stateManager, std::shared_ptr<sf::RenderWindow> window,
                              const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        stateManager->popState(); // go to the level
    } else if (event.type == sf::Event::Closed) {
        window->close();
    }
}
void PausedState::render(std::shared_ptr<sf::RenderWindow> window, unsigned int windowWidth,
                         unsigned int windowHeight) {
    sf::Vector2f viewSize = window->getView().getSize();
    sf::Vector2f viewCenter = window->getView().getCenter();

    // schaal op basis van hoogte
    float preferredHeight = viewSize.y * 0.10f; // 10% van schermhoogte
    float textHeight = title.getLocalBounds().height;

    float scaleY = preferredHeight / textHeight;

    // controleer breedte
    float maxWidth = viewSize.x * 0.80f; // Tekst mag 80% van breedte nemen
    float textWidth = title.getLocalBounds().width;

    float scaleX = maxWidth / textWidth;

    // MIN
    float scale = std::min(scaleX, scaleY);

    title.setScale(scale, scale);

    // centreer tekst
    title.setOrigin(title.getLocalBounds().width / 2.f, title.getLocalBounds().height / 2.f);

    title.setPosition(viewCenter);
    window->draw(title);
}

void PausedState::onEnter() {
    Stopwatch::getInstance().pause(); // reset + start timer when entering game
    std::cout << "paused\n";
}
void PausedState::onExit() {
    Stopwatch::getInstance().start(); // stop when leaving
    std::cout << "Level paused. Final time: " << Stopwatch::getInstance().GetElapsedTime() << "s\n";
}