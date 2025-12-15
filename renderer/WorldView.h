//
// Created by Siebe Haché on 15/10/2025.
//

#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include "../ConcreteFactory.h"
#include "../logic/World.h"
#include "Camera.h"
#include "GhostView.h"
#include "PacmanView.h"
#include <memory>

class WorldView {
private:
    ConcreteFactory* factory = nullptr;
    int lastLives = 0;
    int round = 0;

public:
    static void render(std::shared_ptr<World> world, std::shared_ptr<sf::RenderWindow> window, float windowWidth,
                       float windowHeight);
};

#endif // WORLDVIEW_H
