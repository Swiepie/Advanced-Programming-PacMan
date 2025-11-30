
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Scoreboard.h"
#include "LevelState.h"
#include <SFML/Window/Event.hpp>
#include <iostream>

class MenuState : public State {
private:
    sf::Font font;
    sf::Text title;
    sf::Text highscores;
    Scoreboard sb;

public:
    MenuState() : sb("highscores.txt") {
        sb.load();

        font.loadFromFile("../assets/ARIAL.TTF");

        title.setFont(font);
        title.setString("PAC-MAN PROJECT\nPress any key to play");
        title.setFillColor(sf::Color::Yellow);

        highscores.setFont(font);
        highscores.setFillColor(sf::Color::Green);

        // top5 ophalen
        auto top = sb.getTop5();

        std::string hs = "Highscores:\n";
        for (int s : top) {
            hs += std::to_string(s) + "\n";
        }
        highscores.setString(hs);
    }


    void handleEvent(StateManager& manager, sf::RenderWindow& window, const sf::Event& event) override;
    void update(StateManager& manager, float deltaTime) override {}
    void render(sf::RenderWindow& window,unsigned int windowWidth, unsigned int windowHeight) override;
};

#endif