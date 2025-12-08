//
// Created by Siebe Haché on 15/10/2025.
//

#include "WorldView.h"
#include <iostream>
#include "../entities/Wall.h"
#include "../entities/Coin.h"

sf::View getWorldView(unsigned int windowWidth, unsigned int windowHeight) {
    sf::View view;
    view.setSize(windowWidth, windowHeight);

    view.setCenter(windowWidth / 2.f, windowHeight / 2.f);
    return view;
}
sf::Vector2f normalizeToScreen(float x, float y, float screenWidth, float screenHeight, bool flag, float h, float w) {
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


void WorldView::render(const World& world, sf::RenderWindow& window, float windowWidth, float windowHeight) {
    int currentRound = world.getRounds();
    int currentLives = world.getPacmanLives();

    // Clear cache if round changed OR if Pacman died (lives decreased)
    if (currentRound != round || currentLives != lastLives) {
        ghostViews.clear();
        round = currentRound;
        lastLives = currentLives;
        std::cout << "Cache cleared. Round: " << currentRound << ", Lives: " << currentLives << std::endl;
    }

    float time = world.getTime();
    Pacman* pacman = world.getPacman();

    // ✅ Create a unique view for EACH ghost (not one per color!)
    for (const auto& ghost : world.getGhosts()) {
        if (ghostViews.find(ghost.get()) == ghostViews.end()) {
            ViewCreatorVisitor creator;
            ghost->accept(creator);
            ghostViews[ghost.get()] = std::move(creator.view);

            std::cout << "Created new view for ghost at " << ghost.get() << std::endl;
        }
    }

    // Update Pacman texture
    pacmanview.chooseTexture(pacman->getDirection(), time);

    // Update fear ghost texture
    fearghostview.chooseTexture(time);

    // ✅ Update textures for each ghost using their individual view
    for (const auto& ghost : world.getGhosts()) {
        if (ghostViews.find(ghost.get()) != ghostViews.end()) {
            ghostViews[ghost.get()]->chooseTexture(ghost->getDirection(), time);
        }
    }

    sf::View view = getWorldView(windowWidth, windowHeight);
    window.setView(view);

    float worldw = world.getWidth();
    float worldh = world.getHeight();

    float rectSize = std::min(
        windowWidth / static_cast<float>(world.getWidth()),
        windowHeight / static_cast<float>(world.getHeight())
    );

    float w, h;
    bool HeighthFlag;
    if (worldw/worldh <= windowWidth/windowHeight) {
        h = windowHeight;
        w = worldw*windowHeight/(worldh);
        HeighthFlag = false;
    } else {
        h = (worldh)/worldw*windowWidth;
        w = windowWidth;
        HeighthFlag = true;
    }

    // Get sprites
    sf::Sprite pacmanSprite = pacmanview.getSprite();
    sf::Sprite fearGhostSprite = fearghostview.getSprite();

    // ✅ Simplified RenderVisitor - only needs fear sprite and pacman sprite
    RenderVisitor renderVisitor(
        window,
        fearGhostSprite,
        pacmanSprite,
        rectSize,
        windowWidth,
        windowHeight,
        HeighthFlag,
        h,
        w
    );

    // Render walls
    for (auto& wall : world.getWalls()) {
        wall->accept(renderVisitor);
    }

    // Render collectibles
    for (auto& collectible : world.getCollectibles()) {
        collectible->accept(renderVisitor);
    }

    // Render each ghost using its individual view from ghostViews
    for (const auto& ghost : world.getGhosts()) {
        auto pos = ghost->getPosition();
        auto screenPos = normalizeToScreen(pos.x, pos.y, windowWidth, windowHeight, HeighthFlag, h, w);

        sf::Sprite ghostSprite;
        if (ghost->getFearState()) {
            ghostSprite = fearghostview.getSprite();
        } else if (ghostViews.find(ghost.get()) != ghostViews.end()) {
            ghostSprite = ghostViews[ghost.get()]->getSprite();
        } else {
            std::cerr << "WARNING: No view found for ghost!" << std::endl;
            continue;
        }

        ghostSprite.setPosition(screenPos);
        ghostSprite.setScale(rectSize/16, rectSize/16);
        window.draw(ghostSprite);
    }

    // Render Pacman
    pacman->accept(renderVisitor);
}
