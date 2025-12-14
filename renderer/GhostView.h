//
// Created by siebe on 09/11/2025.
//

#ifndef GHOSTVIEW_H
#define GHOSTVIEW_H

#include "../logic/Stopwatch.h"
#include "../logic/entities/Ghost.h"
#include "Camera.h"
#include "EntityView.h"
#include <SFML/Graphics.hpp>
#include <iostream>
class GhostView : public EntityView {
protected:
  Ghost *ghost;

public:
  explicit GhostView(Ghost *g, std::shared_ptr<sf::RenderWindow> window,
                     int height, int width);

  void render() override;
  void update(float time) override;
  void updateTexture(float time) override;
  virtual void chooseTexture(char direction, float time);
  void chooseFearTexture(float time);
};

class RedGhostView : public GhostView {
public:
  explicit RedGhostView(RedGhost *g, std::shared_ptr<sf::RenderWindow> window,
                        int height, int width);
  void chooseTexture(char direction, float time) override;
};

class BlueGhostView : public GhostView {
public:
  explicit BlueGhostView(BlueGhost *g, std::shared_ptr<sf::RenderWindow> window,
                         int height, int width);
  void chooseTexture(char direction, float time) override;
};

class PinkGhostView : public GhostView {
public:
  explicit PinkGhostView(PinkGhost *g, std::shared_ptr<sf::RenderWindow> window,
                         int height, int width);
  void chooseTexture(char direction, float time) override;
};

#endif // GHOSTVIEW_H
