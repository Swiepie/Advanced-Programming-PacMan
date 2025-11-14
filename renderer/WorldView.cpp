//
// Created by Siebe Haché on 15/10/2025.
//

#include "WorldView.h"
#include <iostream>
#include "../entities/Wall.h"
#include "../entities/Coin.h"

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
sf::View getWorldView(unsigned int windowWidth, unsigned int windowHeight) {
    sf::View view;
    view.setSize(windowWidth, windowHeight);

    view.setCenter(windowWidth / 2.f, windowHeight / 2.f);
    return view;
}

void WorldView::render(const World& world, sf::RenderWindow& window, float windowWidth, float windowHeight) {
    // maak de view
    pacmanview.chooseTexture(world.getPacman()->getDirection());
    for (auto& e : world.getEntities()) {
        if (e->getSymbol() == 'R') {
            redGhostview.chooseTexture(e->getDirection());
        }
        if (e->getSymbol() == 'B') {
            pinkghostview.chooseTexture(e->getDirection());
        }
        if (e->getSymbol() == 'G') {
            blueghostview.chooseTexture(e->getDirection());
        }
    }

    fearghostview.chooseTexture();


    sf::View view = getWorldView(windowWidth, windowHeight);
    window.setView(view);

    float worldw = world.getWidth();
    float worldh = world.getHeight();
    // bepaal tilegrootte
    float rectSize = std::min(
        windowWidth / static_cast<float>(world.getWidth()),
        windowHeight / static_cast<float>(world.getHeight())
    );

    float w;
    float h;
    bool HeighthFlag;
    if (worldw/worldh <= windowWidth/windowHeight) { // dan is de hoogte het knelpunt
        h = windowHeight;
        w = worldw*windowHeight/(worldh);
        HeighthFlag = false;
    } else { // dan is de breedte het knelpunt
        h = (worldh)/worldw*windowWidth;
        w = windowWidth;
        HeighthFlag = true;
    };

    sf::Sprite pacmanSprite = pacmanview.getSprite();
    sf::Sprite redGhostSprite = redGhostview.getSprite();
    sf::Sprite pinkGhostSprite = pinkghostview.getSprite();
    sf::Sprite blueGhostSprite = blueghostview.getSprite();
    sf::Sprite fearGhostSprite = fearghostview.getSprite();
    // render entities in world-coördinaten
    for (auto& e : world.getEntities()) {
        auto pos = e->getPosition(); // nu in wereldcellen
        auto screenPos = normalizeToScreen(pos.x, pos.y, windowWidth, windowHeight, HeighthFlag, h, w);
        char symbol = e->getSymbol();

        if (symbol == '#') {
            sf::RectangleShape rect({rectSize, rectSize});
            rect.setFillColor(sf::Color::Blue);
            rect.setPosition(screenPos);
            window.draw(rect);
        } else if (symbol == '.') {
            sf::CircleShape circle(rectSize / 10.f);
            circle.setFillColor(sf::Color::Yellow);
            circle.setPosition(screenPos.x + rectSize/2 - rectSize/10, screenPos.y + rectSize/2 - rectSize/10);
            window.draw(circle);
        } else if (symbol == 'P') {
            pacmanSprite.setPosition(screenPos);
            pacmanSprite.setScale(rectSize/15, rectSize/15);
            window.draw(pacmanSprite);
        } else if (symbol == 'f') {
            sf::CircleShape circle(rectSize / 10.f);
            circle.setFillColor(sf::Color::Magenta);
            circle.setPosition(screenPos.x + rectSize/2 - rectSize/10, screenPos.y + rectSize/2 - rectSize/10);
            window.draw(circle);

        }
    }
    for (auto& e : world.getEntities()) {
        auto pos = e->getPosition(); // nu in wereldcellen
        auto screenPos = normalizeToScreen(pos.x, pos.y, windowWidth, windowHeight, HeighthFlag, h, w);
        char symbol = e->getSymbol();
        if (symbol == 'R') {
            if (e->getFearState()) {
                fearGhostSprite.setPosition(screenPos);
                fearGhostSprite.setScale(rectSize/16, rectSize/16);
                window.draw(fearGhostSprite);
            } else {
                redGhostSprite.setPosition(screenPos);
                redGhostSprite.setScale(rectSize/16, rectSize/16);
                window.draw(redGhostSprite);
            }
        } else if (symbol == 'B') {
            if (e->getFearState()) {
                fearGhostSprite.setPosition(screenPos);
                fearGhostSprite.setScale(rectSize/16, rectSize/16);
                window.draw(fearGhostSprite);
            } else {
                blueGhostSprite.setPosition(screenPos);
                blueGhostSprite.setScale(rectSize/16, rectSize/16);
                window.draw(blueGhostSprite);
            }

        } else if (symbol == 'G') {
            if (e->getFearState()) {
                fearGhostSprite.setPosition(screenPos);
                fearGhostSprite.setScale(rectSize/16, rectSize/16);
                window.draw(fearGhostSprite);
            } else {
                pinkGhostSprite.setPosition(screenPos);
                pinkGhostSprite.setScale(rectSize/16, rectSize/16);
                window.draw(pinkGhostSprite);
            }

        }
    }
}
