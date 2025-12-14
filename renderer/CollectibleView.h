//
// Created by siebe on 13/12/2025.
//

#ifndef COLLECTIBLEVIEW_H
#define COLLECTIBLEVIEW_H


#include <SFML/Graphics.hpp>
#include "../logic/Stopwatch.h"
#include <iostream>
#include <utility>
#include "EntityView.h"
#include "../logic/entities/Coin.h"
#include "../logic/entities/Fruit.h"
#include "Camera.h"
class FruitView : public EntityView {
private:
	Fruit* fruit;
public:
	explicit FruitView(Fruit *f, std::shared_ptr<sf::RenderWindow> window, float height, float width)
		: EntityView(f, std::move(window), height, width), fruit(f) {
	}

	void update(float time) override;
	void render() override;
	void updateTexture(float time) override;
};

class CoinView : public EntityView {
private:
	Coin* coin;
public:
	explicit CoinView(Coin *c , std::shared_ptr<sf::RenderWindow> window, float height, float width)
		: EntityView(c, std::move(window), height, width), coin(c) {
	}

	void update(float time) override;
	void render() override;
	void updateTexture(float time) override;
};

#endif //COLLECTIBLEVIEW_H
