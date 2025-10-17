
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>


class MenuState : public State {
private:
    sf::Font font;
    sf::Text title;

public:
    MenuState() {
        font.loadFromFile("../assets/ARIAL.TTF");
        title.setFont(font);
        title.setString("PAC-MAN PROJECT\nPress SPACE to play");
        title.setCharacterSize(40);
        title.setFillColor(sf::Color::Yellow);
        title.setPosition(150, 200);
    }

    void handleEvent(StateManager& manager, sf::RenderWindow& window, const sf::Event& event) override;
    void update(StateManager& manager, float deltaTime) override {}
    void render(sf::RenderWindow& window,unsigned int windowWidth, unsigned int windowHeight) override;
};

#endif