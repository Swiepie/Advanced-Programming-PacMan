/**
* @file Wall.h
 * @brief Definieert de Wall entiteit voor het Pac-Man spel
 * @author Siebe Haché
 * @date 15/10/2025
 */

#ifndef WALL_H
#define WALL_H

#include "../Visitor.h"
#include "Entity.h"

/**
 * @class Wall
 * @brief Klasse die een muur in de spelwereld representeert
 *
 * Muren zijn statische obstakels die Pac-Man en spoken niet kunnen passeren.
 * Implementeert het Visitor pattern voor rendering en collision detection.
 */
class Wall : public Entity {
public:
    /**
     * @brief Construeert een Wall op opgegeven positie
     * @param x X-coördinaat van de muur
     * @param y Y-coördinaat van de muur
     */
    Wall(float x, float y) : Entity(x, y) {}

    /**
     * @brief Accepteert een Visitor voor het Visitor pattern
     * @param visitor Referentie naar de Visitor die de muur bezoekt
     *
     * Implementatie van het Visitor pattern voor operaties zoals rendering.
     */
    void accept(Visitor& visitor) override;
};

#endif // WALL_H
