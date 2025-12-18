/**
* @file Observer.h
 * @brief Definieert de Observer interface voor het Observer design pattern
 * @author siebe
 * @date 12/12/2025
 */

#ifndef OBSERVER_H
#define OBSERVER_H

/**
 * @class Observer
 * @brief Abstract base class voor observers in het Observer pattern
 *
 * Biedt een interface voor objecten die notificaties willen ontvangen wanneer
 * de staat van een Subject verandert. Ondersteunt zowel eenvoudige als tijdgebaseerde updates.
 */
class Observer {
public:
    /**
     * @brief Update methode zonder parameters
     *
     * Wordt aangeroepen wanneer het geobserveerde subject verandert.
     * Te implementeren door concrete observer klassen voor eenvoudige notificaties.
     */
    virtual void update() = 0;

    /**
     * @brief Virtual destructor voor correcte cleanup van afgeleide klassen
     *
     * Zorgt ervoor dat afgeleide klassen correct worden opgeruimd bij verwijdering
     * via een basisklasse pointer.
     */
    virtual ~Observer() = default;

    /**
     * @brief Update methode met tijdparameter
     * @param time Huidige speltijd of tijdstempel
     *
     * Wordt aangeroepen voor tijdgebaseerde updates van het geobserveerde subject.
     * Te implementeren door concrete observer klassen die tijdsinformatie nodig hebben.
     */
    virtual void update(float time) = 0;
};

#endif // OBSERVER_H
