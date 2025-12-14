//
// Created by siebe on 04/12/2025.
//

#ifndef VISITOR_H
#define VISITOR_H

#include "entities/Entity.h"
class Wall;
class Coin;
class Fruit;
class Pacman;
class Ghost;
class RedGhost;
class BlueGhost;
class PinkGhost;
class World;
class Entity;
#include "World.h"
#include <vector>

class Visitor {
public:
	virtual ~Visitor() = default;

	virtual void visit(Wall& wall) = 0;
	virtual void visit(Coin& coin) = 0;
	virtual void visit(Fruit& fruit) = 0;
	virtual void visit(Pacman& pacman) = 0;
	virtual void visit(RedGhost& ghost) = 0;
	virtual void visit(BlueGhost& ghost) = 0;
	virtual void visit(PinkGhost& ghost) = 0;
};

class CollectibleVisitor : public Visitor {
private:
	std::shared_ptr<Pacman> pacman;
	World* world;
	float stepW, stepH;
	std::vector<Entity*> toRemove;

public:
	CollectibleVisitor(std::shared_ptr<Pacman> pacman, World* w, float tileWidth, float tileHeight);

	void visit(Wall& wall) override;
	void visit(Coin& coin) override;
	void visit(Fruit& fruit) override;
	void visit(Pacman& p) override;
	void visit(RedGhost& ghost) override;
	void visit(BlueGhost& ghost) override;
	void visit(PinkGhost& ghost) override;

	const std::vector<Entity*>& getToRemove() const;
};

class GhostCollisionVisitor : public Visitor {
private:
	std::shared_ptr<Pacman> pacman;
	World* world;
	float stepW, stepH;
	bool pacmanDied;
	bool ghostEaten;

	void handleGhostCollision(Ghost& ghost);

public:
	GhostCollisionVisitor(std::shared_ptr<Pacman> pacman, World* w, float tileWidth, float tileHeight);

	void visit(Wall& wall) override;
	void visit(Coin& coin) override;
	void visit(Fruit& fruit) override;
	void visit(Pacman& p) override;
	void visit(RedGhost& ghost) override;
	void visit(BlueGhost& ghost) override;
	void visit(PinkGhost& ghost) override;

	bool didPacmanDie() const;
	bool wasGhostEaten() const;
};

class CollisionDetectionVisitor : public Visitor {
private:
	float checkX, checkY;
	float stepW, stepH;
	bool collisionDetected;
	const float COLLISION_MARGIN = 0.97f;

public:
	CollisionDetectionVisitor(float x, float y, float tileWidth, float tileHeight);

	void visit(Wall& wall) override;
	void visit(Coin& coin) override;
	void visit(Fruit& fruit) override;
	void visit(Pacman& pacman) override;
	void visit(RedGhost& ghost) override;
	void visit(BlueGhost& ghost) override;
	void visit(PinkGhost& ghost) override;

	bool hasCollision() const;
};
class DeathVisitor : public Visitor {
private:
	World* world;
	float currentTime;

public:
	DeathVisitor(World* w, float curTime)
		: world(w), currentTime(curTime) {}

	void visit(Wall& wall) override;
	void visit(Coin& coin) override;
	void visit(Fruit& fruit) override;
	void visit(Pacman& pacman) override;
	void visit(RedGhost& ghost) override;
	void visit(BlueGhost& ghost) override;
	void visit(PinkGhost& ghost) override;

private:
	static auto resetGhost(Ghost &ghost) -> void;
};

#endif //VISITOR_H
