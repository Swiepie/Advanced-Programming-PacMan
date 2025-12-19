/**
 * @file EntityView.h
 * @brief Definieert de abstracte EntityView basisklasse voor entity visualisatie
 * @author siebe
 * @date 12/12/2025
 */

#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include "../logic/Observer.h"
#include "../logic/entities/Entity.h"

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @class EntityView
 * @brief Abstracte basisklasse voor het renderen van entiteiten
 *
 * Implementeert het Observer pattern om automatisch te updaten wanneer de
 * onderliggende entity verandert. Biedt gemeenschappelijke functionaliteit
 * voor sprite management, texture updates en frame timing voor alle entity views.
 */
class EntityView : public Observer {
protected:
    Entity* entity;                           ///< Raw pointer naar de geobserveerde entity
    sf::Sprite sprite;                        ///< SFML sprite voor rendering
    sf::Texture texture;                      ///< SFML texture voor de sprite
    float lastFrameTime = 0.0f;               ///< Tijd van laatste frame update
    float frameCooldown = 0.1f;               ///< Minimale tijd tussen frames (in seconden)
    bool mouthOpen = false;                   ///< Indicator voor mond animatie (voor pacman)
    std::shared_ptr<sf::RenderWindow> window; ///< Gedeelde pointer naar het render venster

public:
    /**
     * @brief Construeert een EntityView voor opgegeven entity
     * @param e Pointer naar de entity die gerenderd moet worden
     * @param w Gedeelde pointer naar het SFML render venster
     */
    EntityView(Entity* e, std::shared_ptr<sf::RenderWindow> w) : entity(e), window(std::move(w)) {}

    /**
     * @brief Virtual destructor voor correcte cleanup van afgeleide klassen
     */
    ~EntityView() override = default;

    /**
     * @brief Observer interface implementatie voor updates
     *
     * Basis implementatie - subklassen kunnen deze overriden voor
     * specifieke update logica wanneer de entity verandert.
     */
    void update() override {
        // Base implementation - subclasses can override
    }

    /**
     * @brief Notificatie handler wanneer geobserveerde entity verandert
     *
     * Roept update() aan wanneer de entity een verandering meldt.
     */
    void onNotify() { update(); }

    /**
     * @brief Update de texture of animatie van de entity
     * @param time Delta tijd voor animatie updates
     *
     * Pure virtuele functie die door elke afgeleide klasse geïmplementeerd
     * moet worden voor specifieke texture/animatie logica.
     */
    virtual void updateTexture(float time) = 0;

    /**
     * @brief Geeft de sprite van deze view
     * @return SFML sprite object
     */
    sf::Sprite getSprite();

    /**
     * @brief Geeft de onderliggende entity
     * @return Pointer naar de geobserveerde entity
     */
    Entity* getEntity() const;

    /**
     * @brief Rendert de entity naar het venster
     *
     * Virtuele functie met standaard lege implementatie.
     * Overschrijf in afgeleide klassen voor daadwerkelijke rendering.
     */
    virtual void render() {};

protected:
    /**
     * @brief Controleert of er genoeg tijd verstreken is voor een nieuw frame
     * @param currentTime Huidige tijd in seconden
     * @return true als frame cooldown verstreken is, false anders
     *
     * Hulpmethode voor frame rate limiting in animaties.
     */
    bool readyFrame(float currentTime) const { return (currentTime - lastFrameTime) >= frameCooldown; }

    /**
     * @brief Registreert de tijd van het huidige frame
     * @param currentTime Huidige tijd in seconden
     *
     * Hulpmethode voor het bijhouden van frame timing.
     */
    void recordFrameTime(float currentTime) { lastFrameTime = currentTime; }
};

#endif // ENTITYVIEW_H
