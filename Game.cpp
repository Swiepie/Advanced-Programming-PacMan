#include "Game.h"

#include "states/MenuState.h"

Game::Game() {
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1300, 800), "pacman");
    stateManager = std::make_shared<StateManager>();
    Stopwatch::getInstance().start();
    window->setFramerateLimit(framerate);

    FileDimensions dimensions = getFileDimensions("../assets/map2.txt");

    Camera::getInstance().initialize(static_cast<float>(dimensions.width), static_cast<float>(dimensions.height));

    auto factory = std::make_shared<ConcreteFactory>(window);

    stateManager->pushState(std::make_unique<MenuState>(factory));
}

Game::~Game() {
    window->close();
    window.reset();
    stateManager->popState();
}

void Game::run() const {
    while (window->isOpen()) {

        float deltaTime = Stopwatch::getInstance().GetElapsedTime();

        State* current = stateManager->currentState();

        sf::Event event{};
        unsigned int windowWidth = window->getSize().x;
        unsigned int windowHeight = window->getSize().y;
        while (window->pollEvent(event)) {
            if (current)
                current->handleEvent(stateManager, window, event);
            if (event.type == sf::Event::Resized) {
                windowWidth = event.size.width;
                windowHeight = event.size.height;

                // Update de actieve view zodat deze de nieuwe pixelgrootte gebruikt
                sf::FloatRect visibleArea(0, 0, static_cast<float>(windowWidth), static_cast<float>(windowHeight));
                window->setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::Closed) {
                window->close();
            }
        }

        if (current) {
            current->update(stateManager, deltaTime);
        }

        window->clear(sf::Color::Black);
        if (current) {
            current->render(window, windowWidth, windowHeight);
        }
        Stopwatch::getInstance().restart();
        window->display();
        stateManager->processStateChanges();
    }
}

FileDimensions Game::getFileDimensions(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Kon bestand niet openen: " + filename);
    }

    FileDimensions dims{0, 0};
    std::string line;

    while (std::getline(file, line)) {
        dims.height++;
        if (line.length() > dims.width) {
            dims.width = line.length();
        }
    }
    return dims;
}