//
// Created by siebe on 09/11/2025.
//

#ifndef GHOSTVIEW_H
#define GHOSTVIEW_H


#include <SFML/Graphics.hpp>
#include "..//Stopwatch.h"
#include <iostream>

class GhostView {
protected:
	bool mouthOpen = true;
	double frameCooldown = 1.0/15;
	float frameTimer = 0.0f;
	double speed = 1;
	float lastFrameTime = 0.0f;

	sf::Texture pacmanTexture;
	sf::Sprite ghostSprite;
public:
	GhostView();

	void setTexture(const sf::Texture& texture);
	virtual void chooseTexture(char direction);
	bool readyFrame(float currentTime) const;
	void recordFrameTime(float currentTime);
	sf::Sprite getSprite();
};

class RedGhostView : public GhostView {
public:
	RedGhostView();
  	void chooseTexture(char direction) override;
};

class BlueGhostView : public GhostView {
public:
	BlueGhostView();
	void chooseTexture(char direction) override;
};

class PinkGhostView : public GhostView {
public:
	PinkGhostView();
	void chooseTexture(char direction) override;

};
#endif //GHOSTVIEW_H
