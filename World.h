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
#include "entities/Ghost.h"
class Ghost;
class World {
private:
    std::vector<coord> ghostSpawnPositions;
    float totTime = 0;
    float deltaT = 0.0f;
    float fearmodeTimer = 6;
    float fearmodeStart = 0;
    float deathTime = 0;
    float respawnTimer = 1;
    bool death = false;
    int fps = 60;
    bool pacmanIsAlive = true;
    bool fearmode = false;

    std::vector<std::unique_ptr<Entity>> entities;
    Pacman* pacman = nullptr;
    float tileSize = 32.0f;
    std::vector<std::string> mapData;

    int width = 0;
    int height = 0;

    int coinCount = 0;
    int score = 0;

    int pacmanlives = 3;


    float bfr = deltaT;
public:

    bool loadMap(const std::string& filename);
    void printMap() const; //debug
    void update(float deltaTime);

    void setFearMode(bool fearmode);
    bool getFearMode();
    void increaseScore(int points);
    float getFearModeTimer() const;
    void setFearModeTimer(float timer);
    const std::vector<std::unique_ptr<Entity>>& getEntities() const;
    int getWidth() const;
    int getHeight() const;

    bool tryMove(Pacman* pacman, char dir) const;
    Pacman* getPacman() const;
    void checkCollisions();

    void setFearModeStart(float timer);
    bool tryMoveGhost(Ghost* ghost, char dir) const;
    bool canMoveInDirection(const Ghost* ghost, char dir) const;
    bool isAtIntersection(const Ghost* ghost) const;
    bool isAtDeadEnd(const Ghost* ghost) const;

    int getPacmanLives() const;

    int getScore() const;
    bool isOnTileCenter(const Entity* e) const;


    float getTime() const;

    void decreaseCoins();
    void resetAfterDeath();
};



#endif //WORLD_H
