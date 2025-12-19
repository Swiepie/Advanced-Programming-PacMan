/**
 * @file ConcreteFactory.h
 * @brief Definieert de ConcreteFactory voor het creëren van game entiteiten
 * @author siebe
 * @date 14/12/2025
 */

#ifndef CONCRETEFACTORY_H
#define CONCRETEFACTORY_H

#include "logic/entities/EntityFactory.h"

#include "logic/Observer.h"
#include "renderer/CollectibleView.h"
#include "renderer/GhostView.h"
#include "renderer/PacmanView.h"
#include "renderer/WallView.h"

/**
 * @class ConcreteFactory
 * @brief Concrete implementatie van EntityFactory voor het creëren van game entiteiten
 *
 * Implementeert het Factory pattern voor het aanmaken van alle game entiteiten.
 * Creëert zowel de logica (model) als de visuele representatie (view) van elke
 * entiteit en koppelt deze via het Observer pattern. Beheert de levensduur van
 * alle views in een centrale container.
 */
class ConcreteFactory : public EntityFactory {
private:
    std::vector<std::unique_ptr<EntityView>> views; ///< Container voor alle entity views
    std::shared_ptr<sf::RenderWindow> window;       ///< SFML render venster voor view creatie

public:
    /**
     * @brief Destructor voor ConcreteFactory
     *
     * Ruimt alle views en resources op die door de factory aangemaakt zijn.
     */
    ~ConcreteFactory() override;

    /**
     * @brief Construeert een ConcreteFactory met opgegeven render venster
     * @param window Gedeelde pointer naar het SFML render venster
     *
     * Initialiseert de factory met een referentie naar het render venster
     * voor het creëren van entity views.
     */
    ConcreteFactory(std::shared_ptr<sf::RenderWindow> window);

    /**
     * @brief Creëert een wall entiteit op de opgegeven positie
     * @param x X-coördinaat van de wall
     * @param y Y-coördinaat van de wall
     * @return Unieke pointer naar de aangemaakte Wall entiteit
     *
     * Maakt zowel de Wall model als bijbehorende WallView aan
     * en registreert de view als observer van het model.
     */
    std::unique_ptr<Wall> createWall(float x, float y) override;

    /**
     * @brief Creëert een coin entiteit op de opgegeven positie
     * @param x X-coördinaat van de coin
     * @param y Y-coördinaat van de coin
     * @return Unieke pointer naar de aangemaakte Coin entiteit
     *
     * Maakt zowel de Coin model als bijbehorende CollectibleView aan
     * en registreert de view als observer van het model.
     */
    std::unique_ptr<Coin> createCoin(float x, float y) override;

    /**
     * @brief Creëert een fruit entiteit op de opgegeven positie
     * @param x X-coördinaat van het fruit
     * @param y Y-coördinaat van het fruit
     * @return Unieke pointer naar de aangemaakte Fruit entiteit
     *
     * Maakt zowel de Fruit model als bijbehorende CollectibleView aan
     * en registreert de view als observer van het model.
     */
    std::unique_ptr<Fruit> createFruit(float x, float y) override;

    /**
     * @brief Creëert een Pacman entiteit op de opgegeven positie
     * @param x X-coördinaat van Pacman
     * @param y Y-coördinaat van Pacman
     * @return Unieke pointer naar de aangemaakte Pacman entiteit
     *
     * Maakt zowel de Pacman model als bijbehorende PacmanView aan
     * en registreert de view als observer van het model.
     */
    std::unique_ptr<Pacman> createPacman(float x, float y) override;

    /**
     * @brief Creëert een red ghost entiteit op de opgegeven positie
     * @param x X-coördinaat van de red ghost
     * @param y Y-coördinaat van de red ghost
     * @return Unieke pointer naar de aangemaakte RedGhost entiteit
     *
     * Maakt zowel de RedGhost model als bijbehorende GhostView aan
     * en registreert de view als observer van het model.
     */
    std::unique_ptr<RedGhost> createRedGhost(float x, float y) override;

    /**
     * @brief Creëert een bluee ghost entiteit op de opgegeven positie
     * @param x X-coördinaat van de bluee ghost
     * @param y Y-coördinaat van de bluee ghost
     * @param delay Vertraging voordat de ghost begint te bewegen in seconden
     * @return Unieke pointer naar de aangemaakte BlueGhost entiteit
     *
     * Maakt zowel de BlueGhost model als bijbehorende GhostView aan
     * en registreert de view als observer van het model.
     */
    std::unique_ptr<BlueGhost> createBlueGhost(float x, float y, float delay) override;

    /**
     * @brief Creëert een pink ghost entiteit op de opgegeven positie
     * @param x X-coördinaat van de pink ghost
     * @param y Y-coördinaat van de pink ghost
     * @param delay Vertraging voordat de ghost begint te bewegen in seconden
     * @return Unieke pointer naar de aangemaakte PinkGhost entiteit
     *
     * Maakt zowel de PinkGhost model als bijbehorende GhostView aan
     * en registreert de view als observer van het model.
     */
    std::unique_ptr<PinkGhost> createPinkGhost(float x, float y, float delay) override;
};

#endif // CONCRETEFACTORY_H
