#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class StateManager;

class State {
public:
  virtual ~State() = default;
  virtual void handleEvent(std::shared_ptr<StateManager> stateManager,
                           std::shared_ptr<sf::RenderWindow> window,
                           const sf::Event &event) = 0;
  virtual void update(std::shared_ptr<StateManager> stateManager,
                      float deltaTime) = 0;
  virtual void render(std::shared_ptr<sf::RenderWindow> window,
                      unsigned int windowWidth, unsigned int windowHeight) = 0;
  virtual void onEnter() {};
  virtual void onExit() {};
};
