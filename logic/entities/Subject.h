/**
 * @file Subject.h
 * @brief Definieert de Subject klasse voor het Observer design pattern
 * @author siebe
 * @date 12/12/2025
 */

#ifndef SUBJECT_H
#define SUBJECT_H

#include "../Observer.h"
#include <algorithm>
#include <memory>
#include <vector>

/**
 * @class Subject
 * @brief Klasse die observeerbaar gedrag implementeert voor het Observer pattern
 *
 * Beheert een lijst van observers en notificeert deze wanneer de staat verandert.
 * Ondersteunt een primaire observer (typisch de view) voor directe toegang.
 */
class Subject {
private:
    std::vector<Observer*> observers;    ///< Lijst van geregistreerde observers
    Observer* primaryObserver = nullptr; ///< Primaire observer (meestal de view)

public:
    /**
     * @brief Virtual destructor voor correcte cleanup van afgeleide klassen
     */
    virtual ~Subject() = default;

    /**
     * @brief Registreert een observer bij dit subject
     * @param observer Pointer naar de observer die geregistreerd moet worden
     *
     * Voegt een observer toe aan de lijst van objecten die genotificeerd worden bij veranderingen.
     */
    void attach(Observer* observer);

    /**
     * @brief Verwijdert een observer van dit subject
     * @param observer Pointer naar de observer die verwijderd moet worden
     *
     * Verwijdert een observer uit de lijst zodat deze geen notificaties meer ontvangt.
     */
    void detach(Observer* observer);

    /**
     * @brief Notificeert alle geregistreerde observers
     *
     * Roept de update() methode aan op alle observers om hen op de hoogte te brengen
     * van veranderingen in de staat van dit subject.
     */
    void notify();

    /**
     * @brief Geeft directe toegang tot de primaire observer
     * @return Pointer naar de primaire observer (meestal de view)
     *
     * Biedt directe toegang tot de view observer voor efficiënte communicatie. Dit hebben we nodig voor de rendering.
     */
    Observer* getObserver() const;
};

#endif // SUBJECT_H
