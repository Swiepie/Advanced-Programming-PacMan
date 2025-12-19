/**
 * @file LevelState.h
 * @brief Definieert de level state voor actieve gameplay
 * @author Siebe Haché
 * @date 15/10/2025
 */

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

/**
 * @class LevelState
 * @brief State klasse voor actieve gameplay tijdens een level
 *
 * Beheert de hoofdgameplay loop, inclusief world updates, rendering,
 * speler input en HUD elementen zoals score en levens. Erft van State
 * en implementeert het State pattern voor spel flow management.
 */
class LevelState : public State {
private:
    std::shared_ptr<EntityFactory> factory; ///< Factory voor het creëren van entiteiten
    std::shared_ptr<Camera> camera;         ///< Camera voor viewport transformaties
    std::shared_ptr<World> world;           ///< world met alle entiteiten en logica
    WorldView renderer;                     ///< Renderer voor de world

    sf::Font font;  ///< SFML font voor HUD tekst rendering
    sf::Text lives; ///< Tekst element voor levens weergave
    sf::Text score; ///< Tekst element voor score weergave

    std::string filename = "../assets/map.txt"; ///< Pad naar het te laden map bestand

public:
    /**
     * @brief Construeert een LevelState met opgegeven factory
     * @param factory Gedeelde pointer naar de EntityFactory voor entiteit creatie
     *
     * Initialiseert de world, laadt de map, en stelt HUD elementen in
     * voor score en levens weergave.
     */
    explicit LevelState(const std::shared_ptr<EntityFactory>& factory)
        : factory(factory), world(std::make_shared<World>(factory)) {
        world->loadMap(filename);
        world->printMap();
        font.loadFromFile("../assets/ARIAL.TTF");

        score.setFont(font);
        score.setString("score: " + std::to_string(world->getScore().get()));
        score.setFillColor(sf::Color::Yellow);

        lives.setFont(font);
        lives.setString("lives: " + std::to_string(world->getPacmanLives()));
        lives.setFillColor(sf::Color::Green);
    }

    /**
     * @brief Verwerkt invoer events tijdens gameplay
     * @param stateManager Gedeelde pointer naar de StateManager voor state overgangen
     * @param window Gedeelde pointer naar het render venster
     * @param event SFML event die verwerkt moet worden
     *
     * Behandelt speler input zoals beweging, pauze en andere gameplay acties.
     */
    void handleEvent(std::shared_ptr<StateManager> stateManager, std::shared_ptr<sf::RenderWindow> window,
                     const sf::Event& event) override;

    /**
     * @brief Update de level state logica per frame
     * @param stateManager Gedeelde pointer naar de StateManager
     * @param deltaTime Delta tijd sinds vorige frame in seconden
     *
     * Update de world, entiteiten, en controleert win/verlies condities.
     */
    void update(std::shared_ptr<StateManager> stateManager, float deltaTime) override;

    /**
     * @brief Rendert het level naar het venster
     * @param window Gedeelde pointer naar het render venster
     * @param windowWidth Breedte van het venster in pixels
     * @param windowHeight Hoogte van het venster in pixels
     *
     * Tekent de world, entiteiten en HUD elementen op het scherm.
     */
    void render(std::shared_ptr<sf::RenderWindow> window, unsigned int windowWidth, unsigned int windowHeight) override;

    /**
     * @brief Callback wanneer deze state actief wordt
     *
     * Voert initialisatie uit wanneer overgeschakeld wordt naar deze state.
     */
    void onEnter() override;

    /**
     * @brief Callback wanneer deze state verlaten wordt
     *
     * Voert cleanup uit voordat overgeschakeld wordt naar een andere state.
     */
    void onExit() override;
};
