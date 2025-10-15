#pragma once
#include <SFML/Graphics.hpp>

class StateManager;

class State {
public:
    virtual ~State() = default;
    virtual void handleInput(StateManager& manager, sf::RenderWindow& window) = 0;
    virtual void update(StateManager& manager, float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};
