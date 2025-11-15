//
// Created by Siebe Haché on 28/10/2025.
//

#ifndef PAUSEDSTATE_H
#define PAUSEDSTATE_H

#include "State.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "MenuState.h"
#include "StateManager.h"
#include "LevelState.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

class PausedState: public State {
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

    void handleEvent(StateManager& manager, sf::RenderWindow& window, const sf::Event& event) override;
    void update(StateManager& manager, float deltaTime) override {}
    void render(sf::RenderWindow& window,unsigned int windowWidth, unsigned int windowHeight) override;
    void onEnter() override;
    void onExit() override;
};



#endif //PAUSEDSTATE_H
