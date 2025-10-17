//
// Created by Siebe Haché on 15/10/2025.
//

#ifndef WORLDVIEW_H
#define WORLDVIEW_H



#include <SFML/Graphics.hpp>
#include "../World.h"

class WorldView {
public:
    static void render(const World& world, sf::RenderWindow& window, float windowWidth, float windowHeight);
};



#endif //WORLDVIEW_H
