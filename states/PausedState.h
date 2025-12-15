//
// Created by Siebe Haché on 28/10/2025.
//

#ifndef PAUSEDSTATE_H
#define PAUSEDSTATE_H

#include "LevelState.h"
#include "MenuState.h"
#include "State.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>

class PausedState : public State {
private:
    sf::Font font;
    sf::Text title;

public:
    PausedState() {
        font.loadFromFile("../assets/ARIAL.TTF");
        title.setFont(font);
        title.setString("PAUSED\nPress SPACE to start");
        title.setFillColor(sf::Color::Red);
    }

    void handleEvent(std::shared_ptr<StateManager> stateManager, std::shared_ptr<sf::RenderWindow> window,
                     const sf::Event& event) override;
    void update(std::shared_ptr<StateManager> stateManager, float deltaTime) override {}
    void render(std::shared_ptr<sf::RenderWindow> window, unsigned int windowWidth, unsigned int windowHeight) override;
    void onEnter() override;
    void onExit() override;
};

#endif // PAUSEDSTATE_H
