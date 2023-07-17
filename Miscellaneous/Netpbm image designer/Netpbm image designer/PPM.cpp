#include "PPM.h"

PPM::PPM(ofstream* image, string name, int width, int height, int colorDepth)
{
	this->height = height;
	this->width = width;
	this->image = image;
	this->name = name;
	grid = (RGB*)malloc(width * height * sizeof(RGB));

	image->open(name + extension);

	if (image->is_open()) {
		//header info
		*image << "P3" << endl;
		*image << width << " " << height << endl;
		*image << colorDepth << endl;
	}

	image->close();
}

void PPM::drawBlank()
{
	RGB white = { 255,255,255 };
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			grid[i * height + j] = white;
		}
	}
}

void PPM::draw()
{
	image->open(name + extension, ios_base::app);
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			*image << grid[i * height + j].red << " " << grid[i * height + j].green <<" "<< grid[i * height + j].blue<< " ";
		}

	}
	image->close();
}

void PPM::drawGrid(int colorDepth)
{
	srand(time(NULL));
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			grid[i * height + j].red = rand() % (colorDepth+1);
			grid[i * height + j].green = rand() % (colorDepth+1);
			grid[i * height + j].blue = rand() % (colorDepth+1);
		}
	}
}

