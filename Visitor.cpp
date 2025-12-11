//
// Created by siebe on 04/12/2025.
//
#include "entities/Wall.h"
#include "entities/Coin.h"
#include "entities/Fruit.h"
#include "entities/Pacman.h"
#include "entities/Ghost.h"
#include "World.h"
#include "Visitor.h"

CollectibleVisitor::CollectibleVisitor(Pacman* p, World* w, float tileWidth, float tileHeight)
	: pacman(p), world(w), stepW(tileWidth), stepH(tileHeight) {}

void CollectibleVisitor::visit(Wall& wall) {
	// Walls are not collectible
}

void CollectibleVisitor::visit(Coin& coin) {
	if (pacman && pacman->collidesWith(coin, stepW * 0.5f, stepH * 0.5f)) {
		toRemove.push_back(&coin);
		coin.onCollect(*world);
	}
}

void CollectibleVisitor::visit(Fruit& fruit) {
	if (pacman && pacman->collidesWith(fruit, stepW * 0.5f, stepH * 0.5f)) {
		toRemove.push_back(&fruit);
		fruit.onCollect(*world);
	}
}

void CollectibleVisitor::visit(Pacman& p) {}

void CollectibleVisitor::visit(RedGhost& ghost) {}
void CollectibleVisitor::visit(BlueGhost& ghost) {}
void CollectibleVisitor::visit(PinkGhost& ghost) {}

const std::vector<Entity*>& CollectibleVisitor::getToRemove() const {
	return toRemove;
}


GhostCollisionVisitor::GhostCollisionVisitor(Pacman* p, World* w, float tileWidth, float tileHeight)
	: pacman(p), world(w), stepW(tileWidth), stepH(tileHeight),
	  pacmanDied(false), ghostEaten(false) {}

void GhostCollisionVisitor::visit(Wall& wall) {}
void GhostCollisionVisitor::visit(Coin& coin) {}
void GhostCollisionVisitor::visit(Fruit& fruit) {}
void GhostCollisionVisitor::visit(Pacman& p) {}

void GhostCollisionVisitor::visit(RedGhost& ghost) {
	handleGhostCollision(ghost);
}
void GhostCollisionVisitor::visit(BlueGhost& ghost) {
	handleGhostCollision(ghost);
}
void GhostCollisionVisitor::visit(PinkGhost& ghost) {
	handleGhostCollision(ghost);
}

void GhostCollisionVisitor::handleGhostCollision(Ghost& ghost) {
	if (!pacman || ghostEaten) return;

	if (pacman->collidesWith(ghost, stepW * 1.0f, stepH * 1.0f)) {
		if (world->getFearMode() && ghost.getFearState() && !ghost.getHasBeenEaten()) {
			ghost.resetToSpawn();
			ghost.resetFearState();
			ghost.setHasBeenEaten(true);
			world->getScore().addGhost(200);
			ghostEaten = true;
		} else if (!world->getFearMode() || ghost.getHasBeenEaten()) {
			pacmanDied = true;
		}
	}
}

bool GhostCollisionVisitor::didPacmanDie() const { return pacmanDied; }
bool GhostCollisionVisitor::wasGhostEaten() const { return ghostEaten; }


CollisionDetectionVisitor::CollisionDetectionVisitor(float x, float y, float tileWidth, float tileHeight)
	: checkX(x), checkY(y), stepW(tileWidth), stepH(tileHeight), collisionDetected(false) {}

void CollisionDetectionVisitor::visit(Wall& wall) {
	float wallX = wall.getPosition().x;
	float wallY = wall.getPosition().y;

	float distX = std::fabs(checkX - wallX);
	float distY = std::fabs(checkY - wallY);

	bool overlapX = distX < stepW * COLLISION_MARGIN;
	bool overlapY = distY < stepH * COLLISION_MARGIN;

	if (overlapX && overlapY) {
		collisionDetected = true;
	}
}

void CollisionDetectionVisitor::visit(Coin& coin) {}
void CollisionDetectionVisitor::visit(Fruit& fruit) {}
void CollisionDetectionVisitor::visit(Pacman& pacman) {}
void CollisionDetectionVisitor::visit(RedGhost& ghost) {}
void CollisionDetectionVisitor::visit(BlueGhost& ghost) {}
void CollisionDetectionVisitor::visit(PinkGhost& ghost) {}

bool CollisionDetectionVisitor::hasCollision() const { return collisionDetected; }

void DeathVisitor::visit(Wall& wall) {}
void DeathVisitor::visit(Coin& coin) {}
void DeathVisitor::visit(Fruit& fruit) {}
void DeathVisitor::visit(Pacman& pacman)  {
	pacman.resetToSpawn();
	pacman.setBufferdirection(' ');
	pacman.setDirection(' ');
}
void DeathVisitor::visit(RedGhost& ghost) {
	resetGhost(ghost);
}
void DeathVisitor::visit(BlueGhost& ghost) {
	resetGhost(ghost);
}
void DeathVisitor::visit(PinkGhost& ghost) {
	resetGhost(ghost);
}
void DeathVisitor::resetGhost(Ghost& ghost) {
	ghost.reset();
}