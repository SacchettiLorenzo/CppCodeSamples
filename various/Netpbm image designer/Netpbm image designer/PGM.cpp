#include "PGM.h"

PGM::PGM(ofstream* image, string name, int width, int height, int colorDepth)
{
	this->height = height;
	this->width = width;
	this->image = image;
	this->name = name;
	grid = (int*)malloc(width * height * sizeof(int));

	image->open(name + extension);

	if (image->is_open()) {
		//header info
		*image << "P2" << endl;
		*image << width << " " << height << endl;
		*image << colorDepth << endl;
	}

	image->close();
}

void PGM::drawBlank() {
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			grid[i * height + j] = 0;
		}
	}
}

void PGM::draw()
{
	image->open(name + extension, ios_base::app);
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			*image << grid[i * height + j] << " ";
		}

	}
	image->close();
}

void PGM::drawGrid(int colorDepth)
{
	int temp = 0;
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			grid[i * height + j] = temp;
			if (temp == 0)temp = colorDepth;
			else
			if (temp == colorDepth)temp = 0;
		}
		if (temp == 0)temp = colorDepth;
		else
		if (temp == colorDepth)temp = 0;
	}
}

void PGM::drawCircle(int xc, int yc, int r, int colorDepth)
{
	int twidth = width;
	int theight = height;

	if (twidth > theight) {
		yc = yc - (twidth - theight) / 2;
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
		int y = sqrt(r2 - pow(i, 2));
		int x = sqrt(r2 - pow(i, 2));
		grid[(twidth * (hhyc - y)) - hwxc - i] = colorDepth;  //top left
		grid[(twidth * (hhyc - y)) - hwxc + i] = colorDepth; //top right
		grid[(twidth * (hhyc + y)) + hwxc - i] = colorDepth; //bottom left 
		grid[(twidth * (hhyc + y)) + hwxc + i] = colorDepth; //bottom right
		grid[(theight * (hwyc - i)) - hhxc - x] = colorDepth;  //top left
		grid[(theight * (hwyc - i)) - hhxc + x] = colorDepth; //top right
		grid[(theight * (hwyc + i)) + hhxc - x] = colorDepth; //bottom left 
		grid[(theight * (hwyc + i)) + hhxc + x] = colorDepth; //bottom right
	}

}
