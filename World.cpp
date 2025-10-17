//
// Created by Siebe Haché on 14/10/2025.
//

#include "World.h"
#include <fstream>
#include <iostream>
#include "Entity.h"
#include "Coin.h"
#include "Wall.h"
bool World::loadMap(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open map file " << filename << std::endl;
        return false;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) lines.push_back(line);
    }

    int numRows = static_cast<int>(lines.size());
    int numCols = numRows > 0 ? static_cast<int>(lines[0].size()) : 0;
    width = numCols;
    height = numRows;

    if (numRows == 0 || numCols == 0) return false;

    float tileWidth  = 2.0f / numCols;
    float tileHeight = 2.0f / numRows;

    entities.clear();

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            char c = lines[row][col];

            float x = -1.0f + col * tileWidth;
            float y = -1.0f + row * tileHeight;

            switch (c) {
                case '#':
                    entities.push_back(std::make_unique<Wall>(x, y));
                break;
                case '0':
                    entities.push_back(std::make_unique<Coin>(x, y));
                break;
                default:
                    break;
            }
        }
    }

    return true;
}

void World::printMap() const {
    for (const auto& row : mapData)
        std::cout << row << "\n";
    std::cout << "Map size: " << width << "x" << height << std::endl;
}

void World::update(float deltaTime) {
    for (auto& e : entities) {
        e->update(deltaTime);
    }
}

const std::vector<std::unique_ptr<Entity>>& World::getEntities() const {
    return entities;
};
int World::getWidth() const {
    return width;
};
int World::getHeight() const {
    return height;
};