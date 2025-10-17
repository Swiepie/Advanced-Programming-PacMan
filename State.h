#pragma once
#include <SFML/Graphics.hpp>

class StateManager;

class State {
public:
    virtual ~State() = default;
    virtual void handleEvent(StateManager& manager, sf::RenderWindow& window, const sf::Event& event) = 0;
    virtual void update(StateManager& manager, float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window, unsigned int windowWidth, unsigned int windowHeight) = 0;
};
