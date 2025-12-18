/**
 * @file Random.h
 * @brief Implementeert een singleton random number generator voor het spel
 * @author Siebe Haché
 * @date 14/10/2025
 */

#ifndef RANDOM_H
#define RANDOM_H

#include <array>
#include <chrono>
#include <random>

/**
 * @class Random
 * @brief Singleton klasse voor het genereren van willekeurige getallen
 *
 * Biedt functionaliteit voor het genereren van willekeurige integers, floats en richtingen.
 * Gebruikt het Singleton patroon om consistente randomisatie door het hele spel te garanderen.
 */
class Random {
private:
    std::mt19937 engine;  ///< Mersenne Twister random number generator

    /**
     * @brief Private constructor voor singleton patroon
     *
     * Initialiseert de random engine met een echte willekeurige seed
     * gegenereerd door std::random_device.
     */
    Random() {
        // Gebruik een random_device om een echte willekeurige seed te verkrijgen
        std::random_device rd;
        std::seed_seq seedSeq{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
        engine.seed(seedSeq);
    }

public:
    Random(const Random&) = delete;              ///< Verwijderd - voorkomt kopiëren
    Random& operator=(const Random&) = delete;   ///< Verwijderd - voorkomt toewijzing

    /**
     * @brief Geeft de singleton instantie van de Random generator
     * @return Referentie naar de unieke Random instantie
     */
    static Random& getInstance();

    /**
     * @brief Genereert een willekeurig geheel getal binnen opgegeven bereik
     * @param min Minimale waarde (inclusief)
     * @param max Maximale waarde (inclusief)
     * @return Willekeurig integer tussen min en max
     */
    int getInt(int min, int max);

    /**
     * @brief Genereert een willekeurig kommagetal binnen opgegeven bereik
     * @param min Minimale waarde (inclusief)
     * @param max Maximale waarde (inclusief)
     * @return Willekeurig float tussen min en max
     */
    float getFloat(float min, float max);

    /**
     * @brief Genereert een willekeurige bewegingsrichting
     * @return Willekeurig richtingskarakter voor Pac-Man/spoken beweging
     */
    char getRandomDirection();

    /**
     * @brief Geeft directe toegang tot de onderliggende random engine
     * @return Referentie naar de Mersenne Twister engine
     *
     * Optioneel: biedt toegang tot de engine voor geavanceerde random operaties.
     */
    std::mt19937& getEngine();
};

#endif // RANDOM_H
