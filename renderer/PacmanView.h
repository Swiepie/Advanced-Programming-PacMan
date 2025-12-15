//
// Created by siebe on 02/11/2025.
//

#ifndef PACMANVIEW_H
#define PACMANVIEW_H

#include "../logic/Stopwatch.h"
#include "../logic/entities/Pacman.h"
#include "Camera.h"
#include "EntityView.h"
#include <SFML/Graphics.hpp>
#include <iostream>
class PacmanView : public EntityView {
protected:
    Pacman* pacman;

private:
    float totalTime = 0.0;
    bool mouthOpen = true;
    float frameTimer = 0.0f;
    double speed = 1;

    int i = 2;

public:
    explicit PacmanView(Pacman* pacman, std::shared_ptr<sf::RenderWindow> window, int height, int width);
    void update(float time) override;
    void update() override; // Observer pattern
    void updateTexture(float time) override;
    void chooseTexture(char direction, float time);
    void render() override;
};

#endif // PACMANVIEW_H
