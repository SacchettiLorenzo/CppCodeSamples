#pragma once
#include <fstream>
#include <string>

using namespace std;

class PBM
{
private:
	
	int height = 0;
	int width = 0;
	const char* extension = ".pbm";
	ofstream* image;
	string name;
	bool* grid; //actual image pixels

public:
	PBM(ofstream* image, string name, int width, int height);

	void drawBlank();

	void drawGrid();
	void drawCircle(int xc, int yc, int r);

	void draw();
	
};



