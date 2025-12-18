/**
   * @file Visitor.h
   * @brief Definieert visitor patroon implementaties voor entiteit interacties in het pacman spel
   * @author siebe
   * @date 04/12/2025
   */
  
  #ifndef VISITOR_H
  #define VISITOR_H
  
  #include "entities/Entity.h"
  class Wall;
  class Coin;
  class Fruit;
  class Pacman;
  class Ghost;
  class RedGhost;
  class BlueGhost;
  class PinkGhost;
  class World;
  class Entity;
  #include "World.h"
  #include <vector>
  
  /**
   * @class Visitor
   * @brief Abstracte basisklasse voor visitor patroon implementatie
   *
   * Biedt interface voor het bezoeken van verschillende entiteitstypes in de world.
   * Implementeert het Visitor ontwerppatroon voor polymorfische entiteit interacties.
   */
  class Visitor {
  public:
      virtual ~Visitor() = default;
  
      virtual void visit(Wall& wall) = 0;           ///< Bezoek een muur entity
      virtual void visit(Coin& coin) = 0;           ///< Bezoek een munt entity
      virtual void visit(Fruit& fruit) = 0;         ///< Bezoek een fruit entity
      virtual void visit(Pacman& pacman) = 0;       ///< Bezoek pacman entity
      virtual void visit(RedGhost& ghost) = 0;      ///< Bezoek rode ghost entity
      virtual void visit(BlueGhost& ghost) = 0;     ///< Bezoek blauwe ghost entity
      virtual void visit(PinkGhost& ghost) = 0;     ///< Bezoek roze ghost entity
  };
  
  /**
   * @class CollectibleVisitor
   * @brief Behandelt het verzamelen van items door pacman
   *
   * Detecteert wanneer pacman coins of fruit verzamelt en beheert
   * het verwijderen van de collectibles uit de wereld.
   */
  class CollectibleVisitor : public Visitor {
  private:
      std::shared_ptr<Pacman> pacman;      ///< Referentie naar pacman entity
      World* world;                         ///< Pointer naar world
      float stepW, stepH;                   ///< Tegel afmetingen voor botsingsdetectie
      std::vector<Entity*> toRemove;        ///< Entiteiten gemarkeerd voor verwijdering
  
  public:
      /**
       * @brief Construeert een CollectibleVisitor
       * @param pacman Shared pointer naar pacman entity
       * @param w Pointer naar de world
       * @param tileWidth Breedte van een enkele tile
       * @param tileHeight Hoogte van een enkele tile
       */
      CollectibleVisitor(std::shared_ptr<Pacman> pacman, World* w, float tileWidth, float tileHeight);
  
      void visit(Wall& wall) override;
      void visit(Coin& coin) override;
      void visit(Fruit& fruit) override;
      void visit(Pacman& p) override;
      void visit(RedGhost& ghost) override;
      void visit(BlueGhost& ghost) override;
      void visit(PinkGhost& ghost) override;
  
      /**
       * @brief Geeft de lijst van te verwijderen entiteiten
       * @return Const referentie naar vector van entiteiten gemarkeerd voor verwijdering
       */
      const std::vector<Entity*>& getToRemove() const;
  };
  
  /**
   * @class GhostCollisionVisitor
   * @brief Behandelt collision tussen pacman en spoken
   *
   * Detecteert botsingen tussen pacman en spoken, behandelt zowel
   * pacman dood als ghost consumptie gebaseerd op spelstatus.
   */
  class GhostCollisionVisitor : public Visitor {
  private:
      std::shared_ptr<Pacman> pacman;      ///< Referentie naar pacman entity
      World* world;                         ///< Pointer naar world, raw want deze class bestaat heel kort
      float stepW, stepH;                   ///< Tegel afmetingen voor botsingsdetectie
      bool pacmanDied;                      ///< flag die aangeeft of pacman gestorven is bij botsing
      bool ghostEaten;                      ///< flag die aangeeft of een ghost gegeten is
  
      /**
       * @brief Behandelt botsingslogica tussen pacman en een ghost
       * @param ghost Spook entity betrokken bij botsing
       */
      void handleGhostCollision(Ghost& ghost);
  
  public:
      /**
       * @brief Construeert een GhostCollisionVisitor
       * @param pacman Shared pointer naar pacman entity
       * @param w Pointer naar de world
       * @param tileWidth Breedte van een enkele tile
       * @param tileHeight Hoogte van een enkele tile
       */
      GhostCollisionVisitor(std::shared_ptr<Pacman> pacman, World* w, float tileWidth, float tileHeight);
  
      void visit(Wall& wall) override;
      void visit(Coin& coin) override;
      void visit(Fruit& fruit) override;
      void visit(Pacman& p) override;
      void visit(RedGhost& ghost) override;
      void visit(BlueGhost& ghost) override;
      void visit(PinkGhost& ghost) override;
  
      /**
       * @brief Controleert of pacman gestorven is tijdens botsingscontrole
       * @return True als pacman gestorven is, false anders
       */
      bool didPacmanDie() const;
  
      /**
       * @brief Controleert of een ghost gegeten is tijdens botsingscontrole
       * @return True als ghost gegeten is, false anders
       */
      bool wasGhostEaten() const;
  };
  
  /**
   * @class CollisionDetectionVisitor
   * @brief Detecteert botsingen op specifieke coördinaten
   *
   * Controleert of een gegeven positie zou resulteren in een botsing met muren,
   * gebruikt voor bewegingsvalidatie.
   */
  class CollisionDetectionVisitor : public Visitor {
  private:
      float checkX, checkY;                 ///< Coördinaten om te controleren op botsing
      float stepW, stepH;                   ///< Tegel afmetingen
      bool collisionDetected;               ///< flag die botsingsdetectie aangeeft
      const float COLLISION_MARGIN = 0.965f; ///< Marge voor botsingsdetectie
  
  public:
      /**
       * @brief Construeert een CollisionDetectionVisitor
       * @param x X-coördinaat om te controleren
       * @param y Y-coördinaat om te controleren
       * @param tileWidth Breedte van een enkele tile
       * @param tileHeight Hoogte van een enkele tile
       */
      CollisionDetectionVisitor(float x, float y, float tileWidth, float tileHeight);
  
      void visit(Wall& wall) override;
      void visit(Coin& coin) override;
      void visit(Fruit& fruit) override;
      void visit(Pacman& pacman) override;
      void visit(RedGhost& ghost) override;
      void visit(BlueGhost& ghost) override;
      void visit(PinkGhost& ghost) override;
  
      /**
       * @brief Controleert of botsing gedetecteerd is
       * @return True als botsing gedetecteerd, false anders
       */
      bool hasCollision() const;
  };
  
  /**
   * @class DeathVisitor
   * @brief Behandelt entiteitsgedrag wanneer pacman sterft
   *
   * Reset spoken naar hun initiële posities wanneer pacman een leven verliest.
   */
  class DeathVisitor : public Visitor {
  private:
      World* world;           ///< Pointer naar world deze is raw omdat deze class zo kort bestaat.
      float currentTime;      ///< Huidige speltijd
  
  public:
      /**
       * @brief Construeert een DeathVisitor
       * @param w Pointer naar de world
       * @param curTime Huidige speltijd
       */
      DeathVisitor(World* w, float curTime) : world(w), currentTime(curTime) {}
  
      void visit(Wall& wall) override;
      void visit(Coin& coin) override;
      void visit(Fruit& fruit) override;
      void visit(Pacman& pacman) override;
      void visit(RedGhost& ghost) override;
      void visit(BlueGhost& ghost) override;
      void visit(PinkGhost& ghost) override;
  
  private:
      /**
       * @brief Reset een ghost naar zijn initiële staat
       * @param ghost Spook entity om te resetten
       */
      static auto resetGhost(Ghost& ghost) -> void;
  };
  
  #endif // VISITOR_H