// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

void showImage();
void MatBasics();
void lookupTable();

using namespace cv;
using namespace std;

string image_path = "C:\\Users\\VGpc\\Documents\\GitHub\\CppCodeSamples\\OpenCV\\OpenCVGeneral\\x64\\Debug\\image_0.jpg";
int main()
{
	//showImage();
	//MatBasics();
	lookupTable();
}

void showImage() {

	Mat img = imread(image_path, IMREAD_COLOR);

	imshow("Display window", img);

	int k = waitKey(0);
}

/* Basic class for image handling
*  The instance of a Mat class generate header part of the image with metadata about it
*  copy constructor and assignement operator work with reference so making a modification in any of them will affect all the other ones as well,
*  the headers will remain different so it is possible to create mat object that refer to subset of the original data ROI (Region Of Interest).
*  If a copy of a Mat is needed it is possible to create a copy
*
*  in the example A,B,C,D are referred to the same data, F,G are completely new
*
*  OpenCv cna store colors in differen forms, the famous RGB is stored as BGR
*  while creating an image the type of data used must be specified and also the function used to populate each pixel
*  for example CV_8UC3 means CV_[The number of bits per item][Signed or Unsigned][Type Prefix]C[The channel number]
*  all of this types are predefined and can be found in the documentation
*/
void MatBasics() {
	int k = 0;
	Mat A, C;
	Mat B(A);

	C = imread(image_path, IMREAD_COLOR);

	A = C; //assignement
	imshow("1", A);
	k = waitKey(0);

	Mat D(A, Rect(20, 250, 300, 300)); //ROI
	imshow("2", D);
	k = waitKey(0);

	Mat F = A.clone();
	Mat G;
	A.copyTo(G);


	Mat M(50, 50, CV_8UC3, Scalar(0, 0, 255));
	imshow("3", M);
	cout << "M = " << M << endl;
	k = waitKey(0);

}

/* sometimes the programm need to perform some operation on each pixel (color reduction for example)
*  to improve performace we should avoid to calculate every time the result of the operation but we should have all the possible result already stored
*  the lookup table is defined at the beginning of the program and hold all the possible value
*  for example if we want to perform a color reduction of 10 times the lookup table should hold all the new value for the previous 256 available
*  It is also possible to iterate through the image via MatIterator
*
*  OpenCV privide the function LUT() to performa directly this operation providing a lookup table and input and output Mat
*  the LUT() function has the highest performance because use multithreading
*/
void lookupTable() {
	int ratio = 50;
	uchar table[256]; //lookup table, for each color (index) have one color to pair (value) 
	for (int i = 0; i < 256; ++i)
		table[i] = (uchar)(ratio * (i / ratio));

	Mat normalimg = imread(image_path, IMREAD_COLOR);
	imshow("normal color", normalimg);

	Mat img = normalimg.clone();
	/*
	int channels = img.channels();
	int nRows = img.rows;
	int nCols = img.cols * channels; //multipying column and channel to simulate one column for each color channel (avoid another for loop)

	if (img.isContinuous()) {
		nCols *= nRows;
		nRows = 1;
	}

	int i, j;
	uchar* p;
	for ( i = 0; i < nRows; i++)//for each row of the image
	{
		p = img.ptr<uchar>(i); //pointer to the first element of each row
		for ( j = 0; j < nCols; j++)//for each column and channel of the image
		{
			p[j] = table[p[j]];
		}
	}
	*/



	Mat lookUpTable(1, 256, CV_8U);
	uchar* q = lookUpTable.ptr();
	for (int i = 0; i < 256; ++i)
		q[i] = table[i];

	LUT(normalimg, lookUpTable, img);

	imshow("reducted color", img);
	int k = waitKey(0);
}