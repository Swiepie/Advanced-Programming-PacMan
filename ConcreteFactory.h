//
// Created by siebe on 14/12/2025.
//

#ifndef CONCRETEFACTORY_H
#define CONCRETEFACTORY_H

#include "logic/entities/EntityFactory.h"

#include "logic/Observer.h"
#include "renderer/CollectibleView.h"
#include "renderer/GhostView.h"
#include "renderer/PacmanView.h"
#include "renderer/WallView.h"

class ConcreteFactory : public EntityFactory {
private:
    std::vector<std::unique_ptr<EntityView>> views;

    std::shared_ptr<sf::RenderWindow> window;


public:
    ~ConcreteFactory() override;
    ConcreteFactory(std::shared_ptr<sf::RenderWindow> window);
    std::unique_ptr<Wall> createWall(float x, float y) override;
    std::unique_ptr<Coin> createCoin(float x, float y) override;
    std::unique_ptr<Fruit> createFruit(float x, float y) override;
    std::unique_ptr<Pacman> createPacman(float x, float y) override;
    std::unique_ptr<RedGhost> createRedGhost(float x, float y) override;
    std::unique_ptr<BlueGhost> createBlueGhost(float x, float y, float delay) override;
    std::unique_ptr<PinkGhost> createPinkGhost(float x, float y, float delay) override;
};

#endif // CONCRETEFACTORY_H
