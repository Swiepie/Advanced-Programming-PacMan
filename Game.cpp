#include "Game.h"
#include "MenuState.h"

Game::Game()
    : window(sf::VideoMode(1000, 550), "Pac-Man Project")
{
    window.setFramerateLimit(1);
    stateManager.pushState(std::make_unique<MenuState>());
}

void Game::run() {
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        State* current = stateManager.currentState();
        if (current) {
            current->handleInput(stateManager, window);
            current->update(stateManager, deltaTime);
            current->render(window);
        }

        stateManager.processStateChanges(); // Dit is om sigsevs te voorkomen zodat de state niet al verwijdert wordt
    }
}

