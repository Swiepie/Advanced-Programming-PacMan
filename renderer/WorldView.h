//
// Created by Siebe Haché on 15/10/2025.
//

#ifndef WORLDVIEW_H
#define WORLDVIEW_H



#include <SFML/Graphics.hpp>
#include "../World.h"

class WorldView {
public:
    void render(const World& world, sf::RenderWindow& window);
};



#endif //WORLDVIEW_H
