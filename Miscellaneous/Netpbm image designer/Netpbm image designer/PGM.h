#pragma once
#include <fstream>
#include <string>

using namespace std;
class PGM
{
private:

	int height = 0;
	int width = 0;
	const char* extension = ".pgm";
	ofstream* image;
	string name;
	int* grid; //actual image pixels
	int colorDepth;
public:
	PGM(ofstream* image, string name, int width, int height, int colorDepth);
	void drawBlank();
	void draw();
	void drawGrid(int colorDepth);
	void drawCircle(int xc, int yc, int r, int colorDepth);
};

