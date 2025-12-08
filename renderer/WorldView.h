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
    int lastLives = 0;
    int round = 0;
    PacmanView pacmanview;
    RedGhostView redGhostview;
    PinkGhostView pinkghostview;
    BlueGhostView blueghostview;
    FearGhostView fearghostview;
    std::map<const Ghost*, std::unique_ptr<GhostView>> ghostViews;

public:

    void clearCache() {
        ghostViews.clear();
    }
    void render(const World& world, sf::RenderWindow& window, float windowWidth, float windowHeight);
};



#endif //WORLDVIEW_H
