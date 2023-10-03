#pragma once
#include <fstream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;
class PPM
{
private:
	
	int height = 0;
	int width = 0;
	const char* extension = ".ppm";
	ofstream* image;
	string name;
	struct RGB {
		int red;
		int green;
		int blue;
	}* grid;
public:
	PPM(ofstream* image, string name, int width, int height, int colorDepth);
	void drawBlank();
	void draw();
	void drawGrid(int colorDepth);
};

