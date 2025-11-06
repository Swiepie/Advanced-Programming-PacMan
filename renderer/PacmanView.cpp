//
// Created by siebe on 02/11/2025.
//

#include "PacmanView.h"
#include <iostream>
void PacmanView::setTexture(sf::Texture texture) {
  pacmanTexture = texture;
}
void PacmanView::chooseTexture(char direction){
  std::cout << "PacmanView::chooseTexture  " << direction << std::endl;
  float deltaTime = Stopwatch::getInstance().GetElapsedTime();
  bool changed = false;

  sf::Texture pacmanTexture;
  if (!pacmanTexture.loadFromFile("../sprites/pacman.png")) {
    std::cerr << "Failed to load spritesheet" << std::endl;
  }
  sf::IntRect rect;
  setTexture(pacmanTexture);
  if (readyFrame(deltaTime)) {
    mouthOpen = !mouthOpen;
    sf::IntRect rect;

    switch (direction) {
      case 'N': rect = mouthOpen ? sf::IntRect(0, 0, 15, 15)
                                 : sf::IntRect(15, 0, 15, 15);
      break;
      case 'Z': rect = mouthOpen ? sf::IntRect(0, 15, 15, 15)
                                 : sf::IntRect(15, 15, 15, 15);
      break;
      case 'W': rect = mouthOpen ? sf::IntRect(0, 30, 15, 15)
                                 : sf::IntRect(15, 30, 15, 15);
      break;
      case 'O': rect = mouthOpen ? sf::IntRect(0, 45, 15, 15)
                                 : sf::IntRect(15, 45, 15, 15);
      break;
    }

    pacmanSprite.setTextureRect(rect);
    recordFrameTime(deltaTime);
  }
  rect = sf::IntRect(0, 0, 15, 15);
  if (changed) {
    std::cout << "changed" << std::endl;
    //slaag de tijd op van laatste frame
    recordFrameTime(deltaTime);
    pacmanSprite.setTextureRect(rect);
  }
}

sf::Sprite PacmanView::getSprite() {
  return pacmanSprite;
}