//
// Created by Siebe Haché on 14/10/2025.
//

#ifndef WORLD_H
#define WORLD_H



#include <string>
#include <vector>
#include <memory>
#include "Entity.h"
#include <SFML/Graphics.hpp>

class World {
private:
    std::vector<std::unique_ptr<Entity>> entities;
    float tileSize = 32.0f;
    std::vector<std::string> mapData;
    int width;
    int height;

public:

    bool loadMap(const std::string& filename);
    void printMap() const; //debug
    void update(float deltaTime);

    const std::vector<std::unique_ptr<Entity>>& getEntities() const;
    int getWidth() const;
    int getHeight() const;
};



#endif //WORLD_H
