//
// Created by siebe on 02/11/2025.
//

#ifndef PACMANVIEW_H
#define PACMANVIEW_H

#include <SFML/Graphics.hpp>
#include "..//Stopwatch.h"
#include <iostream>
class PacmanView {
private:
    bool mouthOpen = true;
    double frameCooldown = 1.0/30;
    float frameTimer = 0.0f;
    double speed = 1;
    float lastFrameTime = 0.0f;

    sf::Texture pacmanTexture;
    sf::Sprite pacmanSprite;
public:
    PacmanView() {
        if (!pacmanTexture.loadFromFile("../sprites/pacman.png")) {
            std::cerr << "Failed to load spritesheet" << std::endl;
        }
        pacmanSprite.setTexture(pacmanTexture);
        pacmanSprite.setTextureRect(sf::IntRect(0, 0, 15, 15));
    }

    void setTexture(sf::Texture texture);
    void chooseTexture(char direction);

    bool readyFrame(float currentTime) const {
        return (currentTime - lastFrameTime) >= frameCooldown;
    }

    void recordFrameTime(float currentTime) {
        lastFrameTime = currentTime;
    }
    sf::Sprite getSprite();
};



#endif //PACMANVIEW_H
