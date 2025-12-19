/**
 * @file Score.h
 * @brief Beheert het scoresysteem van het pacman spel
 * @author Siebe Haché
 * @date 14/10/2025
 */

#ifndef SCORE_H
#define SCORE_H
#include <iostream>

#include "Scoreboard.h"

/**
 * @class Score
 * @brief Klasse voor het beheren van de huidige spelscore en combos
 *
 * Houdt de huidige score bij, beheert ghost combo's, tijdgebaseerde vervalmechanismen
 * en interactie met het scoreboard voor highscores.
 */
class Score {
private:
    int ghostCombo = 0;         ///< Huidige combo voor opeenvolgende spoken gegeten
    int currentScore = 0;       ///< Huidige totale score van de speler
    float lastDecayTime = 0.0f; ///< Tijdstip van laatste score verval
    float lastCoinTime = 0.0f;  ///< Tijdstip van laatste verzamelde coin
    Scoreboard scoreboard;      ///< Scoreboard instantie voor highscore beheer

public:
    /**
     * @brief Reset de score naar beginwaarden
     *
     * Zet alle score-gerelateerde variabelen terug naar hun initiële staat.
     */
    void reset();

    /**
     * @brief Voegt punten toe voor het verzamelen van een coin
     * @param currentTime Huidige speltijd voor tijdgebaseerde berekeningen
     *
     * Verhoogt de score wanneer een coin verzameld wordt, rekening houdend met timing.
     */
    void addCoin(float currentTime);

    /**
     * @brief Voegt punten toe voor het eten van een ghost
     * @param basePoints Basispunten voor het ghost
     *
     * Verhoogt de score met combopunten gebaseerd op opeenvolgende spoken gegeten.
     */
    void addGhost(int basePoints);

    /**
     * @brief Reset de ghost combo teller naar nul
     *
     * Wordt aangeroepen wanneer de combo onderbroken wordt.
     */
    void resetGhostCombo();

    /**
     * @brief Voegt punten toe voor het verzamelen van fruit
     * @param basePoints Basispunten voor het fruit
     *
     * Verhoogt de score met de opgegeven fruitpunten.
     */
    void addFruit(int basePoints);

    /**
     * @brief Update de score logica elk frame
     * @param currentTime Huidige speltijd
     *
     * Beheert tijdgebaseerde score vervalmechanismen en andere tijdafhankelijke logica.
     */
    void update(float currentTime);

    /**
     * @brief Geeft de huidige score
     * @return Huidige score als integer
     */
    int get() const;

    /**
     * @brief Dient de huidige score in bij het scoreboard
     *
     * Voegt de huidige score toe aan de highscores en slaat deze op.
     */
    void submit();

    /**
     * @brief Geeft de top 5 highscores
     * @return Const referentie naar vector met de 5 hoogste scores
     */
    const std::vector<int>& getTop5() const;
};

#endif // SCORE_H