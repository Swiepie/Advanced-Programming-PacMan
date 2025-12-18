/**
 * @file EntityFactory.h
 * @brief Definieert de abstracte EntityFactory interface voor het Abstract Factory pattern
 * @author siebe
 * @date 04/12/2025
 */

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "Coin.h"
#include "Entity.h"
#include "Ghost.h"
#include "Pacman.h"
#include "Wall.h"


class Wall;
class Coin;
class Fruit;
class RedGhost;
class BlueGhost;
class PinkGhost;
class PacMan;

/**
 * @class EntityFactory
 * @brief Abstracte factory interface voor het creëren van game entiteiten
 *
 * Definieert de interface voor het Abstract Factory design pattern.
 * Concrete implementaties kunnen verschillende varianten van entiteiten creëren
 * zonder de client code te wijzigen.
 */
class EntityFactory {
public:
    /**
     * @brief Virtual destructor voor correcte cleanup van afgeleide klassen
     */
    virtual ~EntityFactory() = default;

    /**
     * @brief Creëert een muur entiteit
     * @param x X-coördinaat van de muur
     * @param y Y-coördinaat van de muur
     * @return Unieke pointer naar de gecreëerde muur
     */
    virtual std::unique_ptr<Wall> createWall(float x, float y) = 0;

    /**
     * @brief Creëert een munt entiteit
     * @param x X-coördinaat van de munt
     * @param y Y-coördinaat van de munt
     * @return Unieke pointer naar de gecreëerde munt
     */
    virtual std::unique_ptr<Coin> createCoin(float x, float y) = 0;

    /**
     * @brief Creëert een fruit entiteit
     * @param x X-coördinaat van het fruit
     * @param y Y-coördinaat van het fruit
     * @return Unieke pointer naar het gecreëerde fruit
     */
    virtual std::unique_ptr<Fruit> createFruit(float x, float y) = 0;

    /**
     * @brief Creëert een Pac-Man entiteit
     * @param x X-coördinaat van Pac-Man
     * @param y Y-coördinaat van Pac-Man
     * @return Unieke pointer naar de gecreëerde Pac-Man
     */
    virtual std::unique_ptr<Pacman> createPacman(float x, float y) = 0;

    /**
     * @brief Creëert een rood spook entiteit
     * @param x X-coördinaat van het spook
     * @param y Y-coördinaat van het spook
     * @return Unieke pointer naar het gecreëerde rode spook
     */
    virtual std::unique_ptr<RedGhost> createRedGhost(float x, float y) = 0;

    /**
     * @brief Creëert een blauw spook entiteit
     * @param x X-coördinaat van het spook
     * @param y Y-coördinaat van het spook
     * @param delay Chase delay voor het spook in seconden
     * @return Unieke pointer naar het gecreëerde blauwe spook
     */
    virtual std::unique_ptr<BlueGhost> createBlueGhost(float x, float y, float delay) = 0;

    /**
     * @brief Creëert een roze spook entiteit
     * @param x X-coördinaat van het spook
     * @param y Y-coördinaat van het spook
     * @param delay Chase delay voor het spook in seconden
     * @return Unieke pointer naar het gecreëerde roze spook
     */
    virtual std::unique_ptr<PinkGhost> createPinkGhost(float x, float y, float delay) = 0;
};

#endif // ENTITYFACTORY_H
