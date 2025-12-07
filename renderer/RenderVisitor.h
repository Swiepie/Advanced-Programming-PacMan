//
// Created by siebe on 07/12/2025.
//

#ifndef RENDERVISITOR_H
#define RENDERVISITOR_H

#include "../Visitor.h"
#include "GhostView.h"
#include "PacmanView.h"

class RenderVisitor : public Visitor {
private:
	sf::RenderWindow& window;
	sf::Sprite& redSprite;
	sf::Sprite& blueSprite;
	sf::Sprite& pinkSprite;
	sf::Sprite& fearSprite;
	sf::Sprite& pacmanSprite;
	float rectSize;
	float windowWidth, windowHeight;
	bool heightFlag;
	float h, w;

public:
	RenderVisitor (sf::RenderWindow& win, sf::Sprite& red, sf::Sprite& blue,
					   sf::Sprite& pink, sf::Sprite& fear, sf::Sprite& pacman,float size,
					   float winW, float winH, bool hFlag, float height, float width)
		: window(win), redSprite(red), blueSprite(blue), pinkSprite(pink), pacmanSprite(pacman),
		  fearSprite(fear), rectSize(size), windowWidth(winW), windowHeight(winH),
		  heightFlag(hFlag), h(height), w(width) {}

	void visit(Wall& wall) override;
	void visit(Coin& coin) override;
	void visit(Fruit& fruit) override;
	void visit(Pacman& pacman) override;
	void visit(RedGhost& ghost) override;
	void visit(BlueGhost& ghost) override;
	void visit(PinkGhost& ghost) override;

private:
	sf::Vector2f normalizeToScreen(float x, float y, float screenWidth, float screenHeight, bool flag, float h, float w);
	void renderGhost(Ghost& ghost, sf::Sprite& sprite);

};

class TextureVisitor : public Visitor {
private:
	RedGhostView& redView;
	BlueGhostView& blueView;
	PinkGhostView& pinkView;
	PacmanView& pacmanView;
	float time;

public:
	TextureVisitor(RedGhostView& red, BlueGhostView& blue, PinkGhostView& pink, PacmanView& pacman ,float t)
		: redView(red), blueView(blue), pinkView(pink), pacmanView(pacman),time(t) {}

	void visit(RedGhost& ghost) override;
	void visit(BlueGhost& ghost) override;
	void visit(PinkGhost& ghost) override;

	void visit(Wall& wall) override;
	void visit(Coin& coin) override;
	void visit(Fruit& fruit) override;
	void visit(Pacman& pacman) override;

};



#endif //RENDERVISITOR_H
