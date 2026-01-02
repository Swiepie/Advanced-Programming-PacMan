/**
 * @file MenuState.h
 * @brief Definieert de menu state voor het hoofdmenu
 * @author siebe
 * @date 15/11/2025
 */

#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "../logic/Scoreboard.h"
#include "../logic/entities/EntityFactory.h"
#include "LevelState.h"
#include "State.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>

/**
 * @class MenuState
 * @brief State klasse voor het hoofdmenu van het spel
 *
 * Toont het hoofdmenu met titel en top 5 highscores. Erft van State
 * en implementeert het State pattern voor spel flow management.
 * Biedt opties om het spel te starten of highscores te bekijken.
 */
class MenuState : public State {
private:
    sf::RectangleShape playButton; ///< Rechthoek voor play knop achtergrond
    sf::Text playButtonText;       ///< Tekst op de play knop

    sf::Font font;                          ///< SFML font voor tekst rendering
    sf::Text title;                         ///< Titel tekst voor het hoofdmenu
    sf::Text highscores;                    ///< Tekst voor highscores weergave
    Scoreboard sb;                          ///< Scoreboard voor highscore beheer
    std::shared_ptr<EntityFactory> factory; ///< Factory voor het creëren van entiteiten

public:
    /**
     * @brief Construeert een MenuState met opgegeven factory
     * @param factory Gedeelde pointer naar de EntityFactory
     *
     * Initialiseert het hoofdmenu, laadt highscores van disk,
     * stelt lettertype in en formatteert titel en top 5 highscores
     * voor weergave op het scherm.
     */
    explicit MenuState(std::shared_ptr<EntityFactory> factory) : factory(std::move(factory)) {
        sb.load();
        if (!font.loadFromFile("../assets/ARIAL.TTF")) {
            throw std::runtime_error("Failed to load font");
        }
        font.loadFromFile("../assets/ARIAL.TTF");

        title.setFont(font);
        title.setString("PACMAN PROJECT");
        title.setFillColor(sf::Color::Yellow);
        title.setCharacterSize(48);

        highscores.setFont(font);
        highscores.setFillColor(sf::Color::Green);
        highscores.setCharacterSize(24);

        // Refresh highscores display
        updateHighscoresDisplay();

        // Setup play button
        playButton.setSize(sf::Vector2f(200.f, 60.f));
        playButton.setFillColor(sf::Color(50, 50, 150));
        playButton.setOutlineColor(sf::Color::Yellow);
        playButton.setOutlineThickness(3.f);

        playButtonText.setFont(font);
        playButtonText.setString("PLAY");
        playButtonText.setFillColor(sf::Color::White);
        playButtonText.setCharacterSize(32);
    }

private:
    void updateHighscoresDisplay() {
        auto top = sb.getTop5();
        std::string hs = "Top 5 Highscores:\n";
        for (int i = 0; i < top.size(); ++i) {
            hs += std::to_string(i + 1) + ". " + std::to_string(top[i]) + "\n";
        }
        highscores.setString(hs);
    }

    /**
     * @brief Verwerkt invoer events in het hoofdmenu
     * @param stateManager Gedeelde pointer naar de StateManager voor state overgangen
     * @param window Gedeelde pointer naar het render venster
     * @param event SFML event die verwerkt moet worden
     *
     * Behandelt speler input zoals toetsaanslagen om het spel te starten
     * of het menu te verlaten.
     */
    void handleEvent(std::shared_ptr<StateManager> stateManager, std::shared_ptr<sf::RenderWindow> window,
                     const sf::Event& event) override;

    /**
     * @brief Update de menu state logica per frame
     * @param stateManager Gedeelde pointer naar de StateManager
     * @param deltaTime Delta tijd sinds vorige frame in seconden
     *
     * Lege implementatie - hoofdmenu heeft geen actieve update logica.
     */
    void update(std::shared_ptr<StateManager> stateManager, float deltaTime) override {}

    /**
     * @brief Rendert het hoofdmenu naar het venster
     * @param window Gedeelde pointer naar het render venster
     * @param windowWidth Breedte van het venster in pixels
     * @param windowHeight Hoogte van het venster in pixels
     *
     * Tekent de titel en top 5 highscores op het scherm in het menu.
     */
    void render(std::shared_ptr<sf::RenderWindow> window, unsigned int windowWidth, unsigned int windowHeight) override;
};

#endif
