//
// Created by Siebe Haché on 15/10/2025.
//

#ifndef VIEW_H
#define VIEW_H



#include <SFML/Graphics.hpp>
#include "../Entity.h"

class View {
private:
    sf::Shape* shape = nullptr;

public:
    explicit View(const Entity& entity) {
        char symbol = entity.getSymbol();
        auto pos = entity.getPosition();

        if (symbol == '#') {
            auto* rect = new sf::RectangleShape({50, 50});
            rect->setFillColor(sf::Color::Blue);
            rect->setPosition(pos.x, pos.y);
            shape = rect;
        } else if (symbol == '.') {
            auto* circ = new sf::CircleShape(4);
            circ->setFillColor(sf::Color::Yellow);
            circ->setPosition(pos.x + 25, pos.y + 25);
            shape = circ;
        }
    }

    void render(sf::RenderWindow& window) const {
        if (shape) window.draw(*shape);
    }

    ~View() { delete shape; }
};


#endif //VIEW_H
