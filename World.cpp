//
// Created by Siebe Haché on 14/10/2025.
//

#include "World.h"
#include <cmath>
bool World::loadMap(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open map file " << filename << std::endl;
        return false;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) lines.push_back(line);
    }

    int numRows = static_cast<int>(lines.size());
    int numCols = numRows > 0 ? static_cast<int>(lines[0].size()) : 0;
    width = numCols;
    height = numRows;

    if (numRows == 0 || numCols == 0) return false;

    float tileWidth  = 2.0f / numCols;
    float tileHeight = 2.0f / numRows;

    entities.clear();
    int i = 1;
    for (int row = 0; row < numRows; ++row) {
        for ( int col = 0; col < numCols; ++col) {
            char c = lines[row][col];

            float x = -1.0f + floor(col) * tileWidth;
            float y = -1.0f + floor(row) * tileHeight;
            switch (c) {
                case '#':
                    // voeg een loop toe die alle kruisunten vindt/bochten in een vector en maak dan een nieuwe functie die als een object op een kruisount komt en dicht genoeg bij het hoekpunt is er gewoon naartoe teleporten, maar enkel als er al een input buffer is ingevoerd om af de road te gaan.
                    entities.push_back(std::make_unique<Wall>(x, y));
                break;
                case '0':
                    entities.push_back(std::make_unique<Coin>(x, y));
                    coinCount = coinCount + 1;
                break;
                case 'P':{
                    auto p = std::make_unique<Pacman>(x, y);
                    pacman = p.get();
                    p->setSpawn(x, y);
                    entities.push_back(std::move(p));

                    break;
                }
                case 'f':

                    entities.push_back(std::make_unique<Fruit>(x, y));
                    coinCount = coinCount + 1;
                break;
                case 'G':{

                    if (i == 1) {
                        auto g = std::make_unique<RedGhost>(x, y);
                        g->setSpawn(x, y);
                        ghostSpawnPositions.push_back({x, y});
                        entities.push_back(std::move(g));
                        i = i+1;
                        break;
                    }
                    if (i==2) {
                        auto g = std::make_unique<BlueGhost>(x, y, 0.0f);
                        g->setSpawn(x, y);
                        ghostSpawnPositions.push_back({x, y});
                        entities.push_back(std::move(g));
                        i = i+1;
                        break;
                    }
                    if (i==3) {
                        auto g = std::make_unique<BlueGhost>(x, y, 5.0f);
                        g->setSpawn(x, y);
                        ghostSpawnPositions.push_back({x, y});
                        entities.push_back(std::move(g));
                        i = i+1;
                        break;
                    }
                    if (i==4) {
                        auto g = std::make_unique<PinkGhost>(x, y, 10.0f);
                        g->setSpawn(x, y);
                        ghostSpawnPositions.push_back({x, y});
                        entities.push_back(std::move(g));
                        i = i+1;
                    }
                    break;

                }
                default:
                    break;
            }
        }
    }
    return true;
}

void World::printMap() const {
    for (const auto& row : mapData)
        std::cout << row << "\n";
    std::cout << "Map size: " << width << "x" << height << std::endl;
}

void World::update(float deltaTime) {
    totTime += deltaTime;
    deltaT = deltaTime;
    if (death && totTime < deathTime + respawnTimer) {
        return;
    }
    if (death && totTime > deathTime + respawnTimer ) {
        death = false;
    }
    for (auto& e : entities) {
        e->update(deltaTime, *this, *pacman);
    }
    if (fearmode) {
        if (fearmodeTimer + fearmodeStart <= totTime) {
            fearmode = false;

            // **reset fear status for all ghosts**
            for (auto& e : entities) {
                e->resetFearState();
                e->softSnapToTileCenter(*this);
                e->setHasBeenEaten(false); // reset eaten state when fear ends

            }
            std::cout << "Fear mode ended" << std::endl;
        }
    }

    //is het al tijd om opnieuw te bewegen?
        char buffered = pacman->getBufferdirection();
        bool moved = false;

        if (tryMove(pacman, buffered)) {
            pacman->applyBufferdirection();
            moved = true;
        } else {
            char current = pacman->getDirection();
            if (tryMove(pacman, current)) {
                moved = true;
            }
        }

        if (moved) {
            //slaag de tijd op van laatste movement
            checkCollisions();
        }

}

const std::vector<std::unique_ptr<Entity>>& World::getEntities() const {
    return entities;
}
int World::getWidth() const {
    return width;
}
int World::getHeight() const {
    return height;
}
Pacman* World::getPacman() const{
    return pacman;
}

bool World::tryMove(Pacman* pacman, char dir) const {
    if (!pacman) return false;
    float speed = pacman->getSpeed();
    float cd = deltaT;
    float dx = 0, dy = 0;
    switch (dir) {
        case 'N': dy = -1*speed*cd; break;
        case 'Z': dy = 1*speed*cd;  break;
        case 'W': dx = -1*speed*cd; break;
        case 'O': dx = 1*speed*cd;  break;
        default: return false;
    }

    float stepW = 2.0f / width;
    float stepH = 2.0f / height;
    float newX = pacman->getPosition().x + dx * stepW;
    float newY = pacman->getPosition().y + dy * stepH;

    // Constante collision marge
    const float COLLISION_MARGIN = 0.980f - deltaT;

    for (auto& wall : entities) {
        if (wall->getSymbol() == '#') {
            float wallX = wall->getPosition().x;
            float wallY = wall->getPosition().y;

            float distX = std::fabs(newX - wallX);
            float distY = std::fabs(newY - wallY);

            bool overlapX = distX < stepW * COLLISION_MARGIN;
            bool overlapY = distY < stepH * COLLISION_MARGIN;

            if (overlapX && overlapY)
                return false; // geblokkeerd
        }
    }

    const float SNAP_THRESHOLD = 0.65f;

    if (std::fabs(dx) > 0.001f) { // Horizontale beweging
        // Snap Y naar dichtstbijzijnde grid lijn
        float gridY = std::round((newY + 1.0f) / stepH) * stepH - 1.0f;
        if (std::fabs(newY - gridY) < stepH * SNAP_THRESHOLD) {
            newY = gridY;
        }
    }

    if (std::fabs(dy) > 0.001f) { // Verticale beweging
        // Snap X naar dichtstbijzijnde grid lijn
        float gridX = std::round((newX + 1.0f) / stepW) * stepW - 1.0f;
        if (std::fabs(newX - gridX) < stepW * SNAP_THRESHOLD) {
            newX = gridX;
        }
    }

    pacman->setPosition(newX, newY);
    return true;
}

void World::checkCollisions() {
    if (!pacman) return;
    bool ateGhostThisFrame = false;

    // --- Collectibles Removal Loop ---
    entities.erase(
        std::remove_if(entities.begin(), entities.end(),
            [&](const std::unique_ptr<Entity>& e) {
                // Check collision only for collectibles
                if (e->isCollectible() && pacman->collidesWith(*e, 2.0f / width * 0.5f, 2.0f / height * 0.5f)) {
                    e->onCollect(*this);
                    return true; // Remove collectible
                }
                // Don't check ghost collision here, return false for all others
                return false;
            }),
        entities.end()
    );

    // --- Ghost Collision/Eating Loop ---
    for (auto& e : entities) {
        char eSym = e->getSymbol();
        // Check collision only for ghosts
        if ((eSym == 'G' || eSym == 'R' || eSym == 'B') && pacman->collidesWith(*e, 2.0f / width * 0.5f, 2.0f / height * 0.5f)) {

            // Ghost Eating Logic
            if (fearmode && e->getFearState() && !e->getHasBeenEaten() && !ateGhostThisFrame) {

                int ghostIndex = Random::getInstance().getInt(0, 3);
                e->setPosition(ghostSpawnPositions[ghostIndex].x, ghostSpawnPositions[ghostIndex].y);

                // Reset state AFTER teleporting
                e->resetFearState();
                e->setHasBeenEaten(true);

                increaseScore(200); // Score increase
                ateGhostThisFrame = true; // Prevents eating another ghost this frame
                // You can add logic here to ensure the score multiplier increases for subsequent ghosts if desired.

            } //halloooo - Marie :)
            // Pacman Dies Logic
            else if (!fearmode || e->getHasBeenEaten()) {
                pacmanlives = pacmanlives - 1;
                resetAfterDeath();
                std::cout << "Lives: " << pacmanlives << std::endl;
            }
        }
    }
}

bool World::tryMoveGhost(Ghost* ghost, char dir) const {
    if (!ghost) return false;

    float speed = ghost->getSpeed();
    float cd = deltaT;

    // **MIN STAP LOGICA (uit vorige fix)**
    const float MIN_MOVE_FACTOR = 0.005f;
    float moveFactor = speed * cd;

    if (moveFactor < MIN_MOVE_FACTOR) {
        moveFactor = MIN_MOVE_FACTOR;
    }

    float dx = 0, dy = 0;
    switch (dir) {
        case 'N': dy = -1 * moveFactor; break;
        case 'Z': dy =  1 * moveFactor; break;
        case 'W': dx = -1 * moveFactor; break;
        case 'O': dx =  1 * moveFactor; break;
        default: return false;
    }

    float stepW = 2.0f / width;
    float stepH = 2.0f / height;
    float newX = ghost->getPosition().x + dx * stepW;
    float newY = ghost->getPosition().y + dy * stepH;

    // ✅ COLLISION DETECTION MET DYNAMISCHE MARGE
    float COLLISION_MARGIN = 0.980f - bfr; // Vaste basis marge
    if (ghost->getFearState() == true) {
        COLLISION_MARGIN = 0.980f;
    }


    for (auto& wall : entities) {
        if (wall->getSymbol() == '#') {
            float wallX = wall->getPosition().x;
            float wallY = wall->getPosition().y;

            float distX = std::fabs(newX - wallX);
            float distY = std::fabs(newY - wallY);

            // Gebruik de dynamische marge (collisionFactorX/Y)
            bool overlapX = distX < stepW * COLLISION_MARGIN;
            bool overlapY = distY < stepH * COLLISION_MARGIN;

            if (overlapX && overlapY)
                return false; // Geblokkeerd door muur!
        }
    }

    // Grid snap logica
    const float SNAP_THRESHOLD = 0.15f;

    if (std::fabs(dx) > 0.001f) { // Horizontale beweging
        float gridY = std::round((newY + 1.0f) / stepH) * stepH - 1.0f;
        if (std::fabs(newY - gridY) < stepH * SNAP_THRESHOLD) {
            newY = gridY;
        }
    }

    if (std::fabs(dy) > 0.001f) { // Verticale beweging
        float gridX = std::round((newX + 1.0f) / stepW) * stepW - 1.0f;
        if (std::fabs(newX - gridX) < stepH * SNAP_THRESHOLD) {
            newX = gridX;
        }
    }

    ghost->setPosition(newX, newY);
    return true;
}

bool World::canMoveInDirection(const Ghost* ghost, char dir) const {
    if (!ghost) return false;

    // Simuleer de *exacte* volgende zet die tryMoveGhost zou doen

    float speed = ghost->getSpeed();
    float cd = deltaT; // Gebruik de global deltaT

    // **MIN STAP LOGICA (uit vorige fix)**
    const float MIN_MOVE_FACTOR = 0.005f;
    float moveFactor = speed * cd;

    if (moveFactor < MIN_MOVE_FACTOR) {
        moveFactor = MIN_MOVE_FACTOR;
    }

    float dx = 0, dy = 0;
    switch (dir) {
        case 'N': dy = -1 * moveFactor; break;
        case 'Z': dy =  1 * moveFactor; break;
        case 'W': dx = -1 * moveFactor; break;
        case 'O': dx =  1 * moveFactor; break;
        default: return false;
    }

    float stepW = 2.0f / width;
    float stepH = 2.0f / height;
    float newX = ghost->getPosition().x + dx * stepW;
    float newY = ghost->getPosition().y + dy * stepH;

    // Gebruik *exact* dezelfde botsingslogica als tryMoveGhost (inclusief dynamische marge)
    float COLLISION_MARGIN = 0.980f - bfr; // Vaste basis marge
    if (ghost->getFearState() == true) {
        COLLISION_MARGIN = 0.980f;
    }

    for (auto& wall : entities) {
        if (wall->getSymbol() == '#') {
            float wallX = wall->getPosition().x;
            float wallY = wall->getPosition().y;

            float distX = std::fabs(newX - wallX);
            float distY = std::fabs(newY - wallY);

            // Gebruik de dynamische marge
            bool overlapX = distX < stepW * COLLISION_MARGIN;
            bool overlapY = distY < stepH * COLLISION_MARGIN;

            if (overlapX && overlapY)
                return false; // Geblokkeerd
        }
    }
    return true; // Pad is vrij
}

bool World::isAtIntersection(const Ghost* g) const
{
    if (!g) return false;

    // **DE FIX:** Een spook kan alleen op een kruispunt zijn
    // als het zich op een tegel-knooppunt (grid corner) bevindt.
    if (!isOnTileCenter(g)) {
        return false;
    }

    char currentDir = g->getDirection();
    int viableMoves = 0;
    int perpendicularMoves = 0;

    // Count viable moves
    for (char d : {'N', 'Z', 'W', 'O'}) {
        if (canMoveInDirection(g, d)) {
            viableMoves++;


            bool perpendicular = false;
            if ((currentDir == 'N' || currentDir == 'Z') && (d == 'W' || d == 'O')) {
                perpendicular = true;
            } else if ((currentDir == 'W' || currentDir == 'O') && (d == 'N' || d == 'Z')) {
                perpendicular = true;
            }

            if (perpendicular) {
                perpendicularMoves++;
            }
        }
    }
    // - A T-junction: 3 viable moves
    // - A crossroads: 4 viable moves
    if (viableMoves >= 3) {
        // T-junction or crossroads
        return true;
    }

    if (viableMoves == 2 && perpendicularMoves > 0) {
        // Corner turn - only count if we can't continue straight
        char oppositeDir;
        switch (currentDir) {
            case 'N': oppositeDir = 'Z'; break;
            case 'Z': oppositeDir = 'N'; break;
            case 'W': oppositeDir = 'O'; break;
            case 'O': oppositeDir = 'W'; break;
            default: return false;
        }

        // It's a corner if we can't continue forward
        if (!canMoveInDirection(g, currentDir)) {
            return true;
        }
    }

    return false;
}


bool World::isAtDeadEnd(const Ghost* ghost) const {
    if (!ghost) return false;

    // **DE FIX:** Check ook hier of we op een knooppunt zijn
    if (!isOnTileCenter(ghost)) {
        return false;
    }

    char currentDir = ghost->getDirection();
    int viableMoves = 0;
    int perpendicularMoves = 0;

    for (char d : {'N', 'Z', 'W', 'O'}) {
        if (canMoveInDirection(ghost, d)) {
            viableMoves++;

            // Check if this is perpendicular to current direction
            bool perpendicular = false;
            if ((currentDir == 'N' || currentDir == 'Z') && (d == 'W' || d == 'O')) {
                perpendicular = true;
            } else if ((currentDir == 'W' || currentDir == 'O') && (d == 'N' || d == 'Z')) {
                perpendicular = true;
            }

            if (perpendicular) {
                perpendicularMoves++;
            }
        }
    }
    // Intersection if:
    // - More than 2 viable moves (T-junction or crossroads), OR
    // - Exactly 2 viable moves with at least one perpendicular option (corner)
    return (viableMoves == 1);
}


void World::setFearMode(bool fearm) {
    for (auto& e : entities) {
        e->setFearState(fearm);
    }
    fearmode = fearm;
}
bool World::getFearMode() {
    return fearmode;
}
float World::getFearModeTimer() const {
    return fearmodeTimer;
}
void World::setFearModeTimer(float timer) {
    fearmodeTimer = timer;
}
void World::setFearModeStart(float timer) {
    fearmodeStart = timer;
}
void World::increaseScore(int points) {
    score += points;
}
int World::getPacmanLives() const{
    return pacmanlives;
}
int World::getScore() const {
    return score;
}

bool World::isOnTileCenter(const Entity* e) const {
    float stepW = 2.f / width;
    float stepH = 2.f / height;

    float x = e->getPosition().x;
    float y = e->getPosition().y;

    // **AANGEPAST:** Bereken dichtstbijzijnde knooppunt (grid-hoek)
    // rekening houdend met de -1.0f offset
    float centerX = std::round((x + 1.0f) / stepW) * stepW - 1.0f;
    float centerY = std::round((y + 1.0f) / stepH) * stepH - 1.0f;

    float dx = std::fabs(centerX - x);
    float dy = std::fabs(centerY - y);

    // **AANGEPAST:** Gebruik een kleine *relatieve* marge, geen harde 0.0001
    // Dit moet kleiner zijn dan de SNAP_THRESHOLD in tryMove.
    float snapMargin = 0.01f; // 1% van een tile
    return (dx < stepW * snapMargin && dy < stepH * snapMargin);
}



float World::getTime() const {
    return totTime;
}

void World::decreaseCoins() {
    coinCount = coinCount - 1;
    std::cout << "coinCount: " << coinCount << std::endl;
}

void World::resetAfterDeath() {
    if (!pacman) return;

    // 1) Respawn Pacman — snap naar tile-corner / top-left
    deathTime = totTime;
    death = true;
    pacman->resetToSpawn();                       // zet op spawn coords

    // 2) Clear input/buffer and freeze briefly
    pacman->setBufferdirection(' ');    // clear buffered input
    pacman->setDirection(' ');          // geen richting


    // 3) Reset ghosts: teleport naar spawn en reset timers / fear state
    for (auto& e : entities) {
        char s = e->getSymbol();
        if (s == 'G' || s == 'R' || s == 'B') {
            e->resetFearState();
            e->setHasBeenEaten(false);
            // verplaats naar eigen spawn (zorg dat elke ghost spawn bewaard is)
            e->resetToSpawn();        // moet door Ghost/Entity ondersteund worden
            // reset timer zodat ze opnieuw hun start delay gebruiken:
            // als je Ghost een timeAlive of lastMoveTime heeft, zet het hier:
            // voorkomt dat ze direct bewegen
            // als je specifieke chaseDelay etc. gebruikt, zorg dat die teruggezet worden
        }
    }

    // 4) Zorg dat fearmode uit staat
    fearmode = false;

    fearmodeStart = 0.f;
}
//zorg ervoor dat pacm pacman een constantte stapeenhijd vindt om van tile center naar tile canter te gaan met de snelheid, dit kan adhv modulo, of nog andere dingen.
//doe dit ook voor de ghosts; zonder det het er glithcy uitziet.