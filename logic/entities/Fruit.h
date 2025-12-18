/**
* @file Fruit.h
 * @brief Definieert de Fruit entiteit voor het Pac-Man spel
 * @author siebe
 * @date 02/11/2025
 */

#ifndef FRUIT_H
#define FRUIT_H

#include "../Visitor.h"
#include "../World.h"
#include "Entity.h"
#include <iostream>

/**
 * @class Fruit
 * @brief Klasse die een bonusfruit in het spel representeert
 *
 * Fruit is een verzamelbaar object dat extra punten oplevert wanneer het door Pac-Man
 * wordt opgegeten. Implementeert het Visitor pattern voor rendering.
 */
class Fruit : public Entity {
private:
    int worth = 50;  ///< Puntwaarde van het fruit (standaard 50 punten)

public:
    /**
     * @brief Construeert een Fruit op opgegeven positie
     * @param x X-coördinaat van het fruit
     * @param y Y-coördinaat van het fruit
     */
    Fruit(float x, float y) : Entity(x, y) {}

    /**
     * @brief Controleert of het fruit verzamelbaar is
     * @return true als het fruit opgepakt kan worden, false anders
     */
    bool isCollectible() const override;

    /**
     * @brief Verwerkt het verzamelen van het fruit
     * @param world Referentie naar de spelwereld
     *
     * Voegt bonuspunten toe aan de score wanneer het fruit wordt verzameld.
     */
    void onCollect(World& world) override;

    /**
     * @brief Accepteert een Visitor voor het Visitor pattern
     * @param visitor Referentie naar de Visitor die het fruit bezoekt
     *
     * Implementatie van het Visitor pattern voor operaties zoals rendering.
     */
    void accept(Visitor& visitor) override;
};

#endif // FRUIT_H
