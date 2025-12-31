//
// Created by Siebe Haché on 15/10/2025.
//

#include "MenuState.h"

void MenuState::handleEvent(std::shared_ptr<StateManager> stateManager, std::shared_ptr<sf::RenderWindow> window,const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        sf::Vector2f mousePosF(static_cast<float>(mousePos.x),
                               static_cast<float>(mousePos.y));

        // Check of play button werd geklikt
        if (playButton.getGlobalBounds().contains(mousePosF)) {
            stateManager->pushState(std::make_unique<LevelState>(factory));
        }
        }

    // Fallback: ook toetsenbord support
    if (event.type == sf::Event::KeyPressed) {
        stateManager->pushState(std::make_unique<LevelState>(factory));
    }
}

void MenuState::render(std::shared_ptr<sf::RenderWindow> window, unsigned int windowWidth, unsigned int windowHeight) {
    sb.load();
    auto top = sb.getTop5();

    std::string hs = "Top 5 Highscores:\n";
    for (int i = 0; i < top.size(); ++i) {
        hs += std::to_string(i + 1) + ". " + std::to_string(top[i]) + "\n";
    }
    highscores.setString(hs);

    // Centreer titel bovenaan
    title.setPosition(static_cast<float>(windowWidth) / 2.f - title.getGlobalBounds().width / 2.f, 50.f);

    // **Centreer highscores in het midden**
    sf::FloatRect hsBounds = highscores.getGlobalBounds();
    highscores.setPosition(
        static_cast<float>(windowWidth) / 2.f - hsBounds.width / 2.f,
        static_cast<float>(windowHeight) / 2.f - hsBounds.height / 2.f
    );

    // Centreer play button onderaan
    playButton.setPosition(static_cast<float>(windowWidth) / 2.f - 100.f, static_cast<float>(windowHeight) - 150.f);

    // Centreer tekst op button
    sf::FloatRect textBounds = playButtonText.getGlobalBounds();
    playButtonText.setPosition(
        playButton.getPosition().x + (playButton.getSize().x - textBounds.width) / 2.f,
        playButton.getPosition().y + (playButton.getSize().y - textBounds.height) / 2.f - 5.f
    );

    // Hover effect
    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
    if (playButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        playButton.setFillColor(sf::Color(70, 70, 200));
    } else {
        playButton.setFillColor(sf::Color(10, 10, 150));
    }

    // Draw alles
    window->draw(title);
    window->draw(highscores);
    window->draw(playButton);
    window->draw(playButtonText);
}
