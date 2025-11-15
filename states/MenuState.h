
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "LevelState.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

class MenuState : public State {
private:
    sf::Font font;
    sf::Text title;

public:
    MenuState() {
        font.loadFromFile("../assets/ARIAL.TTF");
        title.setFont(font);
        title.setString("PAC-MAN PROJECT\nPress any key to play");
        title.setFillColor(sf::Color::Yellow);
    }

    void handleEvent(StateManager& manager, sf::RenderWindow& window, const sf::Event& event) override;
    void update(StateManager& manager, float deltaTime) override {}
    void render(sf::RenderWindow& window,unsigned int windowWidth, unsigned int windowHeight) override;
};

#endif