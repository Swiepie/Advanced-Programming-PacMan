//
// Created by Siebe Haché on 15/10/2025.
//

#ifndef WORLDVIEW_H
#define WORLDVIEW_H




#include "../World.h"
#include "PacmanView.h"
#include "GhostView.h"
#include <memory>
#include "RenderVisitor.h"



class WorldView {
    private:
    DefaultEntityFactory*factory = nullptr;
    int lastLives = 0;
    int round = 0;


    // Deze views haal je al op via world.getPacman()->getObserver() in WorldView::render.
    // Je hebt ze waarschijnlijk NIET nodig als member variabelen hier.
    // De fout is opgelost door ze te verwijderen of er pointers van te maken:

    // DefaultEntityFactory*factory = nullptr; // Onnodig in WorldView?
    // int lastLives = 0; // Prima
    // int round = 0; // Prima

    /* VERWIJDER DEZE:
    PacmanView pacmanview;
    RedGhostView redGhostview;
    PinkGhostView pinkghostview;
    BlueGhostView blueghostview;
    FearGhostView fearghostview;
    */

    // OF, als je ze echt hier wilt bewaren, maak er Pointers van:
    // PacmanView* pacmanview = nullptr;
    // RedGhostView* redGhostview = nullptr;
    // PinkGhostView* pinkghostview = nullptr;
    // BlueGhostView* blueghostview = nullptr;

    std::map<const Ghost*, std::unique_ptr<GhostView>> ghostViews; // Deze is prima

public:

    void clearCache() {
        ghostViews.clear();
    }
    void render(const World& world, sf::RenderWindow& window, float windowWidth, float windowHeight);
};



#endif //WORLDVIEW_H
