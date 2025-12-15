//
// Created by siebe on 15/11/2025.
//

#ifndef FINISHSTATE_H
#define FINISHSTATE_H

#include "../logic/World.h"
#include "LevelState.h"
#include "MenuState.h"
#include "State.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>

class FinishState : public State {
private:
    std::shared_ptr<EntityFactory> factory;

    sf::Font font;
    sf::Text title;
    int finalScore = 0;
    void updateText();

public:
    explicit FinishState(int score, std::shared_ptr<EntityFactory> factory)
        : finalScore(score), factory(std::move(factory)) {
        font.loadFromFile("../assets/ARIAL.TTF");
        title.setFont(font);
        title.setFillColor(sf::Color::Green);
        updateText();
    }

    void handleEvent(std::shared_ptr<StateManager> stateManager, std::shared_ptr<sf::RenderWindow> window,
                     const sf::Event& event) override;
    void update(std::shared_ptr<StateManager> stateManager, float deltaTime) override {}
    void render(std::shared_ptr<sf::RenderWindow> window, unsigned int windowWidth, unsigned int windowHeight) override;
    void onEnter() override;
};

#endif // FINISHSTATE_H
