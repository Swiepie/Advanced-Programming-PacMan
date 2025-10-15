//
// Created by Siebe Haché on 15/10/2025.
//

#include "State.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>

class LevelState : public State {
private:
    sf::Font font;
    sf::Text label;

public:
    LevelState() {
        font.loadFromFile("../assets/ARIAL.TTF");
        label.setFont(font);
        label.setString("LEVEL 1\nPress ESC to return to menu");
        label.setCharacterSize(40);
        label.setFillColor(sf::Color::Cyan);
        label.setPosition(100, 200);
    }

    void handleInput(StateManager& manager, sf::RenderWindow& window) override;
    void update(StateManager& manager, float deltaTime) override {}
    void render(sf::RenderWindow& window) override {
        window.clear(sf::Color::Black);
        window.draw(label);
        window.display();
    }
};
