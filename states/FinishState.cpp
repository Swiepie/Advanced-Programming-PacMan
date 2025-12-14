//
// Created by siebe on 15/11/2025.
//

#include "FinishState.h"




void FinishState::handleEvent(std::shared_ptr<StateManager> stateManager, std::shared_ptr<sf::RenderWindow> window, const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
		stateManager->popState(); // go to the level
		stateManager->popState(); // pop level
		stateManager->popState(); // pop menu
		stateManager->pushState(std::make_unique<MenuState>(factory));
	} else if (event.type == sf::Event::Closed) {
		window->close();
	}
}
void FinishState::render(std::shared_ptr<sf::RenderWindow> window,unsigned int windowWidth, unsigned int windowHeight) {
	sf::Vector2f viewSize = window->getView().getSize();
	sf::Vector2f viewCenter = window->getView().getCenter();

	//schaal op basis van hoogte
	float preferredHeight = viewSize.y * 0.10f;       // 10% van schermhoogte
	float textHeight = title.getLocalBounds().height;

	float scaleY = preferredHeight / textHeight;

	//controleer breedte
	float maxWidth = viewSize.x * 0.80f;  // Tekst mag 80% van breedte nemen
	float textWidth = title.getLocalBounds().width;

	float scaleX = maxWidth / textWidth;

	// MIN
	float scale = std::min(scaleX, scaleY);

	title.setScale(scale, scale);

	// centreer tekst
	title.setOrigin(
		title.getLocalBounds().width / 2.f,
		title.getLocalBounds().height / 2.f
	);

	title.setPosition(viewCenter);
	window->draw(title);
}
void FinishState::onEnter() {
	Stopwatch::getInstance().reset(); // reset + start timer when entering game
	std::cout << "reset\n";
}

void FinishState::updateText() {
	title.setString("Score: " + std::to_string(finalScore) + "\nPress SPACE to return to menu");
}