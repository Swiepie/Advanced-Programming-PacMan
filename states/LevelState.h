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
#include "FinishState.h"
#include <SFML/Window/Event.hpp>
#include "../entities/Pacman.h"
#include "../Stopwatch.h"
#include <iostream>


class LevelState : public State {
private:
    World world;
    WorldView renderer;

    sf::Font font;
    sf::Text lives;
    sf::Text score;
public:
    LevelState() {
        world.loadMap("../assets/map.txt");
        world.printMap();

        font.loadFromFile("../assets/ARIAL.TTF");
        score.setFont(font);
        score.setString("score: " + std::to_string(world.getScore()));
        score.setFillColor(sf::Color::Yellow);

        lives.setFont(font);
        lives.setString("lives: " + std::to_string(world.getPacmanLives()));
        lives.setFillColor(sf::Color::Green);
    }

    void handleEvent(StateManager& manager, sf::RenderWindow& window, const sf::Event& event) override;
    void update(StateManager& manager, float deltaTime) override;
    void render(sf::RenderWindow& window, unsigned int windowWidth, unsigned int windowHeight) override;
    void onEnter() override;
    void onExit() override;
};
