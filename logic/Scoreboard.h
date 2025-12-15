//
// Created by siebe on 30/11/2025.
//

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

class Scoreboard {
private:
    std::vector<int> highscores;
    std::string filename;

public:
    explicit Scoreboard(const std::string& file = "highscores.txt");

    void load();              // lees bestand
    void save();              // schrijf bestand
    void addScore(int score); // nieuwe score toevoegen
    const std::vector<int>& getTop5() const;
};

#endif // SCOREBOARD_H
