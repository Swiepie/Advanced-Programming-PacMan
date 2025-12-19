/**
 * @file Coin.h
 * @brief Definieert de Coin entiteit voor het pacman spel
 * @author Siebe Haché
 * @date 15/10/2025
 */

#ifndef COIN_H
#define COIN_H

#include "../Visitor.h"
#include "Entity.h"
#include <iostream>

/**
 * @class Coin
 * @brief Klasse die een verzamelbare coin in het spel representeert
 *
 * Coin is een collectable object dat punten oplevert wanneer het door pacman
 * wordt opgegeten. Implementeert het Visitor pattern voor rendering.
 */
class Coin : public Entity {
private:
    int worth = 10; ///< Puntwaarde van de coin (standaard 10 punten)

public:
    /**
     * @brief Construeert een Coin op opgegeven positie
     * @param x X-coördinaat van de coin
     * @param y Y-coördinaat van de coin
     */
    Coin(float x, float y) : Entity(x, y) {}

    /**
     * @brief Controleert of de coin collectable is
     * @return true als de coin opgepakt kan worden, false anders
     */
    bool isCollectible() const override;

    /**
     * @brief Verwerkt het verzamelen van de coin
     * @param world Referentie naar de world
     *
     * Voegt punten toe aan de score wanneer de coin wordt verzameld.
     */
    void onCollect(World& world) override;

    /**
     * @brief Accepteert een Visitor voor het Visitor pattern
     * @param visitor Referentie naar de Visitor die de coin bezoekt
     *
     * Implementatie van het Visitor pattern voor operaties zoals rendering.
     */
    void accept(Visitor& visitor) override;
};

#endif // COIN_H
