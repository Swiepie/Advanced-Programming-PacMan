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


void WorldView::render(const World& world, sf::RenderWindow& window,
                      float windowWidth, float windowHeight) {

    sf::View view = getWorldView(windowWidth, windowHeight);
    window.setView(view);

    float time = world.getTime();
    float worldw = world.getWidth();
    float worldh = world.getHeight();

    // Bereken pixelgrootte van een cel
    float rectSize = std::min(
        windowWidth / static_cast<float>(worldw),
        windowHeight / static_cast<float>(worldh)
    );

    float w, h;
    bool heightFlag;

    // EXACT dezelfde aspect-ratio check als versie 1
    if (worldw / worldh <= windowWidth / windowHeight) {
        h = windowHeight;
        w = worldw * windowHeight / worldh;
        heightFlag = false;
    } else {
        h = (worldh / worldw) * windowWidth;
        w = windowWidth;
        heightFlag = true;
    }

    // =============================
    // Render walls
    // =============================
    for (auto& wall : world.getWalls()) {
        auto pos = wall->getPosition();
        auto screenPos = normalizeToScreen(pos.x, pos.y,
                                           windowWidth, windowHeight,
                                           heightFlag, h, w);

        sf::RectangleShape rect({rectSize, rectSize});
        rect.setFillColor(sf::Color::Blue);
        rect.setPosition(screenPos);
        window.draw(rect);
    }

    // =============================
    // Render collectibles (coins)
    // =============================
    for (auto& collectible : world.getCollectibles()) {
        auto pos = collectible->getPosition();
        auto screenPos = normalizeToScreen(pos.x, pos.y,
                                           windowWidth, windowHeight,
                                           heightFlag, h, w);

        sf::CircleShape circle(rectSize / 10.f);
        circle.setFillColor(sf::Color::Yellow);

        // EXACT CENTREREN zoals visitor
        circle.setPosition(screenPos.x + rectSize/2 - rectSize/10,
                           screenPos.y + rectSize/2 - rectSize/10);

        window.draw(circle);
    }

    // =============================
    // PACMAN (update + render)
    // =============================
    Pacman* pacman = world.getPacman();
    if (pacman && pacman->getObserver()) {

        EntityView* view = static_cast<EntityView*>(pacman->getObserver());

        // Texture update identiek aan visitor
        view->updateTexture(time);

        auto pos = pacman->getPosition();
        auto screenPos = normalizeToScreen(pos.x, pos.y,
                                           windowWidth, windowHeight,
                                           heightFlag, h, w);

        sf::Sprite& sprite = view->getSprite();
        sprite.setPosition(screenPos);

        // SCALE exact als visitor
        sprite.setScale(rectSize / 15.f, rectSize / 15.f);

        window.draw(sprite);
    }

    // =============================
    // GHOSTS (update + render)
    // =============================
    for (auto& ghost : world.getGhosts()) {
        if (ghost->getObserver()) {

            EntityView* view = static_cast<EntityView*>(ghost->getObserver());

            // Texture update identiek aan visitor
            view->updateTexture(time);

            auto pos = ghost->getPosition();
            auto screenPos = normalizeToScreen(pos.x, pos.y,
                                               windowWidth, windowHeight,
                                               heightFlag, h, w);

            sf::Sprite& sprite = view->getSprite();
            sprite.setPosition(screenPos);

            // SCALE exact als visitor
            sprite.setScale(rectSize / 16.f, rectSize / 16.f);

            window.draw(sprite);
        }
    }
}

