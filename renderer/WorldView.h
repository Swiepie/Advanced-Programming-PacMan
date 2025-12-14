//
// Created by Siebe Haché on 15/10/2025.
//

#ifndef WORLDVIEW_H
#define WORLDVIEW_H




#include "../logic/World.h"
#include "PacmanView.h"
#include "GhostView.h"
#include <memory>
#include "../ConcreteFactory.h"
#include "Camera.h"

class WorldView {
    private:
    ConcreteFactory* factory = nullptr;
    int lastLives = 0;
    int round = 0;

public:
    static void render(const World& world, std::shared_ptr<sf::RenderWindow> window, float windowWidth, float windowHeight);
};



#endif //WORLDVIEW_H
