/**
 * @file Stopwatch.h
 * @brief Implementeert een singleton stopwatch voor tijdmeting in het spel
 * @author Siebe Haché
 * @date 14/10/2025
 */

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

/**
 * @class Stopwatch
 * @brief Singleton klasse voor het meten en beheren van speltijd
 *
 * Biedt functionaliteit voor het starten, stoppen, pauzeren en resetten van een timer.
 * Gebruikt het Singleton patroon om één centrale tijdsbron voor het hele spel te garanderen.
 */
class Stopwatch {
private:
    /**
     * @brief Private constructor voor singleton patroon
     *
     * Initialiseert de stopwatch in niet-actieve en niet-gepauzeerde staat.
     */
    Stopwatch() : running(false), paused(false) {}

    bool running;                                      ///< Geeft aan of de stopwatch actief is
    bool paused;                                       ///< Geeft aan of de stopwatch gepauzeerd is
    std::chrono::steady_clock::time_point startTime;  ///< Tijdstip waarop de stopwatch gestart is
    std::chrono::steady_clock::duration elapsed{};    ///< Verstreken tijd sinds start

public:
    /**
     * @brief Geeft de singleton instantie van de Stopwatch
     * @return Referentie naar de unieke Stopwatch instantie
     */
    static Stopwatch& getInstance() {
        static Stopwatch instance; // één instantie in het hele programma
        return instance;
    }

    Stopwatch(const Stopwatch&) = delete;              ///< Verwijderd - voorkomt kopiëren
    Stopwatch& operator=(const Stopwatch&) = delete;   ///< Verwijderd - voorkomt toewijzing

    /**
     * @brief Start de stopwatch
     *
     * Begin met tijdmeting vanaf het huidige moment.
     */
    void start();

    /**
     * @brief Stopt de stopwatch
     *
     * Beëindigt tijdmeting en behoudt de verstreken tijd.
     */
    void stop();

    /**
     * @brief Pauzeert de stopwatch
     *
     * Pauzeert tijdmeting terwijl de huidige verstreken tijd behouden blijft.
     */
    void pause();

    /**
     * @brief Reset de stopwatch naar beginwaarden
     *
     * Zet alle tijdwaarden terug naar nul en stopt de timer.
     */
    void reset();

    /**
     * @brief Herstart de stopwatch
     *
     * Reset en start de stopwatch opnieuw vanaf nul.
     */
    void restart();

    /**
     * @brief Geeft de verstreken tijd in seconden
     * @return Verstreken tijd als float in seconden
     */
    float GetElapsedTime() const;
};

#endif // STOPWATCH_H