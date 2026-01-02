/**
 * @file Ghost.h
 * @brief Definieert de Ghost entiteit en verschillende AI-varianten voor het pacman spel
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
 * Bevat gemeenschappelijke functionaliteit voor alle ghost-types.
 */
class Ghost : public Entity {
protected:
    float moveTimer = 0.0f;    ///< Timer voor bewegingsinterval
    float lastMoveTime = 0.0f; ///< Tijdstip van laatste beweging

    bool chasing = false;      ///< Indicator of ghost aan het achtervolgen is
    float chaseDelay = 0.0f;   ///< Vertraging voordat achtervolging begint
    float ogChaseDelay = 0.0f; ///< Originele chase delay voor reset

    float timeAlive = 0.0f; ///< Tijd dat ghost actief is

    float fearTime = 0.0f;      ///< Tijdsduur in fear mode
    float fearStartTime = 0.0f; ///< Tijdstip waarop fear mode startte
    bool inFearMode = false;    ///< Indicator of ghost in fear mode is

public:
    /**
     * @brief Construeert een Ghost op opgegeven positie met optionele vertraging
     * @param x X-coördinaat van het ghost
     * @param y Y-coördinaat van het ghost
     * @param delay Chase delay in seconden (standaard 0.0)
     *
     * Initialiseert het ghost met snelheid 2.5, normale snelheid opslag 1 en fear mode snelheid 1.5.
     */
    Ghost(float x, float y, float delay = 0.0f) : Entity(x, y), chaseDelay(delay), ogChaseDelay(delay) {
        speed = 2.5;
        speedSave = 1;
        fearSpeed = 1.5;
    }

    /**
     * @brief Past positie zachtjes aan naar het centrum van de huidige tile
     * @param world Referentie naar de world
     *
     * Zorgt voor soepele uitlijning met het tile grid.
     */
    void softSnapToTileCenter(World& world);

    /**
     * @brief Update ghost logica per frame
     * @param deltaTime Tijd sinds vorige frame in seconden
     * @param world Referentie naar de world
     * @param pacman Const referentie naar pacman
     *
     * Wordt aangeroepen elke frame om het ghost's gedrag bij te werken.
     */
    void update(float deltaTime, World& world, const std::shared_ptr<Pacman>& pacman) override;

    /**
     * @brief Zet de fear mode staat van het ghost
     * @param state true om fear mode te activeren, false om te deactiveren
     */
    void setFearState(bool state);

    /**
     * @brief Reset de fear mode staat naar normaal
     */
    void resetFearState();

    /**
     * @brief Controleert of het ghost in fear mode is
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
     * @brief Controleert of het ghost gegeten is
     * @return true als ghost gegeten is, false anders
     */
    bool getHasBeenEaten() const;

    /**
     * @brief Zet de gegeten staat van het ghost
     * @param eaten true als ghost gegeten is, false anders
     */
    void setHasBeenEaten(bool eaten);

    /**
     * @brief Controleert of het ghost klaar is om te bewegen op een specifiek tijdstip
     * @param currentTime Huidig tijdstip in seconden
     * @return true als beweging mogelijk is, false anders
     */
    bool readyToMove(float currentTime) const;

    /**
     * @brief Zet de bewegingsrichting van het ghost
     * @param direct Nieuwe richting
     */
    void setDirection(char direct);

    /**
     * @brief Controleert of het ghost klaar is om te bewegen
     * @return true als beweging mogelijk is, false anders
     */
    bool readyToMove() const;

    /**
     * @brief Geeft de chase delay van het ghost
     * @return Chase delay in seconden
     */
    float getChaseDelay() const;

    /**
     * @brief Kiest een richting tijdens fear mode
     * @param world Referentie naar de world
     * @param pacman Const referentie naar pacman
     *
     * Bepaalt een vluchtrichting weg van pacman tijdens fear mode.
     */
    void chooseDirectionFear(World& world, const std::shared_ptr<Pacman>& pacman);

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
     * @brief Reset het ghost naar beginstate
     */
    void reset();
};

/**
 * @class RedGhost
 * @brief red ghost met vastgezette richting AI
 *
 * Beweegt in een vaste richting en heroverweegt alleen op kruispunten.
 * Agressieve achtervolgingsstrategie.
 */
class RedGhost : public Ghost {
private:
    char lockedDirection; ///< Vastgezette bewegingsrichting

public:
    /**
     * @brief Construeert een RedGhost op opgegeven positie
     * @param x X-coördinaat van het ghost
     * @param y Y-coördinaat van het ghost
     */
    RedGhost(float x, float y);

    /**
     * @brief Update RedGhost logica per frame
     * @param deltaTime Tijd sinds vorige frame in seconden
     * @param world Referentie naar de world
     * @param pacman Const referentie naar pacman
     */
    void update(float deltaTime, World& world, const std::shared_ptr<Pacman>& pacman) override;

    /**
     * @brief Kiest een nieuwe richting gebaseerd op pacman's positie
     * @param pacman Const referentie naar pacman
     */
    void chooseDirection(const std::shared_ptr<Pacman>& pacman);

    /**
     * @brief Accepteert een Visitor voor het Visitor pattern
     * @param visitor Referentie naar de Visitor die het ghost bezoekt
     */
    void accept(Visitor& visitor) override;
};

/**
 * @class BlueGhost
 * @brief blue ghost dat een positie voor pacman uit achtervolgt
 *
 * Voorspelt waar pacman heen gaat en achtervolgt die positie.
 * Heeft een chase delay voor gelaagde uitdaging.
 */
class BlueGhost : public Ghost {
public:
    /**
     * @brief Construeert een BlueGhost op opgegeven positie met delay
     * @param x X-coördinaat van het ghost
     * @param y Y-coördinaat van het ghost
     * @param delay Chase delay in seconden
     */
    BlueGhost(float x, float y, float delay);

    /**
     * @brief Update BlueGhost logica per frame
     * @param deltaTime Tijd sinds vorige frame in seconden
     * @param world Referentie naar de world
     * @param pacman Const referentie naar pacman
     */
    void update(float deltaTime, World& world, const std::shared_ptr<Pacman>& pacman) override;

    /**
     * @brief Kiest een nieuwe richting gebaseerd op voorspelde pacman positie
     * @param world Referentie naar de world
     * @param pacman Const referentie naar pacman
     */
    void chooseDirection(World& world, const std::shared_ptr<Pacman>& pacman);

    /**
     * @brief Accepteert een Visitor voor het Visitor pattern
     * @param visitor Referentie naar de Visitor die het ghost bezoekt
     */
    void accept(Visitor& visitor) override;
};

/**
 * @class PinkGhost
 * @brief pink ghost dat pacman direct achtervolgt
 *
 * Volgt pacman rechtstreeks met kortste pad algoritme.
 * Heeft een chase delay voor gelaagde uitdaging.
 */
class PinkGhost : public Ghost {
public:
    /**
     * @brief Construeert een PinkGhost op opgegeven positie met delay
     * @param x X-coördinaat van het ghost
     * @param y Y-coördinaat van het ghost
     * @param delay Chase delay in seconden
     */
    PinkGhost(float x, float y, float delay);

    /**
     * @brief Update PinkGhost logica per frame
     * @param deltaTime Tijd sinds vorige frame in seconden
     * @param world Referentie naar de world
     * @param pacman Const referentie naar pacman
     */
    void update(float deltaTime, World& world, const std::shared_ptr<Pacman>& pacman) override;

    /**
     * @brief Kiest een nieuwe richting direct naar pacman
     * @param world Referentie naar de world
     * @param pacman Const referentie naar pacman
     */
    void chooseDirection(World& world, const std::shared_ptr<Pacman>& pacman);

    /**
     * @brief Accepteert een Visitor voor het Visitor pattern
     * @param visitor Referentie naar de Visitor die het ghost bezoekt
     */
    void accept(Visitor& visitor) override;
};

#endif // GHOST_H
