//
// Created by siebe on 12/12/2025.
//

#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include "../logic/Observer.h"
#include "../logic/entities/Entity.h"
#include <SFML/Graphics.hpp>

class EntityView : public Observer {
protected:
  Entity *entity; // Raw pointer to the entity we're observing
  sf::Sprite sprite;
  sf::Texture texture;
  float lastFrameTime = 0.0f;
  float frameCooldown = 0.1f;
  bool mouthOpen = false;
  std::shared_ptr<sf::RenderWindow> window;
  float height = 0;
  float width = 0;

public:
  EntityView(Entity *e, std::shared_ptr<sf::RenderWindow> w, float h, float wd)
      : entity(e), window(std::move(w)), height(h), width(wd) {}

  virtual ~EntityView() = default;

  // Observer interface
  void update() override {
    // Base implementation - subclasses can override
  }
  void onNotify() { update(); }
  // Common functionality
  virtual void updateTexture(float time) = 0;

  sf::Sprite getSprite() { return sprite; }
  Entity *getEntity() const { return entity; }
  virtual void render() {};

protected:
  bool readyFrame(float currentTime) const {
    return (currentTime - lastFrameTime) >= frameCooldown;
  }

  void recordFrameTime(float currentTime) { lastFrameTime = currentTime; }
};

#endif // ENTITYVIEW_H
