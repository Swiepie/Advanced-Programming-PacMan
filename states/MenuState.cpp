//
// Created by Siebe Haché on 15/10/2025.
//

#include "MenuState.h"

void MenuState::handleEvent(std::shared_ptr<StateManager> stateManager, std::shared_ptr<sf::RenderWindow> window,
                            const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        stateManager->pushState(std::make_unique<LevelState>(factory)); // go to the level
    }
}
void MenuState::render(std::shared_ptr<sf::RenderWindow> window, unsigned int windowWidth, unsigned int windowHeight) {
    sb.load();
    auto top = sb.getTop5();

    std::string hs = "Highscores:\n";
    for (int s : top) {
        hs += std::to_string(s) + "\n";
    }
    highscores.setString(hs);
    sf::Vector2f viewSize = window->getView().getSize();
    sf::Vector2f viewCenter = window->getView().getCenter();

    float preferredHeight = viewSize.y * 0.10f;
    float titleHeight = title.getLocalBounds().height;
    float scaleY = preferredHeight / titleHeight;

    float maxWidth = viewSize.x * 0.80f;
    float titleWidth = title.getLocalBounds().width;
    float scaleX = maxWidth / titleWidth;
    float scale = std::min(scaleX, scaleY);

    title.setScale(scale, scale);

    title.setOrigin(title.getLocalBounds().width / 2.f, title.getLocalBounds().height / 2.f);
    title.setPosition(viewCenter.x, viewCenter.y - viewSize.y * 0.15f);

    window->draw(title);

    highscores.setScale(scale * 0.75f, scale * 0.75f);

    highscores.setOrigin(highscores.getLocalBounds().width / 2.f, highscores.getLocalBounds().height / 2.f);
    highscores.setPosition(viewCenter.x, viewCenter.y + viewSize.y * 0.1f);

    window->draw(highscores);
}