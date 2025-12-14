//
// Created by Siebe Haché on 14/10/2025.
//

#ifndef SCORE_H
#define SCORE_H
#include <iostream>

#include "Scoreboard.h"


class Score {
private:
	int ghostCombo = 0;
	int currentScore = 0;
	float lastDecayTime = 0.0f;
	float lastCoinTime = 0.0f;
	Scoreboard scoreboard;
public:
	void reset();
	void addCoin(float currentTime);
	void addGhost(int basePoints);
	void resetGhostCombo();
	void addFruit(int basePoints);
	void update(float currentTime);
	int get() const;
	void submit();
	const std::vector<int>& getTop5() const;
};


#endif //SCORE_H
