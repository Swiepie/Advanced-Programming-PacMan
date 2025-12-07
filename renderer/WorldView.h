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
struct ViewCreatorVisitor : public Visitor {
    std::unique_ptr<GhostView> view;

    void visit(RedGhost& g) override { view = std::make_unique<RedGhostView>(); }
    void visit(BlueGhost& g) override { view = std::make_unique<BlueGhostView>(); }
    void visit(PinkGhost& g) override { view = std::make_unique<PinkGhostView>(); }
    void visit(Wall& w) override {}
    void visit(Coin& c) override {}
    void visit(Fruit& f) override {}
    void visit(Pacman& p) override {}
};


class WorldView {
    private:
    PacmanView pacmanview;
    RedGhostView redGhostview;
    PinkGhostView pinkghostview;
    BlueGhostView blueghostview;
    FearGhostView fearghostview;
    std::map<const Ghost*, std::unique_ptr<GhostView>> ghostViews;

public:


    void render(const World& world, sf::RenderWindow& window, float windowWidth, float windowHeight);
};



#endif //WORLDVIEW_H
