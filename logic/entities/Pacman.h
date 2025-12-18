/**
 * @file Pacman.h
 * @brief Definieert de Pacman entiteit, de hoofdspeler van het spel
 * @author siebe
 * @date 22/09/2025
 */

#ifndef PACMAN_H
#define PACMAN_H

#include <iostream>

#include "../Stopwatch.h"
#include "../Visitor.h"
#include "Entity.h"

/**
 * @class Pacman
 * @brief Klasse die de speler-gecontroleerde Pac-Man entiteit representeert
 *
 * Beheert beweging, richting, buffering van input en timing voor Pac-Man.
 * Ondersteunt directe en gebufferde richtingsveranderingen voor responsieve besturing.
 */
class Pacman : public Entity {
private:
    char direction;             ///< Huidige bewegingsrichting van Pac-Man
    char bufferdirection;       ///< Gebufferde richting voor volgende beweging
    float moveTimer = 0.0f;     ///< Timer voor bewegingsinterval
    float lastMoveTime = 0.0f;  ///< Tijdstip van laatste beweging

public:
    /**
     * @brief Construeert een Pacman op opgegeven positie
     * @param x X-coördinaat van Pac-Man
     * @param y Y-coördinaat van Pac-Man
     *
     * Initialiseert Pac-Man met snelheid 4 en zonder beginrichting.
     */
    Pacman(float x, float y) : Entity(x, y), direction(' '), bufferdirection(0) { speed = 4; }

    /**
     * @brief Update Pac-Man logica per frame
     * @param deltaTime Tijd sinds vorige frame in seconden
     *
     * Wordt aangeroepen elke frame om Pac-Man's staat bij te werken.
     */
    void update(float deltaTime) override;

    /**
     * @brief Voegt tijd toe aan de bewegingstimer
     * @param dt Delta tijd om toe te voegen
     */
    void addMoveTime(float dt);

    /**
     * @brief Controleert of Pac-Man klaar is om te bewegen
     * @return true als beweging mogelijk is, false anders
     */
    bool readyToMove() const;

    /**
     * @brief Reset de bewegingstimer naar 0
     */
    void resetMoveTimer();

    /**
     * @brief Controleert of Pac-Man klaar is om te bewegen op een specifiek tijdstip
     * @param currentTime Huidig tijdstip in seconden
     * @return true als beweging mogelijk is, false anders
     */
    bool readyToMove(float currentTime) const;

    /**
     * @brief Registreert het tijdstip van de laatste beweging
     * @param currentTime Tijdstip van de beweging
     */
    void recordMoveTime(float currentTime);

    /**
     * @brief Geeft de gebufferde richting
     * @return Gebufferde richtingskarakter
     */
    char getBufferdirection() const;

    /**
     * @brief Zet de gebufferde richting
     * @param direct Nieuwe gebufferde richting
     */
    void setBufferdirection(char direct);

    /**
     * @brief Past de gebufferde richting toe als huidige richting
     *
     * Gebruikt voor het toepassen van spelerinput zodra de beweging mogelijk is.
     */
    void applyBufferdirection();

    /**
     * @brief Geeft de huidige bewegingsrichting
     * @return Huidige richtingskarakter
     */
    char getDirection() const;

    /**
     * @brief Zet de huidige bewegingsrichting
     * @param direct Nieuwe richting
     */
    void setDirection(char direct);

    /**
     * @brief Geeft de bewegingscooldown tijd
     * @return Cooldown tijd in seconden
     */
    float getmoveCooldown() const;

    /**
     * @brief Accepteert een Visitor voor het Visitor pattern
     * @param visitor Referentie naar de Visitor die Pac-Man bezoekt
     *
     * Implementatie van het Visitor pattern voor operaties zoals rendering.
     */
    void accept(Visitor& visitor) override;
};

#endif // PACMAN_H
