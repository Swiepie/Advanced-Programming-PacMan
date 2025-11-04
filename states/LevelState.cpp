//
// Created by Siebe Haché on 15/10/2025.
//

#include "LevelState.h"


void LevelState::handleEvent(StateManager& manager, sf::RenderWindow& window, const sf::Event& event) {
    if (event.type == sf::Event::Closed)
        window.close();

    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            manager.pushState(std::make_unique<PausedState>()); // back to menu
        }
#if 1
        else if (event.key.code == sf::Keyboard::Up){
            world.movePacman(0, -1);
        }
        else if (event.key.code == sf::Keyboard::Down){
            world.movePacman(0, 1);
        }
        else if (event.key.code == sf::Keyboard::Left){
            world.movePacman(-1, 0);
        }
        else if (event.key.code == sf::Keyboard::Right){
        //std::cout<< "RECHTS" <<std::endl;
        world.movePacman(1, 0);
        }
#endif
    }
}

void LevelState::update(StateManager& manager, float deltaTime)  {
    world.update(deltaTime);
}
void LevelState::render(sf::RenderWindow& window, unsigned int windowWidth, unsigned int windowHeight)  {
    renderer.render(world, window, windowWidth, windowHeight);
}

void LevelState::onEnter() {
    Stopwatch::getInstance().restart(); // reset + start timer when entering game
    std::cout << "Level started! Stopwatch running...\n";
}
void LevelState::onExit() {
    Stopwatch::getInstance().stop(); // stop when leaving
    std::cout << "Level ended. Final time: "
              << Stopwatch::getInstance().GetElapsedTime() << "s\n";
}