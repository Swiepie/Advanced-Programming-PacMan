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
#include "entities/EntityFactory.h"
#include "Score.h"
#include "Visitor.h"
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

	std::unique_ptr<Pacman> pacmanPtr;
    Pacman* pacman = nullptr;
    int coinCount = 0;
    int pacmanlives = 3;

    // Time variables
    float totTime = 0.0f;
    float deltaT = 0.0f;

    // Death/Respawn states
    bool dies = false;
    float diesTime = 0.0f;
    float respawnTimer = 0.9f;
    bool death = false;
    float deathTime = 0.0f;
    bool reset = false;

	// Score
    int rounds = 0;
    Score score;

    // Fear mode
    bool fearmode = false;
    float fearmodeTimer = 6.0f;
    float fearmodeStart = 0.0f;

    // FACTORY POINTER
    std::shared_ptr<EntityFactory> factory;
public:
    explicit World(std::shared_ptr<EntityFactory> entityFactory)
            : factory(std::move(entityFactory)) {}

    bool loadMap(const std::string& filename);
    void printMap() const; //debug
    void update(float deltaTime);

    void setFearMode(bool fearmode);
    bool getFearMode() const;
    float getFearModeTimer() const;
    const std::vector<std::unique_ptr<Entity>>& getEntities() const;
    int getWidth() const;
    int getHeight() const;

    bool tryMove(Pacman* pacman, char dir) const;
	const std::vector<std::unique_ptr<Wall>>& getWalls() const;
	const std::vector<std::unique_ptr<Entity>>& getCollectibles() const;
	const std::vector<std::unique_ptr<Ghost>>& getGhosts() const;
    Pacman* getPacman() const;
    void checkCollisions();

    void setFearModeStart(float timer);
    bool tryMoveGhost(Ghost* ghost, char dir) const;
    bool canMoveInDirection(const Ghost* ghost, char dir) const;
    bool isAtIntersection(const Ghost* ghost) const;

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

};



#endif //WORLD_H
