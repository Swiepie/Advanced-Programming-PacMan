//
// Created by Siebe Haché on 14/10/2025.
//

#ifndef WORLD_H
#define WORLD_H



#include <string>
#include <vector>
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
    const std::vector<std::unique_ptr<Entity>>& getEntities() const {
        return entities;
    }
    bool loadMap(const std::string& filename);
    void printMap() const;
    void update(float deltaTime);
};



#endif //WORLD_H
