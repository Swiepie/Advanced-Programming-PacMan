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
     * @brief Creëert een wall entiteit
     * @param x X-coördinaat van de wall
     * @param y Y-coördinaat van de wall
     * @return Unieke pointer naar de gecreëerde wall
     */
    virtual std::unique_ptr<Wall> createWall(float x, float y) = 0;

    /**
     * @brief Creëert een coin entiteit
     * @param x X-coördinaat van de coin
     * @param y Y-coördinaat van de coin
     * @return Unieke pointer naar de gecreëerde coin
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
     * @brief Creëert een pacman entiteit
     * @param x X-coördinaat van pacman
     * @param y Y-coördinaat van pacman
     * @return Unieke pointer naar de gecreëerde pacman
     */
    virtual std::unique_ptr<Pacman> createPacman(float x, float y) = 0;

    /**
     * @brief Creëert een red ghost entiteit
     * @param x X-coördinaat van het ghost
     * @param y Y-coördinaat van het ghost
     * @return Unieke pointer naar het gecreëerde red ghost
     */
    virtual std::unique_ptr<RedGhost> createRedGhost(float x, float y) = 0;

    /**
     * @brief Creëert een blue ghost entiteit
     * @param x X-coördinaat van het ghost
     * @param y Y-coördinaat van het ghost
     * @param delay Chase delay voor het ghost in seconden
     * @return Unieke pointer naar het gecreëerde bluee ghost
     */
    virtual std::unique_ptr<BlueGhost> createBlueGhost(float x, float y, float delay) = 0;

    /**
     * @brief Creëert een pink ghost entiteit
     * @param x X-coördinaat van het ghost
     * @param y Y-coördinaat van het ghost
     * @param delay Chase delay voor het ghost in seconden
     * @return Unieke pointer naar het gecreëerde pink ghost
     */
    virtual std::unique_ptr<PinkGhost> createPinkGhost(float x, float y, float delay) = 0;
};

#endif // ENTITYFACTORY_H
