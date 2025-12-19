/**
 * @file PausedState.h
 * @brief Definieert de pauze state voor het spel
 * @author Siebe Haché
 * @date 28/10/2025
 */

#ifndef PAUSEDSTATE_H
#define PAUSEDSTATE_H

#include "LevelState.h"
#include "MenuState.h"
#include "State.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>

/**
 * @class PausedState
 * @brief State klasse voor het pauze scherm van het spel
 *
 * Toont een pauze scherm wanneer het spel gepauzeerd is. Erft van State
 * en implementeert het State pattern voor spel flow management.
 * Biedt de mogelijkheid om het spel te hervatten via spatiebalk.
 */
class PausedState : public State {
private:
    sf::Font font;  ///< SFML font voor tekst rendering
    sf::Text title; ///< Titel tekst voor het pauze scherm

public:
    /**
     * @brief Construeert een PausedState
     *
     * Initialiseert het pauze scherm, laadt het lettertype en
     * stelt de pauze tekst in met instructies om het spel te hervatten.
     */
    PausedState() {
        font.loadFromFile("../assets/ARIAL.TTF");
        title.setFont(font);
        title.setString("PAUSED\nPress SPACE to start");
        title.setFillColor(sf::Color::Red);
    }

    /**
     * @brief Verwerkt invoer events in de pauze staat
     * @param stateManager Gedeelde pointer naar de StateManager voor state overgangen
     * @param window Gedeelde pointer naar het render venster
     * @param event SFML event die verwerkt moet worden
     *
     * Behandelt speler input zoals spatiebalk om het spel te hervatten.
     */
    void handleEvent(std::shared_ptr<StateManager> stateManager, std::shared_ptr<sf::RenderWindow> window,
                     const sf::Event& event) override;

    /**
     * @brief Update de pauze state logica per frame
     * @param stateManager Gedeelde pointer naar de StateManager
     * @param deltaTime Delta tijd sinds vorige frame in seconden
     *
     * Lege implementatie - pauze scherm heeft geen actieve update logica.
     */
    void update(std::shared_ptr<StateManager> stateManager, float deltaTime) override {}

    /**
     * @brief Rendert het pauze scherm naar het venster
     * @param window Gedeelde pointer naar het render venster
     * @param windowWidth Breedte van het venster in pixels
     * @param windowHeight Hoogte van het venster in pixels
     *
     * Tekent de gecentreerde pauze tekst op het scherm.
     */
    void render(std::shared_ptr<sf::RenderWindow> window, unsigned int windowWidth, unsigned int windowHeight) override;

    /**
     * @brief Wordt aangeroepen bij het betreden van de pauze staat
     *
     * Print een debug bericht naar de console wanneer het pauze scherm actief wordt.
     */
    void onEnter() override;

    /**
     * @brief Wordt aangeroepen bij het verlaten van de pauze staat
     *
     * Print een debug bericht naar de console wanneer het pauze scherm verlaten wordt.
     */
    void onExit() override;
};

#endif // PAUSEDSTATE_H
