/**
 * @file Scoreboard.h
 * @brief Beheert de highscores van het pacman spel
 * @author siebe
 * @date 30/11/2025
 */

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

/**
 * @class Scoreboard
 * @brief Klasse voor het beheren van highscores
 *
 * Beheert een lijst van highscores, inclusief laden en opslaan naar een bestand,
 * toevoegen van nieuwe scores en ophalen van de top 5 scores.
 */
class Scoreboard {
private:
    std::vector<int> highscores; ///< Vector die alle highscores bevat
    std::string filename;        ///< Bestandsnaam voor persistente opslag van scores

public:
    /**
     * @brief Construeert een Scoreboard met opgegeven bestandsnaam
     * @param file Bestandsnaam voor het opslaan van highscores (standaard: "highscores.txt")
     */
    explicit Scoreboard(const std::string& file = "highscores.txt");

    /**
     * @brief Laadt highscores uit het bestand
     *
     * Leest alle scores uit het opgegeven bestand en slaat ze op in de highscores vector.
     */
    void load();

    /**
     * @brief Slaat highscores op naar het bestand
     *
     * Schrijft alle huidige scores naar het opgegeven bestand voor persistente opslag.
     */
    void save();

    /**
     * @brief Voegt een nieuwe score toe aan de highscores
     * @param score De nieuwe score om toe te voegen
     *
     * Voegt de score toe en sorteert de lijst automatisch van hoog naar laag.
     */
    void addScore(int score);

    /**
     * @brief Geeft de top 5 hoogste scores
     * @return Const referentie naar vector met maximaal 5 hoogste scores
     */
    const std::vector<int>& getTop5() const;
};

#endif // SCOREBOARD_H
