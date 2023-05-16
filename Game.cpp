#include "Game.h"

void Game::runGame(const std::string& filename,int iterations, bool all) {

    std::shared_ptr<Grid> currentGrid = m_grid;
    std::shared_ptr<Grid> nextGrid = std::make_shared<Grid>(*currentGrid);

    for (int i = 0; i < iterations; i++) {

        currentGrid->extendMatrix();
        nextGrid->extendMatrix();

        int currentRows = currentGrid->getRows();
        int currentCols = currentGrid->getCols();

        for (int row = 0; row < currentRows; row++) {
            for (int col = 0; col < currentCols; col++) {

                bool isAlive = currentGrid->getCell(row, col);
                int aliveNeighborsCount = currentGrid->calculateAliveNeighbors(row, col);
                bool shouldLive = m_rule->shouldCellBeAlive(isAlive, aliveNeighborsCount);
                nextGrid->setCell(row, col, shouldLive);
            }
        }

        currentGrid->m_matrix = nextGrid->m_matrix; //TODO avoid copies 
        //std::swap(currentGrid, nextGrid);  // TODO if performances needed solve issue with indexes...

        currentGrid->reduceToSmallestMatrix();
 

        if (currentGrid->getRows() == 0) {
            std::cout << "\n====================================================" << std::endl;
            std::cout << "Population extinct  it is over  _(--)_/ Try again    " << std::endl;
            std::cout << "====================================================" << std::endl;
            return;
        }

        if (!all && i != iterations - 1) {

            continue; // Skip printing if not printing all iterations
        }
        currentGrid->printMatrix(filename, i + 1); // Print the current state of the grid
        std::cout << '\n';
    }
}



