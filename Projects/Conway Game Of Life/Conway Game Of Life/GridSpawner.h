#pragma once
#include <vector>
#include "Square.h"
class GridSpawner
{
public:
    GridSpawner(int gap, int squaresize, int width, int height);
    ~GridSpawner();

    std::vector<Square>* getVecAddr();

private:
    std::vector<Square> grid;
};