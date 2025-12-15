//
// Created by Siebe Haché on 14/10/2025.
//

#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <string>
#include <vector>

#include <fstream>
#include <iostream>

#include "Score.h"
#include "Visitor.h"
#include "entities/Coin.h"
#include "entities/Entity.h"
#include "entities/EntityFactory.h"
#include "entities/Fruit.h"
#include "entities/Ghost.h"
#include "entities/Pacman.h"
#include "entities/Wall.h"
class Ghost;
class EntityFactory;
class World {
private:
    int width = 0;
    int height = 0;
    std::vector<std::string> mapData;
    std::vector<coord> ghostSpawnPositions;
    // Separate vectors for different entity types
    std::vector<std::unique_ptr<Wall>> walls;
    std::vector<std::unique_ptr<Entity>> collectibles; // Coins + Fruits
    std::vector<std::unique_ptr<Ghost>> ghosts;

    std::shared_ptr<Pacman> pacman;

    int coinCount = 0;
    int pacmanlives = 3;

    // Time variables
    float totTime = 0.0f;
    float deltaT = 0.0f;

    // Death/Respawn states
    bool dies = false;
    float diesTime = 0.0f;
    float respawnTimer = 1.3f;
    bool death = false;
    float deathTime = 0.0f;
    bool reset = false;

    // Score
    int rounds = 0;
    Score score;

    float stepW = 2.0f / static_cast<float>(width);
    float stepH = 2.0f / static_cast<float>(height);

    // Fear mode
    bool fearmode = false;
    float fearmodeTimer = 6.0f;
    float fearmodeStart = 0.0f;

    // FACTORY POINTER
    std::shared_ptr<EntityFactory> factory;

public:
    explicit World(std::shared_ptr<EntityFactory> entityFactory) : factory(std::move(entityFactory)) {}

    bool loadMap(const std::string& filename);
    void printMap() const; // debug
    void update(float deltaTime);

    void setFearMode(bool fearmode);
    bool getFearMode() const;
    float getFearModeTimer() const;
    const std::vector<std::unique_ptr<Entity>>& getEntities() const;
    int getWidth() const;
    int getHeight() const;

    bool tryMove(const std::shared_ptr<Pacman>& pacman, char dir) const;
    const std::vector<std::unique_ptr<Wall>>& getWalls() const;
    const std::vector<std::unique_ptr<Entity>>& getCollectibles() const;
    const std::vector<std::unique_ptr<Ghost>>& getGhosts() const;
    std::shared_ptr<Pacman> getPacman() const;
    void checkCollisions();

    void setFearModeStart(float timer);
    bool tryMoveGhost(Ghost* ghost, char dir) const;
    bool canMoveInDirection(const Ghost* ghost, char dir) const;
    bool isAtIntersection(const Ghost* ghost) const;
    bool willCrossTileCenter(const Ghost* ghost, char dir) const;
    int getPacmanLives() const;

    int getScore() const;
    bool isOnTileCenter(const Entity* e) const;

    float getTime() const;

    void decreaseCoins();
    void resetAfterDeath();

    int getCoinCount() const;

    void resetWorld();
    Score& getScore();

    int getDeath();

    int getRounds() const;
};

#endif // WORLD_H
