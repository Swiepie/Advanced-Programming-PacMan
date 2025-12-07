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



void WorldView::render(const World& world, sf::RenderWindow& window, float windowWidth, float windowHeight) {
    float time = world.getTime();
    Pacman* pacman = world.getPacman();

    // ✅ Create views for new ghosts (first time or after reset)
    for (const auto& ghost : world.getGhosts()) {
        if (ghostViews.find(ghost.get()) == ghostViews.end()) {
            ViewCreatorVisitor creator;
            ghost->accept(creator);
            ghostViews[ghost.get()] = std::move(creator.view);
        }
    }
    TextureVisitor textureVisitor(redGhostview, blueghostview, pinkghostview, pacmanview, time);
    for (auto& ghost : world.getGhosts()) {
        ghost->accept(textureVisitor);
    }
    pacman->accept(textureVisitor);
    // Update fear ghost texture
    fearghostview.chooseTexture(time);


    sf::View view = getWorldView(windowWidth, windowHeight);
    window.setView(view);

    float worldw = world.getWidth();
    float worldh = world.getHeight();

    // Determine tile size
    float rectSize = std::min(
        windowWidth / static_cast<float>(world.getWidth()),
        windowHeight / static_cast<float>(world.getHeight())
    );

    float w;
    float h;
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
    sf::Sprite redGhostSprite = redGhostview.getSprite();
    sf::Sprite pinkGhostSprite = pinkghostview.getSprite();
    sf::Sprite blueGhostSprite = blueghostview.getSprite();
    sf::Sprite fearGhostSprite = fearghostview.getSprite();

    // Create render visitor for walls and collectibles
    RenderVisitor renderVisitor(
        window,
        redGhostSprite,
        blueGhostSprite,
        pinkGhostSprite,
        fearGhostSprite,
        pacmanSprite,
        rectSize,
        windowWidth,
        windowHeight,
        HeighthFlag,
        h,
        w
    );

    //  Render walls using visitor
    for (auto& wall : world.getWalls()) {
        wall->accept(renderVisitor);
    }

    // Render collectibles (coins and fruits) using visitor
    for (auto& collectible : world.getCollectibles()) {
        collectible->accept(renderVisitor);
    }
    //  Render ghosts using visitor
    for (auto& ghost : world.getGhosts()) {
        ghost->accept(renderVisitor);
    }
    // Render Pacman using visitor
    pacman->accept(renderVisitor);
}
