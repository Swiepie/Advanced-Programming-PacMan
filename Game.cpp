#include "Game.h"



#include "states/MenuState.h"

Game::Game()
    : window(sf::VideoMode(800, 550), "Pac-Man")
{
    Stopwatch::getInstance().start();
    window.setFramerateLimit(60);
    stateManager.pushState(std::make_unique<MenuState>());
}


void Game::run() {
    while (window.isOpen()) {

        float deltaTime = Stopwatch::getInstance().GetElapsedTime();
        State* current = stateManager.currentState();

        sf::Event event{};
        unsigned int windowWidth = window.getSize().x;
        unsigned int windowHeight = window.getSize().y;
        while (window.pollEvent(event)) {
            if (current)
                current->handleEvent(stateManager, window, event);
            if (event.type == sf::Event::Resized) {
                windowWidth = event.size.width;
                windowHeight = event.size.height;
            }
        }

        if (current) {
            current->update(stateManager, deltaTime);
        }

        window.clear(sf::Color::Black);
        if (current){
            current->render(window, windowWidth, windowHeight);
        }

        window.display();
        stateManager.processStateChanges();
    }
}

