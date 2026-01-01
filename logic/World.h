/**
 * @file World.h
 * @brief Beheert de world en alle game logica voor pacman
 * @author Siebe Haché
 * @date 14/10/2025
 */

#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <string>
#include <vector>

#include <fstream>
#include <iostream>

#include "Score.h"
#include "Visitor.h"
#include "entities/Coin.h"
#include "entities/Entity.h"
#include "entities/EntityFactory.h"
#include "entities/Fruit.h"
#include "entities/Ghost.h"
#include "entities/Pacman.h"
#include "entities/Wall.h"

class Ghost;
class EntityFactory;

/**
 * @class World
 * @brief Hoofdklasse die de world en alle game objecten beheert
 *
 * Beheert het laden van maps, updates van alle entiteiten, collision detection,
 * score systeem, levens van pacman, fear mode mechanisme en algemene game state.
 */
class World {
private:
    int width = 0;                          ///< Breedte van de world in tiles
    int height = 0;                         ///< Hoogte van de world in tiles
    std::vector<std::string> mapData;       ///< Ruwe map data gelezen uit bestand
    std::vector<coord> ghostSpawnPositions; ///< Spawn posities voor spoken

    // Gescheiden vectors voor verschillende entiteit types
    std::vector<std::unique_ptr<Wall>> walls;          ///< Alle muren in de wereld
    std::vector<std::unique_ptr<Entity>> collectibles; ///< Alle verzamelbare items (coinen + fruit)
    std::vector<std::unique_ptr<Ghost>> ghosts;        ///< Alle spoken in het spel

    std::shared_ptr<Pacman> pacman; ///< De pacman speler entiteit

    int coinCount = 0;   ///< Aantal resterende coinen
    int pacmanlives = 3; ///< Aantal levens van pacman

    // Tijd variabelen
    float totTime = 0.0f; ///< Totale verstreken speltijd
    float deltaT = 0.0f;  ///< Tijd sinds laatste frame

    // Dood/Respawn states
    bool dies = false;         ///< Indicator dat pacman sterft
    float diesTime = 0.0f;     ///< Tijdstip van dood
    float respawnTimer = 1.32f; ///< Tijd tot respawn na dood
    bool death = false;        ///< Indicator voor dood state
    float deathTime = 0.0f;    ///< temporary die de tijd bijhoudt van de dood
    bool reset = false;        ///< Indicator voor wereld reset

    // Score
    int rounds = 0; ///< Aantal voltooide rondes
    Score score;    ///< Score object voor puntenbeheer

    float stepW = 2.0f / static_cast<float>(width);  ///< Stap grootte voor breedte normalisatie
    float stepH = 2.0f / static_cast<float>(height); ///< Stap grootte voor hoogte normalisatie

    // Fear mode
    bool fearmode = false;      ///< Indicator of fear mode actief is
    float fearmodeTimer = 6.0f; ///< Duur van fear mode in seconden
    float fearmodeStart = 0.0f; ///< Tijdstip waarop fear mode startte

    // FACTORY POINTER
    std::shared_ptr<EntityFactory> factory; ///< Factory voor het creëren van entiteiten

public:
    /**
     * @brief Destructor voor de World klasse
     */
    ~World() = default;

    /**
     * @brief Construeert een World met opgegeven entity factory
     * @param entityFactory Shared pointer naar de entity factory
     */
    explicit World(std::shared_ptr<EntityFactory> entityFactory) : factory(std::move(entityFactory)) {}

    /**
     * @brief Laadt een map uit een bestand
     * @param filename Pad naar het map bestand
     * @return true als laden succesvol was, false anders
     */
    bool loadMap(const std::string& filename);

    /**
     * @brief Print de map naar console voor debug doeleinden
     */
    void printMap() const;

    /**
     * @brief Update alle wereld logica en entiteiten
     * @param deltaTime Tijd sinds vorige frame in seconden
     */
    void update(float deltaTime);

    /**
     * @brief Activeert of deactiveert fear mode
     * @param fearmode true om fear mode te activeren, false om te deactiveren
     */
    void setFearMode(bool fearmode);

    /**
     * @brief Controleert of fear mode actief is
     * @return true als fear mode actief is, false anders
     */
    bool getFearMode() const;

    /**
     * @brief Geeft de resterende fear mode tijd
     * @return Resterende tijd in seconden
     */
    float getFearModeTimer() const;

    /**
     * @brief Geeft alle entiteiten in de wereld
     * @return Const referentie naar vector met entiteiten (legacy methode)
     */
    const std::vector<std::unique_ptr<Entity>>& getEntities() const;

    /**
     * @brief Geeft de breedte van de wereld
     * @return Breedte in tiles
     */
    int getWidth() const;

    /**
     * @brief Geeft de hoogte van de wereld
     * @return Hoogte in tiles
     */
    int getHeight() const;

    /**
     * @brief Controleert of pacman in een richting kan bewegen
     * @param pacman Shared pointer naar pacman
     * @param dir Bewegingsrichting karakter
     * @return true als beweging mogelijk is, false anders
     */
    bool tryMove(const std::shared_ptr<Pacman>& pacman, char dir) const;

    /**
     * @brief Geeft alle muren in de wereld
     * @return Const referentie naar vector met muren
     */
    const std::vector<std::unique_ptr<Wall>>& getWalls() const;

    /**
     * @brief Geeft alle verzamelbare items
     * @return Const referentie naar vector met collectibles
     */
    const std::vector<std::unique_ptr<Entity>>& getCollectibles() const;

    /**
     * @brief Geeft alle spoken in de wereld
     * @return Const referentie naar vector met spoken
     */
    const std::vector<std::unique_ptr<Ghost>>& getGhosts() const;

    /**
     * @brief Geeft de pacman speler
     * @return Shared pointer naar pacman
     */
    std::shared_ptr<Pacman> getPacman() const;

    /**
     * @brief Controleert alle collisions tussen entiteiten
     */
    void checkCollisions();

    /**
     * @brief Zet de starttijd van fear mode
     * @param timer Starttijd van fear mode
     */
    void setFearModeStart(float timer);

    /**
     * @brief Controleert of een ghost in een richting kan bewegen
     * @param ghost Pointer naar het ghost
     * @param dir Bewegingsrichting karakter
     * @return true als beweging mogelijk is, false anders
     */
    bool tryMoveGhost(Ghost& ghost, char dir) const;

    /**
     * @brief Controleert of beweging in een richting mogelijk is voor een ghost
     * @param ghost Pointer naar de ghost
     * @param dir Bewegingsrichting karakter
     * @return true als beweging mogelijk is, false anders
     */
    bool canMoveInDirection(const Ghost& ghost, char dir) const;

    /**
     * @brief Controleert of een ghost op een kruispunt staat
     * @param ghost Pointer naar de ghost
     * @return true als ghost op kruispunt staat, false anders
     */
    bool isAtIntersection(const Ghost& ghost) const;

    /**
     * @brief Controleert of een ghost het centrum van een tile zal kruisen
     * @param ghost Pointer naar de ghost
     * @param dir Bewegingsrichting karakter
     * @return true als tile centrum gekruist wordt, false anders
     */
    bool willCrossTileCenter(const Ghost& ghost, char dir) const;

    /**
     * @brief Geeft het aantal resterende levens van pacman
     * @return Aantal levens
     */
    int getPacmanLives() const;

    /**
     * @brief Geeft de huidige score
     * @return Score als integer
     */
    int getScore() const;

    /**
     * @brief Controleert of een entiteit op het centrum van een tile staat
     * @param e Pointer naar de entiteit
     * @return true als entiteit op tile centrum staat, false anders
     */
    bool isOnTileCenter(const Entity& e) const;

    /**
     * @brief Geeft de huidige speltijd
     * @return Totale verstreken tijd in seconden
     */
    float getTime() const;

    /**
     * @brief Vermindert het aantal resterende coinen
     */
    void decreaseCoins();

    /**
     * @brief Reset de wereld na de dood van pacman
     */
    void resetAfterDeath();

    /**
     * @brief Geeft het aantal resterende coinen
     * @return Aantal coinen
     */
    int getCoinCount() const;

    /**
     * @brief Reset de gehele wereld naar beginstate
     */
    void resetWorld();

    /**
     * @brief Geeft referentie naar het Score object
     * @return Referentie naar Score
     */
    Score& getScore();

    /**
     * @brief Geeft death state indicator
     * @return Death state als integer
     */
    int getDeath();

    /**
     * @brief Geeft het aantal voltooide rondes
     * @return Aantal rondes
     */
    int getRounds() const;
};

#endif // WORLD_H
