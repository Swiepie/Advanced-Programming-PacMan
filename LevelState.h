//
// Created by Siebe Haché on 15/10/2025.
//

#include "State.h"
#include "World.h"
#include "StateManager.h"
#include <SFML/Graphics.hpp>
#include "renderer/WorldView.h"
class LevelState : public State {
private:
    World world;
    WorldView renderer;
public:
    LevelState() {
        world.loadMap("../assets/map.txt");
        world.printMap();
    }

    void handleInput(StateManager& manager, sf::RenderWindow& window) override;
    void update(StateManager& manager, float deltaTime) override {
        world.update(deltaTime);
    }
    void render(sf::RenderWindow& window) override {
        window.clear(sf::Color::Black);
        renderer.render(world, window);
        window.display();
    }
};
