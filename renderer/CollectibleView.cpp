//
// Created by siebe on 13/12/2025.
//

#include "CollectibleView.h"

void FruitView::update(float time) { render(); }

void FruitView::render() {
  Camera camera;
  float windowWidth = static_cast<float>(window->getSize().x);
  float windowHeight = static_cast<float>(window->getSize().y);

  float rectSize = std::min(windowWidth / width, windowHeight / height);

  float w, h;
  bool heightFlag;

  if (width / height <= windowWidth / windowHeight) {
    h = windowHeight;
    w = width * windowHeight / height;
    heightFlag = false;
  } else {
    h = (height / width) * windowWidth;
    w = windowWidth;
    heightFlag = true;
  }
  auto pos = fruit->getPosition();
  auto screenPos = camera.normalizeToScreen(pos.x, pos.y, windowWidth,
                                            windowHeight, heightFlag, h, w);

  sf::CircleShape circle(rectSize / 7.f);
  circle.setFillColor(sf::Color::Magenta);

  circle.setPosition(screenPos.x + rectSize / 2.f - rectSize / 7.f,
                     screenPos.y + rectSize / 2.f - rectSize / 7.f);

  window->draw(circle);
}

void FruitView::updateTexture(float time) {}

void CoinView::update(float time) { render(); }

void CoinView::render() {
  Camera camera;
  float windowWidth = static_cast<float>(window->getSize().x);
  float windowHeight = static_cast<float>(window->getSize().y);

  float rectSize = std::min(windowWidth / width, windowHeight / height);

  float w, h;
  bool heightFlag;

  if (width / height <= windowWidth / windowHeight) {
    h = windowHeight;
    w = width * windowHeight / height;
    heightFlag = false;
  } else {
    h = (height / width) * windowWidth;
    w = windowWidth;
    heightFlag = true;
  }
  auto pos = coin->getPosition();
  auto screenPos = camera.normalizeToScreen(pos.x, pos.y, windowWidth,
                                            windowHeight, heightFlag, h, w);

  sf::CircleShape circle(rectSize / 10.f);
  circle.setFillColor(sf::Color::Yellow);

  circle.setPosition(screenPos.x + rectSize / 2.f - rectSize / 10.f,
                     screenPos.y + rectSize / 2.f - rectSize / 10.f);
  window->draw(circle);
}

void CoinView::updateTexture(float time) {}
