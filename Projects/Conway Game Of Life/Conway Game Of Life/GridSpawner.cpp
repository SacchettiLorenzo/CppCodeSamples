#include "GridSpawner.h"
GridSpawner::GridSpawner(int gap, int squaresize, int width, int height)
{
    int currentPositionX = 0;
    int currentPositionY = 0;
    for (size_t i = 0; i < height / (squaresize + gap); i++)
    {
        for (size_t j = 0; j < width / (squaresize + gap); j++)
        {
            Square s(squaresize, sf::Vector2f(currentPositionX, currentPositionY));
            s.SetGridPosition(j, i);
            grid.push_back(s);
            currentPositionX += (squaresize + gap);
        }

        currentPositionY += (squaresize + gap);
        currentPositionX = 0;
    }
}

GridSpawner::~GridSpawner()
{
}

std::vector<Square>* GridSpawner::getVecAddr()
{
    return &grid;
}
