//
// Created by Siebe Haché on 15/10/2025.
//
#pragma once
#include "State.h"
#include "PausedState.h"
#include "../World.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>
#include "../renderer/WorldView.h"
#include "MenuState.h"
#include <SFML/Window/Event.hpp>
#include "../entities/Pacman.h"
#include "../Stopwatch.h"
#include <iostream>


class LevelState : public State {
private:
    World world;
    WorldView renderer;
public:
    LevelState() {
        world.loadMap("../assets/map2.txt");
        world.printMap();
    }

    void handleEvent(StateManager& manager, sf::RenderWindow& window, const sf::Event& event) override;
    void update(StateManager& manager, float deltaTime) override;
    void render(sf::RenderWindow& window, unsigned int windowWidth, unsigned int windowHeight) override;
    void onEnter() override;
    void onExit() override;
};
