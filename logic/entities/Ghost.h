/**
 * @file Ghost.h
 * @brief Definieert de Ghost entiteit en verschillende AI-varianten voor het Pac-Man spel
 * @author Siebe Haché
 * @date 07/11/2025
 */

#ifndef GHOST_H
#define GHOST_H

#include "../Random.h"
#include "../World.h"
#include "Entity.h"
#include "Pacman.h"

class World;

/**
 * @class Ghost
 * @brief Basisklasse voor alle spoken in het spel
 *
 * Beheert beweging, AI-gedrag, fear mode mechanisme en timing voor spoken.
 * Bevat gemeenschappelijke functionaliteit voor alle spook-types.
 */
class Ghost : public Entity {
protected:
    float moveTimer = 0.0f;         ///< Timer voor bewegingsinterval
    float lastMoveTime = 0.0f;      ///< Tijdstip van laatste beweging

    bool chasing = false;           ///< Indicator of spook aan het achtervolgen is
    float chaseDelay = 0.0f;        ///< Vertraging voordat achtervolging begint
    float ogChaseDelay = 0.0f;      ///< Originele chase delay voor reset

    float timeAlive = 0.0f;         ///< Tijd dat spook actief is

    float fearTime = 0.0f;          ///< Tijdsduur in fear mode
    float fearStartTime = 0.0f;     ///< Tijdstip waarop fear mode startte
    bool inFearMode = false;        ///< Indicator of spook in fear mode is

public:
    /**
     * @brief Construeert een Ghost op opgegeven positie met optionele vertraging
     * @param x X-coördinaat van het spook
     * @param y Y-coördinaat van het spook
     * @param delay Chase delay in seconden (standaard 0.0)
     *
     * Initialiseert het spook met snelheid 2.5, normale snelheid opslag 1 en fear mode snelheid 1.5.
     */
    Ghost(float x, float y, float delay = 0.0f) : Entity(x, y), chaseDelay(delay), ogChaseDelay(delay) {
        speed = 2.5;
        speedSave = 1;
        fearSpeed = 1.5;
    }

    /**
     * @brief Past positie zachtjes aan naar het centrum van de huidige tile
     * @param world Referentie naar de spelwereld
     *
     * Zorgt voor soepele uitlijning met het tile grid.
     */
    void softSnapToTileCenter(World& world);

    /**
     * @brief Update spook logica per frame
     * @param deltaTime Tijd sinds vorige frame in seconden
     * @param world Referentie naar de spelwereld
     * @param pacman Const referentie naar Pac-Man
     *
     * Wordt aangeroepen elke frame om het spook's gedrag bij te werken.
     */
    void update(float deltaTime, World& world, const Pacman& pacman) override;

    /**
     * @brief Zet de fear mode staat van het spook
     * @param state true om fear mode te activeren, false om te deactiveren
     */
    void setFearState(bool state);

    /**
     * @brief Reset de fear mode staat naar normaal
     */
    void resetFearState();

    /**
     * @brief Controleert of het spook in fear mode is
     * @return true als in fear mode, false anders
     */
    bool getFearState() const;

    /**
     * @brief Voegt tijd toe aan de bewegingstimer
     * @param dt Delta tijd om toe te voegen
     */
    void addMoveTime(float dt);

    /**
     * @brief Geeft de huidige bewegingsrichting
     * @return Huidige richtingskarakter
     */
    virtual char getDirection() const;

    /**
     * @brief Controleert of het spook gegeten is
     * @return true als spook gegeten is, false anders
     */
    bool getHasBeenEaten() const;

    /**
     * @brief Zet de gegeten staat van het spook
     * @param eaten true als spook gegeten is, false anders
     */
    void setHasBeenEaten(bool eaten);

    /**
     * @brief Controleert of het spook klaar is om te bewegen op een specifiek tijdstip
     * @param currentTime Huidig tijdstip in seconden
     * @return true als beweging mogelijk is, false anders
     */
    bool readyToMove(float currentTime) const;

    /**
     * @brief Zet de bewegingsrichting van het spook
     * @param direct Nieuwe richting
     */
    void setDirection(char direct);

    /**
     * @brief Controleert of het spook klaar is om te bewegen
     * @return true als beweging mogelijk is, false anders
     */
    bool readyToMove() const;

    /**
     * @brief Geeft de chase delay van het spook
     * @return Chase delay in seconden
     */
    float getChaseDelay() const;

    /**
     * @brief Kiest een richting tijdens fear mode
     * @param world Referentie naar de spelwereld
     * @param pacman Const referentie naar Pac-Man
     *
     * Bepaalt een vluchtrichting weg van Pac-Man tijdens fear mode.
     */
    void chooseDirectionFear(World& world, const Pacman& pacman);

    /**
     * @brief Keert de huidige bewegingsrichting om
     */
    void reverseDirection();

    /**
     * @brief Geeft de bewegingscooldown tijd
     * @return Cooldown tijd in seconden
     */
    float getMoveCooldown() const;

    /**
     * @brief Reset het spook naar beginstate
     */
    void reset();
};

/**
 * @class RedGhost
 * @brief Rood spook met vastgezette richting AI
 *
 * Beweegt in een vaste richting en heroverweegt alleen op kruispunten.
 * Agressieve achtervolgingsstrategie.
 */
class RedGhost : public Ghost {
private:
    char lockedDirection;   ///< Vastgezette bewegingsrichting

public:
    /**
     * @brief Construeert een RedGhost op opgegeven positie
     * @param x X-coördinaat van het spook
     * @param y Y-coördinaat van het spook
     */
    RedGhost(float x, float y);

    /**
     * @brief Update RedGhost logica per frame
     * @param deltaTime Tijd sinds vorige frame in seconden
     * @param world Referentie naar de spelwereld
     * @param pacman Const referentie naar Pac-Man
     */
    void update(float deltaTime, World& world, const Pacman& pacman) override;

    /**
     * @brief Kiest een nieuwe richting gebaseerd op Pac-Man's positie
     * @param pacman Const referentie naar Pac-Man
     */
    void chooseDirection(const Pacman& pacman);

    /**
     * @brief Accepteert een Visitor voor het Visitor pattern
     * @param visitor Referentie naar de Visitor die het spook bezoekt
     */
    void accept(Visitor& visitor) override;
};

/**
 * @class BlueGhost
 * @brief Blauw spook dat een positie voor Pac-Man uit achtervolgt
 *
 * Voorspelt waar Pac-Man heen gaat en achtervolgt die positie.
 * Heeft een chase delay voor gelaagde uitdaging.
 */
class BlueGhost : public Ghost {
public:
    /**
     * @brief Construeert een BlueGhost op opgegeven positie met delay
     * @param x X-coördinaat van het spook
     * @param y Y-coördinaat van het spook
     * @param delay Chase delay in seconden
     */
    BlueGhost(float x, float y, float delay);

    /**
     * @brief Update BlueGhost logica per frame
     * @param deltaTime Tijd sinds vorige frame in seconden
     * @param world Referentie naar de spelwereld
     * @param pacman Const referentie naar Pac-Man
     */
    void update(float deltaTime, World& world, const Pacman& pacman) override;

    /**
     * @brief Kiest een nieuwe richting gebaseerd op voorspelde Pac-Man positie
     * @param world Referentie naar de spelwereld
     * @param pacman Const referentie naar Pac-Man
     */
    void chooseDirection(World& world, const Pacman& pacman);

    /**
     * @brief Accepteert een Visitor voor het Visitor pattern
     * @param visitor Referentie naar de Visitor die het spook bezoekt
     */
    void accept(Visitor& visitor) override;
};

/**
 * @class PinkGhost
 * @brief Roze spook dat Pac-Man direct achtervolgt
 *
 * Volgt Pac-Man rechtstreeks met kortste pad algoritme.
 * Heeft een chase delay voor gelaagde uitdaging.
 */
class PinkGhost : public Ghost {
public:
    /**
     * @brief Construeert een PinkGhost op opgegeven positie met delay
     * @param x X-coördinaat van het spook
     * @param y Y-coördinaat van het spook
     * @param delay Chase delay in seconden
     */
    PinkGhost(float x, float y, float delay);

    /**
     * @brief Update PinkGhost logica per frame
     * @param deltaTime Tijd sinds vorige frame in seconden
     * @param world Referentie naar de spelwereld
     * @param pacman Const referentie naar Pac-Man
     */
    void update(float deltaTime, World& world, const Pacman& pacman) override;

    /**
     * @brief Kiest een nieuwe richting direct naar Pac-Man
     * @param world Referentie naar de spelwereld
     * @param pacman Const referentie naar Pac-Man
     */
    void chooseDirection(World& world, const Pacman& pacman);

    /**
     * @brief Accepteert een Visitor voor het Visitor pattern
     * @param visitor Referentie naar de Visitor die het spook bezoekt
     */
    void accept(Visitor& visitor) override;
};

#endif // GHOST_H
