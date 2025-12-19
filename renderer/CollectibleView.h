/**
 * @file CollectibleView.h
 * @brief Definieert de view klassen voor verzamelbare objecten (fruit en coinen)
 * @author siebe
 * @date 13/12/2025
 */

#ifndef COLLECTIBLEVIEW_H
#define COLLECTIBLEVIEW_H

#include "../logic/Stopwatch.h"
#include "../logic/entities/Coin.h"
#include "../logic/entities/Fruit.h"
#include "Camera.h"
#include "EntityView.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>

/**
 * @class FruitView
 * @brief View klasse voor het renderen van Fruit entiteiten
 *
 * Beheert de visuele representatie van fruit objecten in het spel.
 * Erft van EntityView en implementeert specifieke rendering logica voor fruit.
 */
class FruitView : public EntityView {
private:
    Fruit* fruit; ///< Pointer naar de fruit entity die gerenderd wordt

public:
    /**
     * @brief Construeert een FruitView voor opgegeven fruit
     * @param f Pointer naar de fruit entity
     * @param window Gedeelde pointer naar het render venster
     */
    explicit FruitView(Fruit* f, std::shared_ptr<sf::RenderWindow> window)
        : EntityView(f, std::move(window)), fruit(f) {}

    /**
     * @brief Update de view logica per frame
     * @param time Delta tijd sinds vorige frame in seconden
     */
    void update(float time) override;

    /**
     * @brief Rendert het fruit naar het venster
     *
     * Tekent de visuele representatie van het fruit op het scherm.
     */
    void render() override;

    /**
     * @brief Update de textuur of animatie van het fruit
     * @param time Delta tijd voor animatie updates
     */
    void updateTexture(float time) override;
};

/**
 * @class CoinView
 * @brief View klasse voor het renderen van Coin entiteiten
 *
 * Beheert de visuele representatie van coin objecten in het spel.
 * Erft van EntityView en implementeert specifieke rendering logica voor coinen.
 */
class CoinView : public EntityView {
private:
    Coin* coin; ///< Pointer naar de coin entity die gerenderd wordt

public:
    /**
     * @brief Construeert een CoinView voor opgegeven coin
     * @param c Pointer naar de coin entity
     * @param window Gedeelde pointer naar het render venster
     */
    explicit CoinView(Coin* c, std::shared_ptr<sf::RenderWindow> window) : EntityView(c, std::move(window)), coin(c) {}

    /**
     * @brief Update de view logica per frame
     * @param time Delta tijd sinds vorige frame in seconden
     */
    void update(float time) override;

    /**
     * @brief Rendert de coin naar het venster
     *
     * Tekent de visuele representatie van de coin op het scherm.
     */
    void render() override;

    /**
     * @brief Update de textuur of animatie van de coin
     * @param time Delta tijd voor animatie updates
     */
    void updateTexture(float time) override;
};

#endif // COLLECTIBLEVIEW_H
