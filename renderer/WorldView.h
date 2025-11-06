//
// Created by Siebe Haché on 15/10/2025.
//

#ifndef WORLDVIEW_H
#define WORLDVIEW_H




#include "../World.h"
#include "PacmanView.h"
#include <memory>

class WorldView {
    private:
    PacmanView pacmanview;
public:
    void render(const World& world, sf::RenderWindow& window, float windowWidth, float windowHeight);
};



#endif //WORLDVIEW_H
