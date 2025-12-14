//
// Created by siebe on 13/12/2025.
//

#ifndef WALLVIEW_H
#define WALLVIEW_H

#include "../logic/Stopwatch.h"
#include "../logic/entities/Wall.h"
#include "Camera.h"
#include "EntityView.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>

class WallView : public EntityView {
private:
  Wall *wall;

public:
  explicit WallView(Wall *w, std::shared_ptr<sf::RenderWindow> window,
                    float height, float width)
      : EntityView(w, std::move(window), height, width), wall(w) {}

  void update(float time) override;
  void render() override;
  void updateTexture(float time) override;
};

#endif // WALLVIEW_H
