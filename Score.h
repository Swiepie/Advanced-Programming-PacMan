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
	void reset();
	void add(int points);
	int get() const;
	void submit();
	const std::vector<int>& getTop5() const;
};


#endif //SCORE_H
