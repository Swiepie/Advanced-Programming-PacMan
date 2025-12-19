/**
 * @file Camera.h
 * @brief Definieert de Camera singleton voor coördinaat transformatie en scherm berekeningen
 * @author Siebe Haché
 * @date [Datum]
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include <memory>

/**
 * @class Camera
 * @brief Singleton klasse voor camera en scherm transformatie beheer
 *
 * Beheert de conversie tussen game wereld coördinaten en scherm coördinaten.
 * Gebruikt het Singleton pattern om één globale camera instantie te garanderen.
 * Biedt hulpmiddelen voor scherm berekeningen en aspect ratio beheer.
 */
class Camera {
private:
    float width;  ///< Breedte van de camera viewport
    float height; ///< Hoogte van de camera viewport

    /**
     * @brief Private constructor voor singleton implementatie
     *
     * Initialiseert camera met breedte en hoogte 0.
     */
    Camera() : width(0), height(0) {}

    // Delete copy constructor en assignment operator voor singleton

public:
    /**
     * @brief Verwijderde copy constructor
     *
     * Voorkomt kopiëren van de singleton instantie.
     */
    Camera(const Camera&) = delete;

    /**
     * @brief Verwijderde assignment operator
     *
     * Voorkomt toewijzing van de singleton instantie.
     */
    Camera& operator=(const Camera&) = delete;

    /**
     * @brief Destructor
     */
    ~Camera() = default;

    /**
     * @brief Geeft de singleton instantie van de Camera
     * @return Referentie naar de unieke Camera instantie
     *
     * Creëert de instantie bij eerste aanroep en retourneert steeds dezelfde instantie.
     */
    static Camera& getInstance();

    /**
     * @brief Initialiseert de camera met opgegeven dimensies
     * @param w Breedte van de viewport
     * @param h Hoogte van de viewport
     *
     * Moet aangeroepen worden voordat de camera gebruikt wordt.
     */
    void initialize(float w, float h);

    /**
     * @brief Geeft de breedte van de camera
     * @return Viewport breedte
     */
    float getWidth() const { return width; }

    /**
     * @brief Geeft de hoogte van de camera
     * @return Viewport hoogte
     */
    float getHeight() const { return height; }

    /**
     * @struct ScreenInfo
     * @brief Hulpstructuur voor scherm berekeningen
     *
     * Bevat berekende scherm informatie voor coördinaat transformaties
     * en aspect ratio beheer.
     */
    struct ScreenInfo {
        float w;         ///< Effectieve breedte na aspect ratio correctie
        float h;         ///< Effectieve hoogte na aspect ratio correctie
        bool heightFlag; ///< Indicator welke dimensie bepalend is voor schaling
        float rectSize;  ///< Grootte van rechthoek eenheden in scherm pixels
    };

    /**
     * @brief Berekent scherm informatie op basis van venster grootte
     * @param windowWidth Huidige venster breedte in pixels
     * @param windowHeight Huidige venster hoogte in pixels
     * @return ScreenInfo structuur met berekende scherm parameters
     *
     * Berekent aspect ratio correctie en schaling voor het weergeven
     * van de game wereld in het venster.
     */
    ScreenInfo getScreenInfo(float windowWidth, float windowHeight) const;

    /**
     * @brief Normaliseert wereld coördinaten naar scherm positie
     * @param x X-coördinaat in wereld ruimte
     * @param y Y-coördinaat in wereld ruimte
     * @param windowWidth Venster breedte in pixels
     * @param windowHeight Venster hoogte in pixels
     * @param heightFlag Indicator voor schaal dimensie
     * @param h Effectieve hoogte na correctie
     * @param w Effectieve breedte na correctie
     * @return SFML Vector2f met scherm coördinaten
     *
     * Statische methode voor conversie van wereld naar scherm coördinaten.
     */
    static sf::Vector2f normalizeToScreen(float x, float y, float windowWidth, float windowHeight, bool heightFlag,
                                          float h, float w);

    /**
     * @brief Converteert wereld coördinaten naar scherm coördinaten
     * @param x X-coördinaat in wereld ruimte
     * @param y Y-coördinaat in wereld ruimte
     * @param info ScreenInfo structuur met scherm parameters
     * @param windowWidth Venster breedte in pixels
     * @param windowHeight Venster hoogte in pixels
     * @return SFML Vector2f met scherm coördinaten
     *
     * Convenience methode die ScreenInfo gebruikt voor transformatie.
     */
    static sf::Vector2f worldToScreen(float x, float y, const ScreenInfo& info, float windowWidth, float windowHeight);
};

#endif // CAMERA_H
