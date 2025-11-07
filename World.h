//
// Created by Siebe Haché on 14/10/2025.
//

#ifndef WORLD_H
#define WORLD_H



#include <string>
#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#include "entities/Entity.h"
#include "entities/Coin.h"
#include "entities/Pacman.h"
#include "entities/Wall.h"
#include "entities/Fruit.h"

class World {
private:
    std::vector<std::unique_ptr<Entity>> entities;
    Pacman* pacman = nullptr;
    float tileSize = 32.0f;
    std::vector<std::string> mapData;
    int width = 0;
    int height = 0;
    int coinCount = 0;

public:

    bool loadMap(const std::string& filename);
    void printMap() const; //debug
    void update(float deltaTime);

    const std::vector<std::unique_ptr<Entity>>& getEntities() const;
    int getWidth() const;
    int getHeight() const;

    bool tryMove(Pacman* pacman, char dir) const;
    Pacman* getPacman() const;
    void checkCollisions();

};



#endif //WORLD_H
