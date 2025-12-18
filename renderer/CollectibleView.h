//
// Created by siebe on 13/12/2025.
//

#ifndef COLLECTIBLEVIEW_H
#define COLLECTIBLEVIEW_H

#include "../logic/Stopwatch.h"
#include "../logic/entities/Coin.h"
#include "../logic/entities/Fruit.h"
#include "Camera.h"
#include "EntityView.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
class FruitView : public EntityView {
private:
    Fruit* fruit;

public:
    explicit FruitView(Fruit* f, std::shared_ptr<sf::RenderWindow> window)
        : EntityView(f, std::move(window)), fruit(f) {}

    void update(float time) override;
    void render() override;
    void updateTexture(float time) override;
};

class CoinView : public EntityView {
private:
    Coin* coin;

public:
    explicit CoinView(Coin* c, std::shared_ptr<sf::RenderWindow> window)
        : EntityView(c, std::move(window)), coin(c) {}

    void update(float time) override;
    void render() override;
    void updateTexture(float time) override;
};

#endif // COLLECTIBLEVIEW_H
