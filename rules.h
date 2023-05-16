#pragma once
class GameRule {
public:
    virtual bool shouldCellBeAlive(bool isCurrentlyAlive, int aliveNeighborsCount) const = 0;
};

class ConwaysRule : public GameRule {
public:
    bool shouldCellBeAlive(bool isCurrentlyAlive, int aliveNeighborsCount) const override;
 
};
