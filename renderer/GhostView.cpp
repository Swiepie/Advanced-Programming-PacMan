//
// Created by siebe on 09/11/2025.
//

#include "GhostView.h"
GhostView::GhostView() {
	if (!pacmanTexture.loadFromFile("../sprites/pacman.png")) {
		std::cerr << "Failed to load spritesheet" << std::endl;
	}
	ghostSprite.setTexture(pacmanTexture);
	ghostSprite.setTextureRect(sf::IntRect(0, 0, 15, 15));
}

RedGhostView::RedGhostView() {
	if (!pacmanTexture.loadFromFile("../sprites/pacman.png")) {
		std::cerr << "Failed to load spritesheet" << std::endl;
	}
	ghostSprite.setTexture(pacmanTexture);
	ghostSprite.setTextureRect(sf::IntRect(64, 64, 16, 16));
}
BlueGhostView::BlueGhostView() {
	if (!pacmanTexture.loadFromFile("../sprites/pacman.png")) {
		std::cerr << "Failed to load spritesheet" << std::endl;
	}
	ghostSprite.setTexture(pacmanTexture);
	ghostSprite.setTextureRect(sf::IntRect(64, 96, 16, 16));
}
PinkGhostView::PinkGhostView() {
	 if (!pacmanTexture.loadFromFile("../sprites/pacman.png")) {
		 std::cerr << "Failed to load spritesheet" << std::endl;
	 }
	ghostSprite.setTexture(pacmanTexture);
	ghostSprite.setTextureRect(sf::IntRect(64, 80, 16, 16));
}
FearGhostView::FearGhostView() {
	if (!pacmanTexture.loadFromFile("../sprites/pacman.png")) {
		std::cerr << "Failed to load spritesheet" << std::endl;
	}
	ghostSprite.setTexture(pacmanTexture);
	ghostSprite.setTextureRect(sf::IntRect(64, 80, 16, 16));
}

void GhostView::setTexture(const sf::Texture& texture) {
	pacmanTexture = texture;
}
void GhostView::chooseTexture(char direction){
	float deltaTime = Stopwatch::getInstance().GetElapsedTime();

	if (readyFrame(deltaTime)) {
		mouthOpen = !mouthOpen;
		sf::IntRect rect;
		switch (direction) {
			case 'N': rect = mouthOpen ? sf::IntRect(0, 30, 15, 15)
									   : sf::IntRect(15, 30, 15, 15);
			break;
			case 'Z': rect = mouthOpen ? sf::IntRect(0, 45, 15, 15)
									   : sf::IntRect(15, 45, 15, 15);
			break;
			case 'W': rect = mouthOpen ? sf::IntRect(0, 15, 15, 15)
									   : sf::IntRect(15, 15, 15, 15);
			break;
			case 'O': rect = mouthOpen ? sf::IntRect(0, 0, 15, 15)
									   : sf::IntRect(15, 0, 15, 15);
			break;
		}

		ghostSprite.setTextureRect(rect);
		recordFrameTime(deltaTime);
	}
}

sf::Sprite GhostView::getSprite() {
	return ghostSprite;
}

bool GhostView::readyFrame(float currentTime) const {
	return (currentTime - lastFrameTime) >= frameCooldown;
}

void GhostView::recordFrameTime(float currentTime) {
	lastFrameTime = currentTime;
}

void RedGhostView::chooseTexture(char direction){
	float deltaTime = Stopwatch::getInstance().GetElapsedTime();

	sf::Texture pacmanTexture;
	if (!pacmanTexture.loadFromFile("../sprites/pacman.png")) {
		std::cerr << "Failed to load spritesheet" << std::endl;
	}

	setTexture(pacmanTexture);
	if (readyFrame(deltaTime)) {
		mouthOpen = !mouthOpen;
		sf::IntRect rect;
		switch (direction) {
			case 'N': rect = mouthOpen ? sf::IntRect(64, 64, 16, 16)
									   : sf::IntRect(80, 64, 16, 16);
			break;
			case 'Z': rect = mouthOpen ? sf::IntRect(96, 64, 16, 16)
									   : sf::IntRect(112, 64, 16, 16);
			break;
			case 'W': rect = mouthOpen ? sf::IntRect(32, 64, 16, 16)
									   : sf::IntRect(48, 64, 16, 16);
			break;
			case 'O': rect = mouthOpen ? sf::IntRect(0, 64, 16, 16)
									   : sf::IntRect(16, 64, 16, 16);
			break;
		}

		ghostSprite.setTextureRect(rect);
		recordFrameTime(deltaTime);
	}
}
void BlueGhostView::chooseTexture(char direction){
	float deltaTime = Stopwatch::getInstance().GetElapsedTime();

	sf::Texture pacmanTexture;
	if (!pacmanTexture.loadFromFile("../sprites/pacman.png")) {
		std::cerr << "Failed to load spritesheet" << std::endl;
	}

	setTexture(pacmanTexture);
	if (readyFrame(deltaTime)) {
		mouthOpen = !mouthOpen;
		sf::IntRect rect;
		switch (direction) {
			case 'N': rect = mouthOpen ? sf::IntRect(64, 96, 16, 16)
									   : sf::IntRect(80, 96, 16, 16);
			break;
			case 'Z': rect = mouthOpen ? sf::IntRect(96, 96, 16, 16)
									   : sf::IntRect(112, 96, 16, 16);
			break;
			case 'W': rect = mouthOpen ? sf::IntRect(32, 96, 16, 16)
									   : sf::IntRect(48, 96, 16, 16);
			break;
			case 'O': rect = mouthOpen ? sf::IntRect(0, 96, 16, 16)
									   : sf::IntRect(16, 96, 16, 16);
			break;
		}

		ghostSprite.setTextureRect(rect);
		recordFrameTime(deltaTime);
	}
}
void PinkGhostView::chooseTexture(char direction){
	float deltaTime = Stopwatch::getInstance().GetElapsedTime();

	sf::Texture pacmanTexture;
	if (!pacmanTexture.loadFromFile("../sprites/pacman.png")) {
		std::cerr << "Failed to load spritesheet" << std::endl;
	}

	setTexture(pacmanTexture);
	if (readyFrame(deltaTime)) {
		mouthOpen = !mouthOpen;
		std::cout << direction << std::endl;
		sf::IntRect rect;
		switch (direction) {
			case 'N': rect = mouthOpen ? sf::IntRect(64, 80, 16, 16)
									   : sf::IntRect(80, 80, 16, 16);
			break;
			case 'Z': rect = mouthOpen ? sf::IntRect(96, 80, 16, 16)
									   : sf::IntRect(112, 80, 16, 16);
			break;
			case 'W': rect = mouthOpen ? sf::IntRect(32, 80, 16, 16)
									   : sf::IntRect(48, 80, 16, 16);
			break;
			case 'O': rect = mouthOpen ? sf::IntRect(0, 80, 16, 16)
									   : sf::IntRect(16, 80, 16, 16);
			break;
		}

		ghostSprite.setTextureRect(rect);
		recordFrameTime(deltaTime);
	}
}

void FearGhostView::chooseTexture() {
	float deltaTime = Stopwatch::getInstance().GetElapsedTime();

	sf::Texture pacmanTexture;
	if (!pacmanTexture.loadFromFile("../sprites/pacman.png")) {
		std::cerr << "Failed to load spritesheet" << std::endl;
	}

	setTexture(pacmanTexture);
	if (readyFrame(deltaTime)) {
		mouthOpen = !mouthOpen;
		sf::IntRect rect;
		 rect = mouthOpen ? sf::IntRect(128, 64, 16, 16)
									   : sf::IntRect(144, 64, 16, 16);

		ghostSprite.setTextureRect(rect);
		recordFrameTime(deltaTime);
	}
}