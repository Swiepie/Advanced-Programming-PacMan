//
// Created by siebe on 02/11/2025.
//

#ifndef PACMANVIEW_H
#define PACMANVIEW_H

#include <SFML/Graphics.hpp>
#include "..//Stopwatch.h"
#include "../entities/Pacman.h"
#include <iostream>
#include "EntityView.h"
#include "Camera.h"
class PacmanView : public EntityView {
private:
    float totalTime = 0.0;
    bool mouthOpen = true;
    double frameCooldown = 1.0/15;
    float frameTimer = 0.0f;
    double speed = 1;
    float lastFrameTime = 0.0f;

    int i = 2;
    sf::Texture pacmanTexture;
    sf::Sprite pacmanSprite;
public:
    explicit PacmanView(Pacman* pacman);

    void update() override; // Observer pattern
    void updateTexture(float time) override;
    void chooseTexture(char direction, float time);
};



#endif //PACMANVIEW_H
