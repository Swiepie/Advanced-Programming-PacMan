
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "../logic/Scoreboard.h"
#include "../logic/entities/EntityFactory.h"
#include "LevelState.h"
#include "State.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>

class MenuState : public State {
private:
    sf::Font font;
    sf::Text title;
    sf::Text highscores;
    Scoreboard sb;
    std::shared_ptr<EntityFactory> factory;

public:
    explicit MenuState(std::shared_ptr<EntityFactory> factory) : factory(std::move(factory)) {
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

    void handleEvent(std::shared_ptr<StateManager> stateManager, std::shared_ptr<sf::RenderWindow> window,
                     const sf::Event& event) override;
    void update(std::shared_ptr<StateManager> stateManager, float deltaTime) override {}
    void render(std::shared_ptr<sf::RenderWindow> window, unsigned int windowWidth, unsigned int windowHeight) override;
};

#endif