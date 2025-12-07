//
// Created by siebe on 07/12/2025.
//

#include "RenderVisitor.h"

sf::Vector2f RenderVisitor::normalizeToScreen(float x, float y, float screenWidth, float screenHeight, bool flag, float h, float w) {
	float whitespaceH = (screenHeight-h) / 2;
	float whitespaceW = (screenWidth-w) / 2;

	if(!flag) {
		float px = (x + 1.0f) * 0.5f * w + whitespaceW;
		float py = ((y + 1.0f) * 0.5f * h);
		return {px, py};
	} else {
		float px = ((x + 1.0f) * 0.5f * w) ;
		float py = (y + 1.0f) * 0.5f * h + whitespaceH;
		return {px, py};
	}
}

void RenderVisitor::renderGhost(Ghost& ghost, sf::Sprite& sprite) {
	auto pos = ghost.getPosition();
	auto screenPos = normalizeToScreen(pos.x, pos.y, windowWidth, windowHeight, heightFlag, h, w);
	sprite.setPosition(screenPos);
	sprite.setScale(rectSize/16, rectSize/16);
	window.draw(sprite);
}
void RenderVisitor::visit(RedGhost& ghost){
	renderGhost(ghost, ghost.getFearState() ? fearSprite : redSprite);
}
void RenderVisitor::visit(BlueGhost& ghost){
	renderGhost(ghost, ghost.getFearState() ? fearSprite : blueSprite);
}
void RenderVisitor::visit(PinkGhost& ghost){
	renderGhost(ghost, ghost.getFearState() ? fearSprite : pinkSprite);
}
void RenderVisitor::visit(Wall& wall) {
	auto pos = wall.getPosition();
	auto screenPos = normalizeToScreen(pos.x, pos.y, windowWidth, windowHeight, heightFlag, h, w);
	sf::RectangleShape rect({rectSize, rectSize});
	rect.setFillColor(sf::Color::Blue);
	rect.setPosition(screenPos);
	window.draw(rect);
}
void RenderVisitor::visit(Coin& coin) {
	auto pos = coin.getPosition();
	auto screenPos = normalizeToScreen(pos.x, pos.y, windowWidth, windowHeight, heightFlag, h, w);
	sf::CircleShape circle(rectSize / 10.f);
	circle.setFillColor(sf::Color::Yellow);
	circle.setPosition(screenPos.x + rectSize/2 - rectSize/10, screenPos.y + rectSize/2 - rectSize/10);
	window.draw(circle);
}
void RenderVisitor::visit(Fruit& fruit) {
	auto pos = fruit.getPosition();
	auto screenPos = normalizeToScreen(pos.x, pos.y, windowWidth, windowHeight, heightFlag, h, w);

	sf::CircleShape circle(rectSize / 10.f);
	circle.setFillColor(sf::Color::Magenta);
	circle.setPosition(screenPos.x + rectSize/2 - rectSize/10, screenPos.y + rectSize/2 - rectSize/10);
	window.draw(circle);
}
void RenderVisitor::visit(Pacman& pacman) {
	auto pos = pacman.getPosition();
	auto screenPos = normalizeToScreen(pos.x, pos.y, windowWidth, windowHeight, heightFlag, h, w);

	pacmanSprite.setPosition(screenPos);
	pacmanSprite.setScale(rectSize/15, rectSize/15);
	window.draw(pacmanSprite);
}



void TextureVisitor::visit(RedGhost& ghost)  {
	redView.chooseTexture(ghost.getDirection(), time);
}
void TextureVisitor::visit(BlueGhost& ghost)  {
	blueView.chooseTexture(ghost.getDirection(), time);
}
void TextureVisitor::visit(PinkGhost& ghost)  {
	pinkView.chooseTexture(ghost.getDirection(), time);
}
void TextureVisitor::visit(Wall& wall) {
    // doesnt exist
}
void TextureVisitor::visit(Coin& coin) {
	// doesnt exist
}
void TextureVisitor::visit(Fruit& fruit) {
	// doesnt exist
}
void TextureVisitor::visit(Pacman& pacman) {
	pacmanView.chooseTexture(pacman.getDirection(), time);
}