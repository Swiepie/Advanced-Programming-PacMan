
#include "GhostView.h"
#include <iostream>

GhostView::GhostView(Ghost* ghost) : EntityView(ghost) {
    if (!texture.loadFromFile("../sprites/pacman.png")) {
        std::cerr << "Failed to load ghost spritesheet" << std::endl;
    }
    sprite.setTexture(texture);
}

void GhostView::update() {
    // Called when ghost position changes
}

void GhostView::updateTexture(float time) {
    Ghost* ghost = static_cast<Ghost*>(entity);
    chooseTexture(ghost->getDirection(), time);
}

void GhostView::chooseTexture(char direction, float time) {
    // Base implementation
}

// RedGhostView
RedGhostView::RedGhostView(Ghost* ghost) : GhostView(ghost) {
    sprite.setTextureRect(sf::IntRect(64, 64, 16, 16));
}

void RedGhostView::chooseTexture(char direction, float time) {
    if (readyFrame(time)) {
        mouthOpen = !mouthOpen;
        sf::IntRect rect;
        switch (direction) {
            case 'N': rect = mouthOpen ? sf::IntRect(64, 64, 16, 16)
                                       : sf::IntRect(80, 64, 16, 16);
                break;
            case 'Z': rect = mouthOpen ? sf::IntRect(96, 64, 16, 16)
                                       : sf::IntRect(112, 64, 16, 16);
                break;
            case 'W': rect = mouthOpen ? sf::IntRect(32, 64, 16, 16)
                                       : sf::IntRect(48, 64, 16, 16);
                break;
            case 'O': rect = mouthOpen ? sf::IntRect(0, 64, 16, 16)
                                       : sf::IntRect(16, 64, 16, 16);
                break;
        }
        sprite.setTextureRect(rect);
        recordFrameTime(time);
    }
}

// BlueGhostView
BlueGhostView::BlueGhostView(Ghost* ghost) : GhostView(ghost) {
    sprite.setTextureRect(sf::IntRect(64, 96, 16, 16));
}

void BlueGhostView::chooseTexture(char direction, float time) {
    if (readyFrame(time)) {
        mouthOpen = !mouthOpen;
        sf::IntRect rect;
        switch (direction) {
            case 'N': rect = mouthOpen ? sf::IntRect(64, 96, 16, 16)
                                       : sf::IntRect(80, 96, 16, 16);
                break;
            case 'Z': rect = mouthOpen ? sf::IntRect(96, 96, 16, 16)
                                       : sf::IntRect(112, 96, 16, 16);
                break;
            case 'W': rect = mouthOpen ? sf::IntRect(32, 96, 16, 16)
                                       : sf::IntRect(48, 96, 16, 16);
                break;
            case 'O': rect = mouthOpen ? sf::IntRect(0, 96, 16, 16)
                                       : sf::IntRect(16, 96, 16, 16);
                break;
        }
        sprite.setTextureRect(rect);
        recordFrameTime(time);
    }
}

// PinkGhostView
PinkGhostView::PinkGhostView(Ghost* ghost) : GhostView(ghost) {
    sprite.setTextureRect(sf::IntRect(64, 80, 16, 16));
}

void PinkGhostView::chooseTexture(char direction, float time) {
    if (readyFrame(time)) {
        mouthOpen = !mouthOpen;
        sf::IntRect rect;
        switch (direction) {
            case 'N': rect = mouthOpen ? sf::IntRect(64, 80, 16, 16)
                                       : sf::IntRect(80, 80, 16, 16);
                break;
            case 'Z': rect = mouthOpen ? sf::IntRect(96, 80, 16, 16)
                                       : sf::IntRect(112, 80, 16, 16);
                break;
            case 'W': rect = mouthOpen ? sf::IntRect(32, 80, 16, 16)
                                       : sf::IntRect(48, 80, 16, 16);
                break;
            case 'O': rect = mouthOpen ? sf::IntRect(0, 80, 16, 16)
                                       : sf::IntRect(16, 80, 16, 16);
                break;
        }
        sprite.setTextureRect(rect);
        recordFrameTime(time);
    }
}