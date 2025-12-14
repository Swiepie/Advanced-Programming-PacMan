//
// Created by siebe on 13/12/2025.
//

#ifndef WALLVIEW_H
#define WALLVIEW_H

#include <SFML/Graphics.hpp>
#include "../logic/Stopwatch.h"
#include <iostream>
#include <utility>
#include "EntityView.h"
#include "../logic/entities/Wall.h"
#include "Camera.h"

class WallView : public EntityView {
private:
	Wall* wall;
	public:
	explicit WallView(Wall *w, std::shared_ptr<sf::RenderWindow> window, float height, float width)
		: EntityView(w, std::move(window), height, width), wall(w) {
	}

	void update(float time) override;
	void render() override;
	void updateTexture(float time) override;
};



#endif //WALLVIEW_H
