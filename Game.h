/**
 * @file Game.h
 * @brief Definieert de Game klasse voor het hoofdspel management
 * @author Siebe Haché
 * @date 14/10/2025
 */

#ifndef GAME_H
#define GAME_H

#include "logic/Stopwatch.h"
#include "logic/entities/EntityFactory.h"
#include "states/StateManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

/**
 * @struct FileDimensions
 * @brief Struct voor het opslaan van de afmetingen van een level
 *
 * Bevat de breedte en hoogte van een level bestand in aantal karakters/regels.
 */
struct FileDimensions {
    std::size_t width;  ///< Breedte van het level in karakters
    std::size_t height; ///< Hoogte van het level in regels
};

/**
 * @class Game
 * @brief Hoofdklasse voor het opstarten en draaien van het spel
 *
 * Deze klasse initialiseert het SFML venster, de StateManager en de game-loop.
 * Het beheert de tijdsberekeningen via Stopwatch en verwerkt window events.
 * De Game-klasse scheidt volledig de representatie (SFML) van de game-logica.
 */
class Game {
private:
    std::shared_ptr<sf::RenderWindow> window;   ///< SFML render venster voor visuele weergave
    std::shared_ptr<StateManager> stateManager; ///< Manager voor game state transities
    int framerate = 60;                         ///< Target framerate in frames per seconde

public:
    /**
     * @brief Bepaalt de afmetingen van een level-bestand
     * @param filename Pad naar het level-bestand (.txt)
     * @return FileDimensions Struct met breedte en hoogte van het bestand
     * @throws std::runtime_error Als het bestand niet geopend kan worden
     *
     * Deze functie leest het bestand regel voor regel en bepaalt:
     * - Height: het aantal regels
     * - Width: de lengte van de langste regel
     *
     * Wordt gebruikt bij het initialiseren van de views van de entities.
     */
    static FileDimensions getFileDimensions(const std::string& filename);

    /**
     * @brief Construeert en initialiseert het Game object
     *
     * Initialiseert het SFML venster, StateManager en zet de initiële game state.
     * Configureert het venster met de juiste afmetingen en framerate limiet.
     */
    Game();

    /**
     * @brief Destructor voor Game
     *
     * Ruimt alle game resources op en sluit het SFML venster.
     */
    ~Game();

    /**
     * @brief Start de hoofdgame loop
     *
     * Draait de game loop die events verwerkt, de huidige state update
     * en de visuele representatie rendert. Blijft draaien totdat het
     * venster gesloten wordt.
     */
    void run() const;
};

#endif // GAME_H
