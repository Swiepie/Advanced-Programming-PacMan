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
    int i = 1;
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
                    coinCount = coinCount + 1;
                break;
                case 'P':{
                    auto p = std::make_unique<Pacman>(x, y);
                    pacman = p.get();
                    entities.push_back(std::move(p));
                    break;
                }
                case 'f':
                    std::cout << "fruitje" << std::endl;
                    entities.push_back(std::make_unique<Fruit>(x, y));
                break;
                case 'G':{
                    if (i == 1) {
                        entities.push_back(std::make_unique<RedGhost>(x, y)); // start meteen
                        i = i+1;
                        break;
                    }
                    if (i==2) {
                        entities.push_back(std::make_unique<BlueGhost>(x, y, 0.0f)); // start meteen
                        i = i+1;
                        break;
                    }
                    if (i==3) {
                        entities.push_back(std::make_unique<BlueGhost>(x, y, 5.0f)); // start na 5s
                        i = i+1;
                        break;
                    }
                    if (i==4) {
                        entities.push_back(std::make_unique<PinkGhost>(x, y, 10.0f)); // start na 10s
                        std::cout << "gay" << std::endl;
                        break;
                    }

                    break;

                }
                default:
                    break;
            }
        }
    }
    for (auto& e : entities) {
        //std::cout << e->getPosition().x << "      " << e->getPosition().y << std::endl;
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
        e->update(deltaTime, *this, *pacman);
    }

    pacman->addMoveTime(deltaTime);

    //is het al tijd om opnieuw te bewegen?
    if (pacman->readyToMove(deltaTime)) {
        char buffered = pacman->getBufferdirection();
        bool moved = false;

        if (tryMove(pacman, buffered)) {
            pacman->applyBufferdirection();
            moved = true;
        } else {
            char current = pacman->getDirection();
            if (tryMove(pacman, current)) {
                moved = true;
            }
        }

        if (moved) {
            //slaag de tijd op van laatste movement
            checkCollisions();
            pacman->recordMoveTime(deltaTime);
        }
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
Pacman* World::getPacman() const{
    return pacman;
}

bool World::tryMove(Pacman* pacman, char dir) const {
    if (!pacman) return false;
    float speed = pacman->getSpeed();
    float dx = 0, dy = 0;
    switch (dir) {
        case 'N': dy = -0.1*speed; break;
        case 'Z': dy = 0.1*speed;  break;
        case 'W': dx = -0.1*speed; break;
        case 'O': dx = 0.1*speed;  break;
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
            bool overlapX = std::fabs(newX - wallX) + 0.0051 < stepW;
            bool overlapY = std::fabs(newY - wallY) + 0.0051 < stepH;
            if (overlapX && overlapY)
                return false; // geblokkeerd
        }
    }
    pacman->setPosition(newX, newY);
    return true;
}

void World::checkCollisions() {
    //std::cout<< "Entities collided: " << std::endl;
    if (!pacman) return;
    entities.erase(
        std::remove_if(entities.begin(), entities.end(),
            [&](const std::unique_ptr<Entity>& e) {
                if (e->isCollectible() && pacman->collidesWith(*e, 2.0f / width * 0.5f, 2.0f / height * 0.5f)) {
                    e->onCollect(*pacman);
                    return true; // verwijderen
                }
                return false;
            }),
        entities.end()
    );
}

bool World::tryMoveGhost(Ghost* ghost, char dir) const {
    if (!ghost) return false;
    float speed = ghost->getSpeed();
    float dx = 0, dy = 0;
    switch (dir) {
        case 'N': dy = -0.1 * speed; break;
        case 'Z': dy =  0.1 * speed; break;
        case 'W': dx = -0.1 * speed; break;
        case 'O': dx =  0.1 * speed; break;
        default: return false;
    }

    float stepW = 2.0f / width;
    float stepH = 2.0f / height;
    float newX = ghost->getPosition().x + dx * stepW;
    float newY = ghost->getPosition().y + dy * stepH;

    // Botsing met muren
    for (auto& wall : entities) {
        if (wall->getSymbol() == '#') {
            float wallX = wall->getPosition().x;
            float wallY = wall->getPosition().y;
            bool overlapX = std::fabs(newX - wallX) + 0.0051 < stepW;
            bool overlapY = std::fabs(newY - wallY) + 0.0051 < stepH;
            if (overlapX && overlapY)
                return false;
        }
    }
    ghost->setPosition(newX, newY);
    return true;
}

bool World::canMoveInDirection(const Ghost* ghost, char dir) const {
    if (!ghost) return false;
    float stepW = 2.0f / width;
    float stepH = 2.0f / height;

    // Use actual ghost speed for checking
    float speed = ghost->getSpeed();
    float dx = 0, dy = 0;
    switch (dir) {
        case 'N': dy = -0.1 * speed * stepH; break;
        case 'Z': dy =  0.1 * speed * stepH; break;
        case 'W': dx = -0.1 * speed * stepW; break;
        case 'O': dx =  0.1 * speed * stepW; break;
        default: return false;
    }

    float newX = ghost->getPosition().x + dx;
    float newY = ghost->getPosition().y + dy;

    for (auto& wall : entities) {
        if (wall->getSymbol() == '#') {
            float wallX = wall->getPosition().x;
            float wallY = wall->getPosition().y;
            bool overlapX = std::fabs(newX - wallX) + 0.0051 < stepW;
            bool overlapY = std::fabs(newY - wallY) + 0.0051 < stepH;
            if (overlapX && overlapY)
                return false;
        }
    }
    return true;
}

bool World::isAtIntersection(const Ghost* ghost) const {
    if (!ghost) return false;

    char currentDir = ghost->getDirection();
    int viableMoves = 0;
    int perpendicularMoves = 0;

    for (char d : {'N', 'Z', 'W', 'O'}) {
        if (canMoveInDirection(ghost, d)) {
            viableMoves++;

            // Check if this is perpendicular to current direction
            bool perpendicular = false;
            if ((currentDir == 'N' || currentDir == 'Z') && (d == 'W' || d == 'O')) {
                perpendicular = true;
            } else if ((currentDir == 'W' || currentDir == 'O') && (d == 'N' || d == 'Z')) {
                perpendicular = true;
            }

            if (perpendicular) {
                perpendicularMoves++;
            }
        }
    }

    // Intersection if:
    // - More than 2 viable moves (T-junction or crossroads), OR
    // - Exactly 2 viable moves with at least one perpendicular option (corner)
    return (viableMoves > 2) || (viableMoves >= 2 && perpendicularMoves > 0);
}