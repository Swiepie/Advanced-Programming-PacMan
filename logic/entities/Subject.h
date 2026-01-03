/**
* @file Subject.h
 * @brief Definieert de Subject klasse voor het Observer design pattern
 * @author siebe
 * @date 12/12/2025
 */

#ifndef SUBJECT_H
#define SUBJECT_H

#include "../Observer.h"

/**
 * @class Subject
 * @brief Klasse die observeerbaar gedrag implementeert voor het Observer pattern
 *
 * Beheert een enkele observer en notificeert deze wanneer de staat verandert.
 */
class Subject {
private:
    Observer* observer = nullptr; ///< De geregistreerde observer

public:
    /**
     * @brief Virtual destructor voor correcte cleanup van afgeleide klassen
     */
    virtual ~Subject() = default;

    /**
     * @brief Registreert een observer bij dit subject
     * @param obs Pointer naar de observer die geregistreerd moet worden
     */
    void attach(Observer* obs);

    /**
     * @brief Verwijdert de observer van dit subject
     */
    void detach();

    /**
     * @brief Notificeert de geregistreerde observer
     */
    void notify();

    /**
     * @brief Geeft directe toegang tot de observer
     * @return Pointer naar de observer (meestal de view)
     */
    Observer* getObserver() const;
};

#endif // SUBJECT_H
