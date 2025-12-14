//
// Created by Siebe Haché on 15/10/2025.
//

#include "LevelState.h"


void LevelState::handleEvent(std::shared_ptr<StateManager> stateManager, std::shared_ptr<sf::RenderWindow> window, const sf::Event& event) {
    if (event.type == sf::Event::Closed)
        window->close();


    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            stateManager->pushState(std::make_unique<PausedState>()); // back to menu
        }

        auto pacman = world->getPacman();
        if (!pacman) return;

        switch (event.key.code) {
            case sf::Keyboard::Up:    pacman->setBufferdirection('N'); break;
            case sf::Keyboard::Down:  pacman->setBufferdirection('Z'); break;
            case sf::Keyboard::Left:  pacman->setBufferdirection('W'); break;
            case sf::Keyboard::Right: pacman->setBufferdirection('O'); break;
            default: break;
        }
    }
}

void LevelState::update(std::shared_ptr<StateManager> stateManager, float deltaTime)  {
    if (deltaTime > 0.5) {
        return;
    }
    if (world->getPacmanLives()<= 0 ) {
        int score = world->getScore().get();
        stateManager->pushState(std::make_unique<FinishState>(score, factory));
        world->getScore().submit();

    }
    if (world->getCoinCount() == 0) {
        world->loadMap("../assets/map2.txt");
        world->resetWorld();
    }
    world->update(deltaTime);
}
void LevelState::render(std::shared_ptr<sf::RenderWindow> window, unsigned int windowWidth, unsigned int windowHeight)  {

    WorldView::render(world, window, windowWidth, windowHeight);

    float verticalOffset = 40.f;

    sf::Vector2f viewSize = window->getView().getSize();
    sf::Vector2f viewCenter = window->getView().getCenter();

    score.setString("   Score: " + std::to_string(world->getScore().get()));
    lives.setString("   Lives: " + std::to_string(world->getPacmanLives()));

    // Schaal op basis van hoogte (10% van view hoogte)
    float preferredHeight = viewSize.y * 0.10f;
    float textHeight = score.getLocalBounds().height;
    float scaleY = preferredHeight / textHeight;
    // Controleer breedte (max 80% van view breedte)
    float maxWidth = viewSize.x * 0.80f;
    float textWidth = score.getLocalBounds().width;
    float scaleX = maxWidth / textWidth;

    float scale = std::min(scaleX, scaleY);

    scale /= 4.f; // jouw scaling-aanpassing
    score.setScale(scale, scale);
    lives.setScale(scale, scale);

    // Origins linksboven
    sf::FloatRect scoreBounds = score.getLocalBounds();
    score.setOrigin(scoreBounds.left, scoreBounds.top);

    sf::FloatRect livesBounds = lives.getLocalBounds();
    lives.setOrigin(livesBounds.left, livesBounds.top);

    // Linksonder positie
    float leftX = viewCenter.x - viewSize.x / 2.f + 10.f;
    float bottomY = viewCenter.y + viewSize.y / 2.f - 10.f;

    // Score komt eerst
    float scoreY = bottomY - scoreBounds.height * scale - verticalOffset;

    // Lives komt eronder (dus nog een regel lager)
    float livesY = scoreY + scoreBounds.height * scale + 5.f; // 5px spacing

    score.setPosition(leftX, scoreY);
    lives.setPosition(leftX, livesY);

    window->draw(score);
    window->draw(lives);
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