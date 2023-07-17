#include "PBM.h"
#include <math.h>
#include <iostream>
#define PI 3.14159265

PBM::PBM(ofstream* image, string name, int width, int height) {

	this->height = height;
	this->width = width;
	this->image = image;
	this->name = name;
	grid = (bool*)malloc(width * height * sizeof(bool));

	image->open(name + extension);

	if (image->is_open()) {
		//header info
		*image << "P1" << endl;
		*image << width << " " << height << endl;
	}

	image->close();
}

void PBM::drawBlank() {
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			grid[i * height + j] = 0;
		}
	}
}

void PBM::drawGrid()
{
	bool temp = 0;
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			grid[i * height + j] = temp;
			temp = !temp;
		}
		temp = !temp;
	}
}

void PBM::drawCircle(int xc, int yc, int r)
{
	int twidth = width;
	int theight = height;

	if (twidth > theight) {
		yc = yc - (twidth-theight)/2;
		theight = twidth;
	}

	
	if (theight > twidth) {
		//xc = xc - (theight - twidth) / 360;
		theight = twidth;
	}
	
	int hh = (theight / 2);
	int hw = (twidth / 2);
	int hhyc = hh + yc;
	int hhxc = hh + xc;
	int hwxc = hw + xc;
	int hwyc = hw + yc;

	int r2 = pow(r, 2);
	
	for (size_t i = 0; i < r; i++)
	{
		int y = sqrt(r2 - pow(i,2));
		int x = sqrt(r2 - pow(i, 2));
		grid[(twidth * (hhyc - y)) - hwxc - i] = 1;  //top left
		grid[(twidth * (hhyc - y)) - hwxc + i] = 1; //top right
		grid[(twidth * (hhyc + y)) + hwxc - i] = 1; //bottom left 
		grid[(twidth * (hhyc + y)) + hwxc + i] = 1; //bottom right
		grid[(theight * (hwyc - i)) - hhxc - x] = 1;  //top left
		grid[(theight * (hwyc - i)) - hhxc + x] = 1; //top right
		grid[(theight * (hwyc + i)) + hhxc - x] = 1; //bottom left 
		grid[(theight * (hwyc + i)) + hhxc + x] = 1; //bottom right
	}
	
}




void PBM::draw()
{
	image->open(name + extension, ios_base::app);
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			*image << grid[i * height + j];
		}

	}
	image->close();
}

