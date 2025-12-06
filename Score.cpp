//
// Created by Siebe Haché on 14/10/2025.
//

#include "Score.h"
void Score::reset() {
	currentScore = 0;
}

void Score::add(int points) {
	currentScore += points;
}

int Score::get() const {
	return currentScore;
}

void Score::submit() {
	scoreboard.addScore(currentScore);
	std::cout << currentScore << "\n";
}

const std::vector<int>& Score::getTop5() const {
	return scoreboard.getTop5();
}
