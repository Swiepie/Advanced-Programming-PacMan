//
// Created by Siebe Haché on 15/10/2025.
//
#pragma once
#include "../logic/Stopwatch.h"
#include "../logic/World.h"
#include "../logic/entities/Pacman.h"
#include "../renderer/Camera.h"
#include "../renderer/WorldView.h"
#include "FinishState.h"
#include "MenuState.h"
#include "PausedState.h"
#include "State.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <utility>

class World;
class LevelState : public State {
private:
    std::shared_ptr<EntityFactory> factory;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<World> world;
    WorldView renderer;

    sf::Font font;
    sf::Text lives;
    sf::Text score;

public:
    explicit LevelState(const std::shared_ptr<EntityFactory>& factory)
        : factory(factory), world(std::make_shared<World>(factory)) {
        world->loadMap("../assets/map2.txt");
        world->printMap();
        font.loadFromFile("../assets/ARIAL.TTF");

        score.setFont(font);
        score.setString("score: " + std::to_string(world->getScore().get()));
        score.setFillColor(sf::Color::Yellow);

        lives.setFont(font);
        lives.setString("lives: " + std::to_string(world->getPacmanLives()));

        lives.setFillColor(sf::Color::Green);
    }

    void handleEvent(std::shared_ptr<StateManager> stateManager, std::shared_ptr<sf::RenderWindow> window,
                     const sf::Event& event) override;
    void update(std::shared_ptr<StateManager> stateManager, float deltaTime) override;
    void render(std::shared_ptr<sf::RenderWindow> window, unsigned int windowWidth, unsigned int windowHeight) override;
    void onEnter() override;
    void onExit() override;
};
