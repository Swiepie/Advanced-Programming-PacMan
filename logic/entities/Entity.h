/**
 * @file Entity.h
 * @brief Definieert de abstracte Entity basisklasse voor alle game objecten
 * @author siebe
 * @date 22/09/2025
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "Subject.h"
#include <memory>
#include <string>

/**
 * @struct coord
 * @brief Eenvoudige coördinaat structuur voor 2D posities
 */
struct coord {
    float x, y; ///< X en Y coördinaten
};

class Visitor;
class Pacman;
class World;

/**
 * @class Entity
 * @brief Abstracte basisklasse voor alle entiteiten in het spel
 *
 * Biedt gemeenschappelijke functionaliteit zoals positie, beweging, botsingsdetectie
 * en spawn management. Erft van Subject voor het Observer pattern en implementeert
 * het Visitor pattern voor rendering en operaties.
 */
class Entity : public Subject {
protected:
    double speed = 2.5;        ///< Huidige bewegingssnelheid van de entiteit
    double speedSave = 1;      ///< Opgeslagen snelheid voor herstel na modificatie
    double fearSpeed = 1.5;    ///< Snelheid tijdens fear mode (voor spoken)
    float moveCooldown;        ///< Cooldown tussen bewegingen
    coord position;            ///< Huidige positie van de entiteit
    char direction;            ///< Huidige bewegingsrichting
    bool hasBeenEaten = false; ///< Indicator of entiteit opgegeten is
    coord spawn;               ///< Spawn positie voor respawn
    bool fpinkn = false;       ///< Indicator of entiteit bevroren is
    float respawnTimer;        ///< Timer voor respawn mechanisme

public:
    /**
     * @brief Virtual destructor voor correcte cleanup van afgeleide klassen
     */
    ~Entity() override;

    /**
     * @brief Construeert een Entity op opgegeven positie
     * @param x X-coördinaat van de entiteit
     * @param y Y-coördinaat van de entiteit
     *
     * Initialiseert entiteit met bewegingscooldown 0, geen richting en respawn timer 0.
     */
    Entity(float x, float y) : moveCooldown(0), position{x, y}, direction(0), spawn(), respawnTimer(0) {}

    /**
     * @brief Accepteert een Visitor voor het Visitor pattern
     * @param visitor Referentie naar de Visitor die de entiteit bezoekt
     *
     * Pure virtuele functie die door afgeleide klassen geïmplementeerd moet worden
     * voor operaties zoals rendering.
     */
    virtual void accept(Visitor& visitor) = 0;

    /**
     * @brief Geeft de huidige positie van de entiteit
     * @return Coördinaat structuur met positie
     */
    coord getPosition() const;

    /**
     * @brief Zet de positie van de entiteit
     * @param x Nieuwe X-coördinaat
     * @param y Nieuwe Y-coördinaat
     */
    void setPosition(float x, float y);

    /**
     * @brief Update entiteit logica per frame
     * @param deltaTime Tijd sinds vorige frame in seconden
     *
     * Basis update functie voor generieke entiteiten.
     */
    virtual void update(float deltaTime);

    /**
     * @brief Controleert of deze entiteit botst met een andere
     * @param other Referentie naar de andere entiteit
     * @param stepW Breedte stap voor botsingsdetectie (standaard 0.05)
     * @param stepH Hoogte stap voor botsingsdetectie (standaard 0.05)
     * @return true als entiteiten botsen, false anders
     *
     * Gebruikt rechthoekige botsingsdetectie met aanpasbare stappen.
     */
    bool collidesWith(const Entity& other, float stepW = 0.05f, float stepH = 0.05f) const;

    /**
     * @brief Controleert of de entiteit collectable is
     * @return true als entiteit opgepakt kan worden, false anders
     *
     * Standaard implementatie retourneert false. Override in afgeleide klassen
     * voor verzamelbare objecten zoals coinen en fruit.
     */
    virtual bool isCollectible() const;

    /**
     * @brief Verwerkt het verzamelen van de entiteit
     * @param world Referentie naar de world
     *
     * Standaard implementatie doet niets. Override in afgeleide klassen
     * voor verzamelbare objecten om effecten toe te passen.
     */
    virtual void onCollect(World& world);

    /**
     * @brief Update entiteit logica met wereld en pacman context
     * @param deltaTime Tijd sinds vorige frame in seconden
     * @param world Referentie naar de world
     * @param pacman Const referentie naar pacman
     *
     * Uitgebreide update functie voor entiteiten die interactie met de
     * wereld en pacman nodig hebben (zoals spoken).
     */
    virtual void update(float deltaTime, World& world, const Pacman& pacman) {}

    /**
     * @brief Zet de spawn positie van de entiteit
     * @param x X-coördinaat van spawn punt
     * @param y Y-coördinaat van spawn punt
     */
    void setSpawn(float x, float y);

    /**
     * @brief Reset entiteit naar spawn positie
     *
     * Gebruikt voor respawn mechanisme na death of level reset.
     */
    void resetToSpawn();

    /**
     * @brief Geeft de huidige snelheid van de entiteit
     * @return Snelheid als float
     */
    float getSpeed() const;

    /**
     * @brief Zet de snelheid van de entiteit
     * @param spd Nieuwe snelheid
     */
    void setSpeed(double spd);
};

#endif // ENTITY_H
