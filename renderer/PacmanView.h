/**
 * @file PacmanView.h
 * @brief Definieert de view klasse voor Pacman entiteit rendering
 * @author siebe
 * @date 02/11/2025
 */

#ifndef PACMANVIEW_H
#define PACMANVIEW_H

#include "../logic/Stopwatch.h"
#include "../logic/entities/Pacman.h"
#include "Camera.h"
#include "EntityView.h"
#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @class PacmanView
 * @brief View klasse voor het renderen van de Pacman speler entiteit
 *
 * Beheert de visuele representatie van Pacman in het spel. Implementeert
 * mond animaties die synchroniseren met beweging en richting. Erft van
 * EntityView en implementeert het Observer pattern voor automatische updates.
 */
class PacmanView : public EntityView {
protected:
    Pacman* pacman;  ///< Pointer naar de Pacman entiteit die gerenderd wordt

private:
    float totalTime = 0.0;      ///< Totale verstreken tijd voor animatie tracking
    bool mouthOpen = true;      ///< Indicator voor mond open/dicht status in animatie
    float frameTimer = 0.0f;    ///< Timer voor frame switching in animatie cyclus
    double speed = 1;           ///< Animatie snelheid multiplier
    int i = 2;                  ///< Frame index voor sprite sheet selectie

public:
    /**
     * @brief Construeert een PacmanView voor opgegeven Pacman entiteit
     * @param pacman Pointer naar de Pacman entiteit
     * @param window Gedeelde pointer naar het render venster
     */
    explicit PacmanView(Pacman* pacman, std::shared_ptr<sf::RenderWindow> window);

    /**
     * @brief Update de view logica per frame
     * @param time Delta tijd sinds vorige frame in seconden
     *
     * Update animaties, mond beweging en synchroniseert met Pacman status.
     */
    void update(float time) override;

    /**
     * @brief Observer pattern update zonder tijd parameter
     *
     * Alternatieve update methode voor observer notificaties zonder timing info.
     */
    void update() override;

    /**
     * @brief Update de textuur of animatie van Pacman
     * @param time Delta tijd voor animatie updates
     *
     * Selecteert de juiste sprite op basis van huidige richting en mond status.
     */
    void updateTexture(float time) override;

    /**
     * @brief Kiest de juiste textuur op basis van bewegingsrichting
     * @param direction Huidige bewegingsrichting ('U', 'D', 'L', 'R')
     * @param time Delta tijd voor animatie timing
     *
     * Selecteert de correcte sprite uit de sprite sheet voor de opgegeven
     * richting en huidige mond animatie frame.
     */
    void chooseTexture(char direction, float time);

    /**
     * @brief Rendert Pacman naar het venster
     *
     * Tekent de visuele representatie van Pacman op het scherm met
     * de huidige positie en animatie frame.
     */
    void render() override;
};

#endif // PACMANVIEW_H
