//
// Created by Siebe Haché on 14/10/2025.
//

#include "World.h"
#include <cmath>
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
                case 'P':{
                    auto p = std::make_unique<Pacman>(x, y);
                    pacman = p.get();
                    entities.push_back(std::move(p));
                    break;
                }
                case 'F':
                    entities.push_back(std::make_unique<Fruit>(x, y));
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

    if (!pacman) return;

    pacman->addMoveTime(deltaTime); // nieuwe functie in Pacman
    double speed = pacman->getSpeed();
    if (pacman->readyToMove()) {
        char buffered = pacman->getBufferdirection();
        bool moved = false;
        if (tryMove(pacman, buffered)) {
            pacman->applyBufferdirection();  // maak buffered -> current
            moved = true;
        } else {
            // probeer huidige richting
            char current = pacman->getDirection();
            if (tryMove(pacman, current)) {
                moved = true;
            }
        }

        if (moved)
            pacman->resetMoveTimer();

    }
}

const std::vector<std::unique_ptr<Entity>>& World::getEntities() const {
    return entities;
}
int World::getWidth() const {
    return width;
}
int World::getHeight() const {
    return height;
}
Pacman* World::getPacman(){
    return pacman;
}

bool World::tryMove(Pacman* pacman, char dir) {
    if (!pacman) return false;

    float dx = 0, dy = 0;
    double speed = pacman->getSpeed();
    switch (dir) {
        case 'N': dy = -0.1; break;
        case 'Z': dy = 0.1;  break;
        case 'W': dx = -0.1; break;
        case 'O': dx = 0.1;  break;
        default: return false;
    }

    float stepW = 2.0f / width;
    float stepH = 2.0f / height;
    float newX = pacman->getPosition().x + dx * stepW;
    float newY = pacman->getPosition().y + dy * stepH;

    for (auto& wall : entities) {
        if (wall->getSymbol() == '#') {
            float wallX = wall->getPosition().x;
            float wallY = wall->getPosition().y;

            // AABB overlap check (center-based coordinates)
            bool overlapX = std::fabs(newX - wallX)+0.0051 < stepW;
            bool overlapY = std::fabs(newY - wallY)+0.0051 < stepH;
            if (overlapX && overlapY)
                return false; // geblokkeerd
        }
    }
    pacman->setPosition(newX, newY);
    return true;
}