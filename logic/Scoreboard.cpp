//
// Created by siebe on 30/11/2025.
//

#include "Scoreboard.h"

#include <iostream>

Scoreboard::Scoreboard(const std::string& file) : filename(file) { load(); }

void Scoreboard::load() {
    highscores.clear();
    std::ifstream file(filename);

    if (!file.is_open())
        return;

    int s;
    while (file >> s)
        highscores.push_back(s);

    // sorteer grootste eerst
    std::sort(highscores.begin(), highscores.end(), std::greater<>());
}

void Scoreboard::save() {
    std::cout << "Scoreboard::save()" << std::endl;
    std::ofstream file(filename, std::ios::trunc);
    for (int i = 0; i < highscores.size() && i < 5; i++)
        file << highscores[i] << "\n";
}

void Scoreboard::addScore(int score) {
    load();
    highscores.push_back(score);

    std::sort(highscores.begin(), highscores.end(), std::greater<>());

    if (highscores.size() > 5)
        highscores.resize(5); // alleen top 5 bijhouden

    save();
}

const std::vector<int>& Scoreboard::getTop5() const { return highscores; }