
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
        font.loadFromFile("../assets/ARIAL.TTF"); // Zorg dat dit pad klopt
        title.setFont(font);
        title.setString("PAC-MAN PROJECT\nPress SPACE to play");
        title.setCharacterSize(40);
        title.setFillColor(sf::Color::Yellow);
        title.setPosition(150, 200);
    }

    void handleInput(StateManager& manager, sf::RenderWindow& window) override;
    void update(StateManager& manager, float deltaTime) override {}
    void render(sf::RenderWindow& window) override {
        window.clear(sf::Color::Black);
        window.draw(title);
        window.display();
    }
};

#endif