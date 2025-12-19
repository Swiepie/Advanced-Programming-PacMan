/**
 * @file State.h
 * @brief Definieert de abstracte basis klasse voor alle game states
 * @author Siebe Haché
 * @date 28/10/2025
 */

#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>
#include <memory>

class StateManager;

/**
 * @class State
 * @brief Abstracte basis klasse voor het State pattern in het spel
 *
 * Definieert de interface voor alle game states zoals MenuState, LevelState
 * en PausedState. Implementeert het State pattern voor modulair state management.
 * Elke concrete state moet de pure virtual methodes implementeren.
 */
class State {
public:
    /**
     * @brief Virtuele destructor voor correcte cleanup van afgeleide klassen
     */
    virtual ~State() = default;

    /**
     * @brief Verwerkt invoer events in de huidige state
     * @param stateManager Gedeelde pointer naar de StateManager voor state overgangen
     * @param window Gedeelde pointer naar het render venster
     * @param event SFML event die verwerkt moet worden
     *
     * Pure virtual methode die door elke concrete state geïmplementeerd moet worden
     * om input events zoals toetsaanslagen en muisklikken te verwerken.
     */
    virtual void handleEvent(std::shared_ptr<StateManager> stateManager, std::shared_ptr<sf::RenderWindow> window,
                             const sf::Event& event) = 0;

    /**
     * @brief Update de state logica per frame
     * @param stateManager Gedeelde pointer naar de StateManager
     * @param deltaTime Delta tijd sinds vorige frame in seconden
     *
     * Pure virtual methode voor het updaten van game logica, animaties
     * en andere tijdsgebonden bewerkingen in de state.
     */
    virtual void update(std::shared_ptr<StateManager> stateManager, float deltaTime) = 0;

    /**
     * @brief Rendert de state naar het venster
     * @param window Gedeelde pointer naar het render venster
     * @param windowWidth Breedte van het venster in pixels
     * @param windowHeight Hoogte van het venster in pixels
     *
     * Pure virtual methode voor het tekenen van alle visuele elementen
     * van de state op het scherm.
     */
    virtual void render(std::shared_ptr<sf::RenderWindow> window, unsigned int windowWidth,
                        unsigned int windowHeight) = 0;

    /**
     * @brief Wordt aangeroepen bij het betreden van deze state
     *
     * Optionele methode voor initialisatie logica wanneer de state actief wordt.
     * Standaard implementatie is leeg.
     */
    virtual void onEnter() {};

    /**
     * @brief Wordt aangeroepen bij het verlaten van deze state
     *
     * Optionele methode voor cleanup logica wanneer de state verlaten wordt.
     * Standaard implementatie is leeg.
     */
    virtual void onExit() {};
};

#endif