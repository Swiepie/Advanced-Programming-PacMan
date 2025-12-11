//
// Created by Siebe Haché on 14/10/2025.
//
#include <cmath>
#include "Score.h"
void Score::reset() {
	currentScore = 0;
	lastDecayTime = 0.0f;
	lastCoinTime = 0.0f;
}

void Score::addCoin(float currentTime) {
	float dt = currentTime - lastCoinTime;

	// Exponentiële combo: snelle coins → grote bonus
	float k = 1.0f;
	float multiplier = std::exp(-k * dt) + 1.0f;

	int basePoints = 10;
	int added = static_cast<int>(basePoints * multiplier);

	currentScore += added;
	lastCoinTime = currentTime;
}

void Score::addGhost(int basePoints) {
	ghostCombo++; // combo stijgt in fear mode

	int comboMultiplier = 1 << (ghostCombo - 1); // bitshift: 2^(combo-1)
	int added = basePoints * comboMultiplier;

	currentScore += added;
}
void Score::resetGhostCombo() {
	ghostCombo = 0;
}

void Score::addFruit(int basePoints) {
	currentScore += basePoints;
}

void Score::update(float currentTime) {
	float decayRate = 1.f;     // punten per seconde
	float decayDelay = 0.5f;    // hoe lang wachten na laatste coin voor decay start

	// Pas decay toe *alleen* als je langer dan 0.5s geen coin hebt gegeten
	if (currentTime - lastCoinTime > decayDelay) {

		if (currentTime - lastDecayTime > 1.0f) {
			currentScore -= decayRate;
			if (currentScore < 0) currentScore = 0;

			lastDecayTime = currentTime;
		}
	}
}

int Score::get() const {
	return currentScore;
}

void Score::submit() {
	scoreboard.addScore(currentScore);
}

const std::vector<int>& Score::getTop5() const {
	return scoreboard.getTop5();
}