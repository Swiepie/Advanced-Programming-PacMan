//
// Created by Siebe Haché on 14/10/2025.
//

#include "World.h"
#include <cmath>
bool World::loadMap(const std::string& filename) {
    if (!factory) {
        std::cerr << "Error: No EntityFactory set in World." << std::endl;
        return false;
    }

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

    // Clear all vectors
    walls.clear();
    collectibles.clear();
    ghosts.clear();
    ghostSpawnPositions.clear();
    coinCount = 0;

    int ghostCounter = 1;

    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            char c = lines[row][col];

            float x = -1.0f + floor(col) * tileWidth;
            float y = -1.0f + floor(row) * tileHeight;

            switch (c) {
                case '#':
                    walls.push_back(factory->createWall(x, y));
                    break;

                case '0':
                    collectibles.push_back(factory->createCoin(x, y));
                    coinCount++;
                    break;

                case 'P': {
                    auto p = factory->createPacman(x, y);
                    pacman = p.get();
                    p->setSpawn(x, y);
                    pacmanPtr = std::move(p);
                    break;
                }

                case 'f':
                    collectibles.push_back(factory->createFruit(x, y));
                    coinCount++;
                    break;

                case 'G': {
                    if (ghostCounter == 1) {
                        auto g = factory->createRedGhost(x, y);
                        g->setSpawn(x, y);
                        ghostSpawnPositions.push_back({x, y});
                        ghosts.push_back(std::move(g));
                    }
                    else if (ghostCounter == 2) {
                        auto g = factory->createBlueGhost(x, y, 0.0f);
                        g->setSpawn(x, y);
                        ghostSpawnPositions.push_back({x, y});
                        ghosts.push_back(std::move(g));
                    }
                    else if (ghostCounter == 3) {
                        auto g = factory->createBlueGhost(x, y, 5.0f);
                        g->setSpawn(x, y);
                        ghostSpawnPositions.push_back({x, y});
                        ghosts.push_back(std::move(g));
                    }
                    else if (ghostCounter == 4) {
                        auto g = factory->createPinkGhost(x, y, 10.0f);
                        g->setSpawn(x, y);
                        ghostSpawnPositions.push_back({x, y});
                        ghosts.push_back(std::move(g));
                    }
                    ghostCounter++;
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
    if (dies && totTime < diesTime + respawnTimer) {
        pacman->setDirection('D');
        return;
    }
    if (dies && totTime > diesTime + respawnTimer) {
        dies = false;
        resetAfterDeath();
    }

    if (death && totTime < deathTime + respawnTimer) {
        return;
    }
    if (death && totTime > deathTime + respawnTimer ) {
        death = false;
    }
    if (reset) {
        if (!(fearmodeTimer == 2)) {
            fearmodeTimer = fearmodeTimer - 0.5f;
        }
        for (auto& g : ghosts) {
            g->setSpeed(g->getSpeed() + 0.5 * rounds);
        }

        pacman->setSpeed(4);
        reset = false;
    }
    for (auto& g : ghosts) {
        g->update(deltaTime, *this, *pacman  );
    }
    if (pacmanPtr) {
        pacmanPtr->update(deltaTime);
    }
    if (fearmode) {
        if (fearmodeTimer + fearmodeStart <= totTime) {
            fearmode = false;

            // **reset fear status for all ghosts**
            for (auto& g : ghosts) {
                std::cout <<"ghost speed: " << g->getSpeed() << "\n";
                g->resetFearState();
                g->softSnapToTileCenter(*this);
                g->setHasBeenEaten(false);
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

const std::vector<std::unique_ptr<Wall>>& World::getWalls() const {
    return walls;
}

const std::vector<std::unique_ptr<Entity>>& World::getCollectibles() const {
    return collectibles;
}

const std::vector<std::unique_ptr<Ghost>>& World::getGhosts() const {
    return ghosts;
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
    CollisionDetectionVisitor collisionVisitor(newX, newY, stepW, stepH);
    for (auto& wall : walls) {
        wall->accept(collisionVisitor);
        if (collisionVisitor.hasCollision()) {
            return false;
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

    float stepW = 2.0f / width;
    float stepH = 2.0f / height;

    // Check collectibles
    CollectibleVisitor collectibleVisitor(pacman, this, stepW, stepH);
    for (auto& collectible : collectibles) {
        collectible->accept(collectibleVisitor);
    }

    // Remove collected items
    const auto& toRemove = collectibleVisitor.getToRemove();
    collectibles.erase(
        std::remove_if(collectibles.begin(), collectibles.end(),
            [&toRemove](const std::unique_ptr<Entity>& e) {
                return std::find(toRemove.begin(), toRemove.end(), e.get()) != toRemove.end();
            }),
        collectibles.end()
    );

    // Check ghost collisions
    GhostCollisionVisitor ghostVisitor(pacman, this, stepW, stepH);
    for (auto& ghost : ghosts) {
        ghost->accept(ghostVisitor);
    }

    if (ghostVisitor.didPacmanDie()) {
        if (!dies) {
            pacmanlives--;
            dies = true;
            diesTime = totTime;
            std::cout << "Lives: " << pacmanlives << std::endl;
        }
        return;
    }
}

bool World::tryMoveGhost(Ghost* ghost, char dir) const {
    if (!ghost) return false;

    float speed = ghost->getSpeed();
    float cd = deltaT;
    float dx = 0, dy = 0;

    switch (dir) {
        case 'N': dy = -1 * speed * cd; break;
        case 'Z': dy = 1 * speed * cd; break;
        case 'W': dx = -1 * speed * cd; break;
        case 'O': dx = 1 * speed * cd; break;
        default: return false;
    }

    float stepW = 2.0f / width;
    float stepH = 2.0f / height;
    float newX = ghost->getPosition().x + dx * stepW;
    float newY = ghost->getPosition().y + dy * stepH;

    const float COLLISION_MARGIN = 0.965f;

    for (auto& wall : walls) {
        float wallX = wall->getPosition().x;
        float wallY = wall->getPosition().y;
        float distX = std::fabs(newX - wallX);
        float distY = std::fabs(newY - wallY);
        bool overlapX = distX < stepW * COLLISION_MARGIN;
        bool overlapY = distY < stepH * COLLISION_MARGIN;

        if (overlapX && overlapY) {
            // ✅ COLLISION - Don't update anything
            return false;
        }
    }

    const float SNAP_THRESHOLD = 0.15f;

    if (std::fabs(dx) > 0.001f) {
        float gridY = std::round((newY + 1.0f) / stepH) * stepH - 1.0f;
        if (std::fabs(newY - gridY) < stepH * SNAP_THRESHOLD) {
            newY = gridY;
        }
    }

    if (std::fabs(dy) > 0.001f) {
        float gridX = std::round((newX + 1.0f) / stepW) * stepW - 1.0f;
        if (std::fabs(newX - gridX) < stepW * SNAP_THRESHOLD) {
            newX = gridX;
        }
    }

    // ✅ SUCCESS - Update position AND ensure direction matches
    ghost->setPosition(newX, newY);
    ghost->setDirection(dir);

    return true;
}


bool World::canMoveInDirection(const Ghost* ghost, char dir) const {
    if (!ghost) return false;
    float stepW = 2.0f / width;
    float stepH = 2.0f / height;

    float dx = 0, dy = 0;
    switch (dir) {
        case 'N': dy = -0.05; break;
        case 'Z': dy =  0.05; break;
        case 'W': dx = -0.05; break;
        case 'O': dx =  0.05; break;
        default: return false;
    }

    // ✅ CORNER CUTTING: Use ghost's actual position OR snapped position for checking
    float checkX = ghost->getPosition().x;
    float checkY = ghost->getPosition().y;

    char currentDir = ghost->getDirection();
    bool changingDirection = (currentDir != dir);

    if (changingDirection) {
        const float CORNER_CUT_THRESHOLD = 0.05f;

        // If checking horizontal move, use snapped Y
        if (dir == 'W' || dir == 'O') {
            float gridY = std::round((checkY + 1.0f) / stepH) * stepH - 1.0f;
            if (std::fabs(checkY - gridY) < stepH * CORNER_CUT_THRESHOLD) {
                checkY = gridY;
            }
        }

        // If checking vertical move, use snapped X
        if (dir == 'N' || dir == 'Z') {
            float gridX = std::round((checkX + 1.0f) / stepW) * stepW - 1.0f;
            if (std::fabs(checkX - gridX) < stepW * CORNER_CUT_THRESHOLD) {
                checkX = gridX;
            }
        }
    }

    float newX = checkX + dx * stepW;
    float newY = checkY + dy * stepH;

    for (auto& wall : walls) {
        float wallX = wall->getPosition().x;
        float wallY = wall->getPosition().y;
        bool overlapX = std::fabs(newX - wallX) + 0.0001 < stepW;
        bool overlapY = std::fabs(newY - wallY) + 0.0001 < stepH;
        if (overlapX && overlapY)
            return false;
    }
    return true;
}

bool World::isAtIntersection(const Ghost* ghost) const {
    if (!ghost) return false;


    // **DE FIX:** Een spook kan alleen op een kruispunt zijn
    // als het zich op een tegel-knooppunt (grid corner) bevindt.
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
    return (viableMoves > 2) || (viableMoves >= 2 && perpendicularMoves > 0);
}


void World::setFearMode(bool fearm) {
    for (auto& g : ghosts) {
        g->setFearState(fearm);
    }
    fearmode = fearm;
}
bool World::getFearMode() const {
    return fearmode;
}
float World::getFearModeTimer() const {
    return fearmodeTimer;
}
void World::setFearModeStart(float timer) {
    fearmodeStart = timer;
}

int World::getPacmanLives() const{
    return pacmanlives;
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

    // Set death state
    deathTime = totTime;
    death = true;

    // Create visitor to reset all entities
    DeathVisitor visitor(this, totTime);

    // Visit Pacman
    pacman->accept(visitor);

    // Visit all ghosts
    for (auto& g : ghosts) {
        g->accept(visitor);
    }

    // Disable fear mode
    fearmode = false;
    fearmodeStart = 0.f;
}

int World::getCoinCount() const{
    return coinCount; ;
}

void World::resetWorld() {
    rounds = rounds + 1;
    reset = true;
}

Score& World::getScore() {
    return score;
}
