#include <iostream>
#include <fstream>

#include "PBM.h"
#include "PGM.h"
#include "PPM.h"

using namespace std;



int main()
{
    ofstream image;
    ofstream* imagePtr = &image;

    //PBM i(imagePtr,"PMBimage",700,800);

    //PGM ii(imagePtr, "PGMimage", 50, 50, 255);

    PPM iii(imagePtr, "PPMimage", 50, 50, 255);
    iii.drawBlank();
    iii.drawGrid(255);
    iii.draw();
}

//netpbm format
/*
* the file start with 2 char that describe the format P1,P2,P3
*  P1 : portable BitMap - .pbm - colors: 0->1 (white and black)
*  P2 : Portable grayMap - .pgm - colors: 0->255 (gray scale)
*  P3 : Portable PixMap - .ppm - colors: 0->255  for each RGB channel
* 
* the header at the begin of the file inlcude format, length and width, max color value for each channel
*/
