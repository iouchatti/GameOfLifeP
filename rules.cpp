#include "rules.h"
bool ConwaysRule::shouldCellBeAlive(bool isCurrentlyAlive, int aliveNeighborsCount) const {
    if (isCurrentlyAlive && (aliveNeighborsCount == 2 || aliveNeighborsCount == 3)) {
        return true;
    }
    if (!isCurrentlyAlive && aliveNeighborsCount == 3) {
        return true;
    }
    return false;
}