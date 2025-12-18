/**
* @file WorldView.h
 * @brief Definieert de view klasse voor World rendering en coördinatie
 * @author Siebe Haché
 * @date 15/10/2025
 */

#ifndef WORLDVIEW_H
#define WORLDVIEW_H

#include "../ConcreteFactory.h"
#include "../logic/World.h"
#include "Camera.h"
#include "GhostView.h"
#include "PacmanView.h"
#include <memory>

/**
 * @class WorldView
 * @brief Hoofdview klasse die de volledige spelwereld rendert
 *
 * Coördineert het renderen van alle entiteiten in de spelwereld.
 * Beheert de camera, factory voor view creatie en houdt spelstatus bij
 * zoals levens en ronde nummer. Fungeert als centrale rendering manager.
 */
class WorldView {
private:
  ConcreteFactory* factory = nullptr;  ///< Factory voor het creëren van entity views
  int lastLives = 0;                   ///< Aantal levens in vorige frame (voor change detection)
  int round = 0;                       ///< Huidige ronde/level nummer

public:
  /**
   * @brief Destructor voor WorldView cleanup
   */
  ~WorldView() = default;

  /**
   * @brief Rendert de volledige spelwereld naar het venster
   * @param world Gedeelde pointer naar de World die gerenderd moet worden
   * @param window Gedeelde pointer naar het SFML render venster
   * @param windowWidth Breedte van het render venster in pixels
   * @param windowHeight Hoogte van het render venster in pixels
   *
   * Statische methode die alle entiteiten in de wereld rendert met
   * correcte camera transformatie en viewport instellingen.
   */
  static void render(const std::shared_ptr<World>& world, const std::shared_ptr<sf::RenderWindow>& window,
                     float windowWidth, float windowHeight);
};

#endif // WORLDVIEW_H