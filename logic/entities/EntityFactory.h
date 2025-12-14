//
// Created by siebe on 04/12/2025.
//

#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "Coin.h"
#include "Entity.h"
#include "Ghost.h"
#include "Pacman.h"
#include "Wall.h"

#include <unordered_map>
class Wall;
class Coin;
class Fruit;
class RedGhost;
class BlueGhost;
class PinkGhost;
class PacMan;

class EntityFactory {
public:
  virtual ~EntityFactory() = default;
  virtual std::unique_ptr<Wall> createWall(float x, float y) = 0;
  virtual std::unique_ptr<Coin> createCoin(float x, float y) = 0;
  virtual std::unique_ptr<Fruit> createFruit(float x, float y) = 0;
  virtual std::unique_ptr<Pacman> createPacman(float x, float y) = 0;
  virtual std::unique_ptr<RedGhost> createRedGhost(float x, float y) = 0;
  virtual std::unique_ptr<BlueGhost> createBlueGhost(float x, float y,
                                                     float delay) = 0;
  virtual std::unique_ptr<PinkGhost> createPinkGhost(float x, float y,
                                                     float delay) = 0;
};

#endif // ENTITYFACTORY_H
