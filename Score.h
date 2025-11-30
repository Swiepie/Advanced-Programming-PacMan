//
// Created by Siebe Haché on 14/10/2025.
//

#ifndef SCORE_H
#define SCORE_H
#include <iostream>

#include "Scoreboard.h"


class Score {
private:
	int currentScore = 0;


	Scoreboard scoreboard;
public:
	void reset() {
		currentScore = 0;
	}

	void add(int points) {
		currentScore += points;
	}

	int get() const {
		return currentScore;
	}

	void submit() {
		scoreboard.addScore(currentScore);
		std::cout << currentScore << "\n";
	}

	const std::vector<int>& getTop5() const {
		return scoreboard.getTop5();
	}
};


#endif //SCORE_H
