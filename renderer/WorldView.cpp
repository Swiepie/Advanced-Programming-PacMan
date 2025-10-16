//
// Created by Siebe Haché on 15/10/2025.
//

#include "WorldView.h"

#include <iostream>

#include "../Wall.h"
#include "../Coin.h"

sf::Vector2f normalizeToScreen(float x, float y, float screenWidth, float screenHeight, bool flag, float rectsize, float worldWidth, float worldHeight, float h, float w) {
    float whitespace = (screenHeight-h)/2;
    if(flag == true) {
        float px = (x + 1.0f) * 0.5f * screenWidth;
        float py = ((y + 1.0f) * 0.5f * screenHeight)+ whitespace;
        return {px, py};
    } else {å
        float px = ((x + 1.0f) * 0.5f * screenWidth) + whitespace;
        float py = (y + 1.0f) * 0.5f * screenHeight;
        return {px, py};
    }
    //float px = (x + 1.0f) * 0.5f * screenWidth;


}

void WorldView::render(const World& world, sf::RenderWindow& window) {
    float windoww = window.getSize().x;
    float windowh = window.getSize().y;

    float worldw = world.getWidth();
    float worldh = world.getHeight();

    float w;
    float h;

    float rectSize;
    bool HeighthFlag = false;
    if (worldw/worldh >= windoww/windowh) { // dan is de hoogte het knelpunt
        h = windowh;
        w = worldw*windowh/(worldh);
        HeighthFlag = false;
        rectSize = windowh/worldh;// HIER ZAT DE FOUT
    } else { // dan is de breedte het knelpunt
        h = (worldw)/worldh*windoww;
        w = windoww;
        HeighthFlag = true;
        rectSize = windoww/worldw;
    };

//maak een world get width/heigth zodat je gebruik kan maken hier om alles altijd even groot te houden op het scherm
    //op basis daarvan kunnen we de windox size starten, en als ze vergroten, moet er witruimte voorzien worden aan de boven en onderkant zodat de rechthoeken niet uigerokken worden.
    //Dus we moeten op basis van de tot hoogte en breedte formules gebruiken om te zien welke kant het kleinste is en daarvan de rest afhankelijk maken.
    //
    for (auto& e : world.getEntities()) {
        auto pos = e->getPosition();
        auto screenPos = normalizeToScreen(pos.x, pos.y, w, h, HeighthFlag, rectSize, worldw, worldh, h, w);
        char symbol = e->getSymbol();
        if (symbol == '#') {
            sf::RectangleShape rect({rectSize, rectSize});
            rect.setFillColor(sf::Color::Blue);
            rect.setPosition(screenPos);
            window.draw(rect);
        } else if (symbol == '.') {
            sf::CircleShape circle(4);
            circle.setFillColor(sf::Color::Yellow);
            circle.setPosition(screenPos.x+21, screenPos.y+21);
            window.draw(circle);
        }
    }
    std::cout << h << " " << w <<std::endl;
    std::cout << rectSize << std::endl;
    std::cout << "width: " << windoww << "  heigth: " << windowh <<std::endl;
    std::cout << "World width: " << worldw << "  heigth: " << worldh <<std::endl;
}