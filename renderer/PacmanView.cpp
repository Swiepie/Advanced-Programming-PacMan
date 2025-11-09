//
// Created by siebe on 02/11/2025.
//

#include "PacmanView.h"
#include <iostream>
PacmanView::PacmanView() {
  if (!pacmanTexture.loadFromFile("../sprites/pacman.png")) {
    std::cerr << "Failed to load spritesheet" << std::endl;
  }
  pacmanSprite.setTexture(pacmanTexture);
  pacmanSprite.setTextureRect(sf::IntRect(0, 0, 15, 15));
}

void PacmanView::setTexture(const sf::Texture& texture) {
  pacmanTexture = texture;
}
void PacmanView::chooseTexture(char direction){
  float deltaTime = Stopwatch::getInstance().GetElapsedTime();


  setTexture(pacmanTexture);
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

    pacmanSprite.setTextureRect(rect);
    recordFrameTime(deltaTime);
  }
}

sf::Sprite PacmanView::getSprite() {
  return pacmanSprite;
}

bool PacmanView::readyFrame(float currentTime) const {
  return (currentTime - lastFrameTime) >= frameCooldown;
}

void PacmanView::recordFrameTime(float currentTime) {
  lastFrameTime = currentTime;
}