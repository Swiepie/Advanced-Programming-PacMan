//
// Created by siebe on 09/11/2025.
//

#ifndef GHOSTVIEW_H
#define GHOSTVIEW_H


#include <SFML/Graphics.hpp>
#include "..//Stopwatch.h"
#include <iostream>
#include "EntityView.h"
#include "../entities/Ghost.h"

class GhostView : public EntityView {
public:
	explicit GhostView(Ghost* ghost);

	void update() override;
	void updateTexture(float time) override;
	virtual void chooseTexture(char direction, float time);
};

class RedGhostView : public GhostView {
public:
	explicit RedGhostView(Ghost* ghost);
	void chooseTexture(char direction, float time) override;
};

class BlueGhostView : public GhostView {
public:
	explicit BlueGhostView(Ghost* ghost);
	void chooseTexture(char direction, float time) override;
};

class PinkGhostView : public GhostView {
public:
	explicit PinkGhostView(Ghost* ghost);
	void chooseTexture(char direction, float time) override;
};
class FearGhostView : public GhostView {
	public:
	FearGhostView();
	void chooseTexture(float time);
};
#endif //GHOSTVIEW_H
