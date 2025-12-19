/**
 * @file FinishState.h
 * @brief Definieert de finish state voor het einde van het spel
 * @author siebe
 * @date 15/11/2025
 */

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

/**
 * @class FinishState
 * @brief State klasse voor het einde-scherm van het spel
 *
 * Toont de eindstand en score wanneer het spel afgelopen is.
 * Erft van State en implementeert het State pattern voor spel flow management.
 * Biedt opties om terug te keren naar het hoofdmenu.
 */
class FinishState : public State {
private:
    std::shared_ptr<EntityFactory> factory; ///< Factory voor het creëren van entiteiten

    sf::Font font;      ///< SFML font voor tekst rendering
    sf::Text title;     ///< Titel tekst voor het eindscherm
    int finalScore = 0; ///< Eindstand van de speler

    /**
     * @brief Update de weergegeven tekst met de huidige score
     *
     * Helper methode om titel en score informatie bij te werken.
     */
    void updateText();

public:
    /**
     * @brief Construeert een FinishState met opgegeven score
     * @param score Eindstand van het voltooide spel
     * @param factory Gedeelde pointer naar de EntityFactory
     *
     * Initialiseert het eindscherm met de opgegeven score,
     * laadt het lettertype en stelt de tekst in.
     */
    explicit FinishState(int score, std::shared_ptr<EntityFactory> factory)
        : finalScore(score), factory(std::move(factory)) {
        font.loadFromFile("../assets/ARIAL.TTF");
        title.setFont(font);
        title.setFillColor(sf::Color::Green);
        updateText();
    }

    /**
     * @brief Verwerkt invoer events voor het eindscherm
     * @param stateManager Gedeelde pointer naar de StateManager voor state overgangen
     * @param window Gedeelde pointer naar het render venster
     * @param event SFML event die verwerkt moet worden
     *
     * Behandelt speler input zoals toetsaanslagen om terug te keren naar menu
     * of het spel af te sluiten.
     */
    void handleEvent(std::shared_ptr<StateManager> stateManager, std::shared_ptr<sf::RenderWindow> window,
                     const sf::Event& event) override;

    /**
     * @brief Update de state logica per frame
     * @param stateManager Gedeelde pointer naar de StateManager
     * @param deltaTime Delta tijd sinds vorige frame in seconden
     *
     * Lege implementatie - eindscherm heeft geen actieve update logica.
     */
    void update(std::shared_ptr<StateManager> stateManager, float deltaTime) override {}

    /**
     * @brief Rendert het eindscherm naar het venster
     * @param window Gedeelde pointer naar het render venster
     * @param windowWidth Breedte van het venster in pixels
     * @param windowHeight Hoogte van het venster in pixels
     *
     * Tekent de eindscore en eventuele aanvullende informatie op het scherm.
     */
    void render(std::shared_ptr<sf::RenderWindow> window, unsigned int windowWidth, unsigned int windowHeight) override;

    /**
     * @brief Callback wanneer deze state actief wordt
     *
     * Voert initialisatie uit wanneer overgeschakeld wordt naar deze state.
     */
    void onEnter() override;
};

#endif // FINISHSTATE_H