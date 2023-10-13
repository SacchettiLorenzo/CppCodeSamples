#pragma once
#include "Square.h"
#include <vector>
#include <iostream>
#include <algorithm>
class Simulation
{
public:
	Simulation(std::vector<Square>* vec_ptr, int* width, int* height, int* squaresize, int* gap);
	void setVecPtr(std::vector<Square>* vec_ptr);

	//define a smaller portion of the grid to perform the calculation on
	void defineSquaredAround();

	//
	void performSimulation();

	//check the square neightbour
	bool checkTopLeftNeightbour(Square s);
	bool checkLeftNeightbour(Square s);
	bool checkBottomLeftNeightbour(Square s);
	bool checkBottomNeightbour(Square s);
	bool checkBottomRightNeightbour(Square s);
	bool checkRightNeightbour(Square s);
	bool checkTopRightNeightbour(Square s);
	bool checkTopNeightbour(Square s);

private:
	int* width;
	int* height;
	int* sqauresize;
	int* gap;
	struct Around{
		int topLeftX;
		int topLeftY;
		int bottomRightX;
		int bottomRightY;
	} around;
	std::vector<Square>* vec_ptr;
	std::vector<Square> simulativeSubset;

};

