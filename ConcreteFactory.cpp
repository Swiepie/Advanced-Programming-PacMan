//
// Created by siebe on 14/12/2025.
//

#include "ConcreteFactory.h"
#include <memory>

#include "renderer/CollectibleView.h"

ConcreteFactory::~ConcreteFactory() {
    views.clear();


}
ConcreteFactory::ConcreteFactory(std::shared_ptr<sf::RenderWindow> window, int height, int width)
    : window(std::move(window)), height(height), width(width) {}

std::unique_ptr<Wall> ConcreteFactory::createWall(float x, float y) {
    auto wall = std::make_unique<Wall>(x, y);

    // Create view and attach it
    auto view = std::make_unique<WallView>(wall.get(), window, height, width);
    wall->attach(view.get());

    // Store view to keep it alive
    views.push_back(std::move(view));

    return wall;
}

std::unique_ptr<Coin> ConcreteFactory::createCoin(float x, float y) {
    auto coin = std::make_unique<Coin>(x, y);

    // Create view and attach it
    auto view = std::make_unique<CoinView>(coin.get(), window, height, width);
    coin->attach(view.get());

    // Store view to keep it alive
    views.push_back(std::move(view));

    return coin;
}

std::unique_ptr<Fruit> ConcreteFactory::createFruit(float x, float y) {
    auto fruit = std::make_unique<Fruit>(x, y);

    // Create view and attach it
    auto view = std::make_unique<FruitView>(fruit.get(), window, height, width);
    fruit->attach(view.get());

    // Store view to keep it alive
    views.push_back(std::move(view));

    return fruit;
}

std::unique_ptr<Pacman> ConcreteFactory::createPacman(float x, float y) {
    auto pacman = std::make_unique<Pacman>(x, y);

    // Create view and attach it
    auto view = std::make_unique<PacmanView>(pacman.get(), window, height, width);
    pacman->attach(view.get());

    // Store view to keep it alive
    views.push_back(std::move(view));

    return pacman;
}

std::unique_ptr<RedGhost> ConcreteFactory::createRedGhost(float x, float y) {
    auto ghost = std::make_unique<RedGhost>(x, y);

    auto view = std::make_unique<RedGhostView>(ghost.get(), window, height, width);
    ghost->attach(view.get());

    views.push_back(std::move(view));

    return ghost;
}

std::unique_ptr<BlueGhost> ConcreteFactory::createBlueGhost(float x, float y, float delay) {
    auto ghost = std::make_unique<BlueGhost>(x, y, delay);

    auto view = std::make_unique<BlueGhostView>(ghost.get(), window, height, width);
    ghost->attach(view.get());

    views.push_back(std::move(view));

    return ghost;
}

std::unique_ptr<PinkGhost> ConcreteFactory::createPinkGhost(float x, float y, float delay) {
    auto ghost = std::make_unique<PinkGhost>(x, y, delay);

    auto view = std::make_unique<PinkGhostView>(ghost.get(), window, height, width);
    ghost->attach(view.get());

    views.push_back(std::move(view));

    return ghost;
}