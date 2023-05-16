#pragma once
#include <memory>
#include <string>
#include "rules.h"
#include "Grid.h"
#include "inputParser.h"
class Game{
private:
    std::shared_ptr<Grid> m_grid;
    std::unique_ptr<GameRule> m_rule;
public:
    Game(const std::shared_ptr<Grid> initialGrid, std::unique_ptr<GameRule> rule)
        : m_grid(initialGrid), m_rule(std::move(rule)) {}

    void runGame(const std::string& filename,int iterations, bool all);
};

