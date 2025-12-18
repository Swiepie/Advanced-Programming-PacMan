/**
* @file WallView.h
 * @brief Definieert de view klasse voor Wall entiteiten
 * @author siebe
 * @date 13/12/2025
 */

#ifndef WALLVIEW_H
#define WALLVIEW_H

#include "../logic/Stopwatch.h"
#include "../logic/entities/Wall.h"
#include "Camera.h"
#include "EntityView.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>

/**
 * @class WallView
 * @brief View klasse voor het renderen van Wall entiteiten
 *
 * Beheert de visuele representatie van muur objecten in het spel.
 * Erft van EntityView en implementeert specifieke rendering logica voor muren.
 * Muren zijn statische objecten die het speelveld begrenzen.
 */
class WallView : public EntityView {
private:
    Wall* wall;  ///< Pointer naar de muur entiteit die gerenderd wordt

public:
    /**
     * @brief Construeert een WallView voor opgegeven muur
     * @param w Pointer naar de muur entiteit
     * @param window Gedeelde pointer naar het render venster
     */
    explicit WallView(Wall* w, std::shared_ptr<sf::RenderWindow> window)
        : EntityView(w, std::move(window)), wall(w) {}

    /**
     * @brief Update de view logica per frame
     * @param time Delta tijd sinds vorige frame in seconden
     */
    void update(float time) override;

    /**
     * @brief Rendert de muur naar het venster
     *
     * Tekent de visuele representatie van de muur op het scherm.
     */
    void render() override;

    /**
     * @brief Update de textuur of animatie van de muur
     * @param time Delta tijd voor animatie updates
     */
    void updateTexture(float time) override;
};

#endif // WALLVIEW_H
