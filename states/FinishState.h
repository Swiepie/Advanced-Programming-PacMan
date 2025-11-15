//
// Created by siebe on 15/11/2025.
//

#ifndef FINISHSTATE_H
#define FINISHSTATE_H

#include "State.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "MenuState.h"
#include "StateManager.h"
#include "LevelState.h"
#include <SFML/Window/Event.hpp>
#include "../World.h"
#include <iostream>

class FinishState : public State {
private:
	sf::Font font;
	sf::Text title;
	int finalScore = 0;
	void updateText() {
		title.setString("Score: " + std::to_string(finalScore) + "\nPress SPACE to return to menu");
	}

public:
	explicit FinishState(int score) : finalScore(score) {
		font.loadFromFile("../assets/ARIAL.TTF");
		title.setFont(font);
		title.setFillColor(sf::Color::Green);
		updateText();
	}

	void handleEvent(StateManager& manager, sf::RenderWindow& window, const sf::Event& event) override;
	void update(StateManager& manager, float deltaTime) override {}
	void render(sf::RenderWindow& window,unsigned int windowWidth, unsigned int windowHeight) override;
	void onEnter() override;
};



#endif //FINISHSTATE_H
