/**
 * @file GhostView.h
 * @brief Definieert de view klassen voor Ghost entiteiten en hun varianten
 * @author siebe
 * @date 09/11/2025
 */

#ifndef GHOSTVIEW_H
#define GHOSTVIEW_H

#include "../logic/Stopwatch.h"
#include "../logic/entities/Ghost.h"
#include "Camera.h"
#include "EntityView.h"
#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @class GhostView
 * @brief Basisklasse voor het renderen van Ghost entiteiten
 *
 * Beheert de visuele representatie van ghostsin het spel. Implementeert
 * animaties voor verschillende richtingen en fear mode. Erft van EntityView
 * en biedt basis functionaliteit die door specifieke ghost views uitgebreid wordt.
 */
class GhostView : public EntityView {
protected:
    Ghost* ghost; ///< Pointer naar de ghost entity die gerenderd wordt

public:
    /**
     * @brief Construeert een GhostView voor opgegeven ghost
     * @param g Pointer naar de ghost entity
     * @param window Gedeelde pointer naar het render venster
     */
    explicit GhostView(Ghost* g, std::shared_ptr<sf::RenderWindow> window);

    /**
     * @brief Rendert de ghost naar het venster
     *
     * Tekent de visuele representatie van de ghost op het scherm,
     * inclusief positie en huidige animatie frame.
     */
    void render() override;

    /**
     * @brief Update de view logica per frame
     * @param time Delta tijd sinds vorige frame in seconden
     *
     * Update animaties en synchroniseert met ghost status.
     */
    void update(float time) override;

    /**
     * @brief Update de textuur of animatie van de ghost
     * @param time Delta tijd voor animatie updates
     *
     * Selecteert de juiste textuur op basis van richting en status (normaal/fear mode).
     */
    void updateTexture(float time) override;

    /**
     * @brief Kiest de juiste textuur op basis van bewegingsrichting
     * @param direction Huidige bewegingsrichting van de ghost
     * @param time Delta tijd voor animatie timing
     *
     * Virtuele methode die door afgeleide klassen overschreven wordt
     * voor kleur-specifieke textures.
     */
    virtual void chooseTexture(char direction, float time);

    /**
     * @brief Kiest de fear mode textuur
     * @param time Delta tijd voor fear mode animatie
     *
     * Toont de bluee "vulnerable" textuur wanneer de ghost in fear mode is.
     */
    void chooseFearTexture(float time);
};

/**
 * @class RedGhostView
 * @brief View klasse voor red ghost
 *
 * Specialisatie van GhostView met red sprite textures.
 */
class RedGhostView : public GhostView {
public:
    /**
     * @brief Construeert een RedGhostView voor opgegeven red ghost
     * @param g Pointer naar de red ghost entity
     * @param window Gedeelde pointer naar het render venster
     */
    explicit RedGhostView(RedGhost* g, std::shared_ptr<sf::RenderWindow> window);

    /**
     * @brief Kiest de red ghost textuur op basis van richting
     * @param direction Huidige bewegingsrichting
     * @param time Delta tijd voor animatie
     */
    void chooseTexture(char direction, float time) override;
};

/**
 * @class BlueGhostView
 * @brief View klasse voor bluee ghost
 *
 * Specialisatie van GhostView met bluee sprite textures.
 */
class BlueGhostView : public GhostView {
public:
    /**
     * @brief Construeert een BlueGhostView voor opgegeven bluee ghost
     * @param g Pointer naar de bluee ghost entity
     * @param window Gedeelde pointer naar het render venster
     */
    explicit BlueGhostView(BlueGhost* g, std::shared_ptr<sf::RenderWindow> window);

    /**
     * @brief Kiest de bluee ghost textuur op basis van richting
     * @param direction Huidige bewegingsrichting
     * @param time Delta tijd voor animatie
     */
    void chooseTexture(char direction, float time) override;
};

/**
 * @class PinkGhostView
 * @brief View klasse voor pink ghost
 *
 * Specialisatie van GhostView met pink sprite textures.
 */
class PinkGhostView : public GhostView {
public:
    /**
     * @brief Construeert een PinkGhostView voor opgegeven pink ghost
     * @param g Pointer naar de pink ghost entity
     * @param window Gedeelde pointer naar het render venster
     */
    explicit PinkGhostView(PinkGhost* g, std::shared_ptr<sf::RenderWindow> window);

    /**
     * @brief Kiest de pink ghost textuur op basis van richting
     * @param direction Huidige bewegingsrichting
     * @param time Delta tijd voor animatie
     */
    void chooseTexture(char direction, float time) override;
};

#endif // GHOSTVIEW_H
