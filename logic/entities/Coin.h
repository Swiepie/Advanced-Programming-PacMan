/**
* @file Coin.h
 * @brief Definieert de Coin entiteit voor het Pac-Man spel
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
 * @brief Klasse die een verzamelbare munt in het spel representeert
 *
 * Coin is een verzamelbaar object dat punten oplevert wanneer het door Pac-Man
 * wordt opgegeten. Implementeert het Visitor pattern voor rendering.
 */
class Coin : public Entity {
private:
    int worth = 10;  ///< Puntwaarde van de munt (standaard 10 punten)

public:
    /**
     * @brief Construeert een Coin op opgegeven positie
     * @param x X-coördinaat van de munt
     * @param y Y-coördinaat van de munt
     */
    Coin(float x, float y) : Entity(x, y) {}

    /**
     * @brief Controleert of de munt verzamelbaar is
     * @return true als de munt opgepakt kan worden, false anders
     */
    bool isCollectible() const override;

    /**
     * @brief Verwerkt het verzamelen van de munt
     * @param world Referentie naar de spelwereld
     *
     * Voegt punten toe aan de score wanneer de munt wordt verzameld.
     */
    void onCollect(World& world) override;

    /**
     * @brief Accepteert een Visitor voor het Visitor pattern
     * @param visitor Referentie naar de Visitor die de munt bezoekt
     *
     * Implementatie van het Visitor pattern voor operaties zoals rendering.
     */
    void accept(Visitor& visitor) override;
};

#endif // COIN_H
