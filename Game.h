//
// Created by Siebe Haché on 14/10/2025.
//

#ifndef GAME_H
#define GAME_H

#include "logic/Stopwatch.h"
#include "logic/entities/EntityFactory.h"
#include "states/StateManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
/**
 * @brief Struct voor het opslaan van de afmetingen van een level.
 */
struct FileDimensions {
    std::size_t width;
    std::size_t height;
};

/**
 * @class Game
 * @brief Hoofdklasse voor het opstarten en draaien van het spel.
 *
 * Deze klasse initialiseert het SFML venster, de StateManager en de game-loop.
 * Het beheert de tijdsberekeningen via Stopwatch en verwerkt window events.
 * De Game-klasse scheidt volledig de representatie (SFML) van de game-logica.
 */
class Game {
private:
    /**
     * @brief Bepaalt de afmetingen van een level-bestand.
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
    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<StateManager> stateManager;
    int framerate = 60;
public:
    static FileDimensions getFileDimensions(const std::string& filename);
    Game();
    ~Game();
    void run() const;
};

#endif // GAME_H
