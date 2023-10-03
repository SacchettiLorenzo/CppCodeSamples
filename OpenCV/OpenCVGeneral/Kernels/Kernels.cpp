// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

string image_path = "C:\\Users\\VGpc\\Pictures\\Image samples\\800x600\\image_1.jpg";

void Identity(Mat);
void Ridge(Mat);
void EdgeDetection(Mat);
void Sharpen(Mat);
void BoxBlur(Mat);
void GaussianBlur(Mat);
void GaussianBlurBigger(Mat);

int main(int argc, char* argv[])
{

	Mat src;
	src = imread(image_path, IMREAD_COLOR);

	Identity(src);
	Ridge(src);
	EdgeDetection(src);
	Sharpen(src);
	BoxBlur(src);
	GaussianBlur(src);
	GaussianBlurBigger(src);

	waitKey();
	return EXIT_SUCCESS;
}

/* A kernel is a n x n square matrix that rapresent the wheight that the nearby pixel have on the selected one.
*  To calculate the value of the pixel based on the nearby pixels we need to multiplay the kernel element with the corresponding pixel
*  then divide for the sum of all the element of the kernel. (convolution)
*  to apply the kernel to the pixel e:
*
*  img:			kernel:					result: e5 = (a1+b2+c3+d4+e5+f6+g7+h8+i9)*(1/45)
*  |a,b,c|				|1,2,3|	 1				|a1,b2,c3|	1
*  |d,e,f|				|4,5,6|* -				|d4,e5,f6|* -
*  |g,h,i|				|7,8,9|	 45				|g7,h8,i9|  45
*
*  using different value in the kernel is possible to filter specific element inside the image
*  The kernel can be built with various numeric type so during the calculation it might be precision loss if using only integer or char types
*  OpenCV provide some optimized function for known filters
*
*  The function filter2D applies the kernel to the Mat instance (it is possible to provide information about color depth and starting point)
*
*
*/

void Identity(Mat src) {
	//The nearby pixels do not have effect on the central one
	Mat kernel = (Mat_<double>(3, 3) <<
		0, 0, 0,
		0, 1, 0,
		0, 0, 0);
	//kernel = kernel / 1;
	Mat dest = Mat();
	filter2D(src, dest, -1, kernel);
	imshow("Identity", dest);
}

void Ridge(Mat src) {
	Mat kernel = (Mat_<double>(3, 3) <<
		0, -1, 0,
		-1, 4, -1,
		0, -1, 0);
	//no division because sum = 0
	Mat dest;
	filter2D(src, dest, -1, kernel);
	imshow("Ridge", dest);
}

void EdgeDetection(Mat src) {
	Mat kernel = (Mat_<double>(3, 3) <<
		-1, -1, -1,
		-1, 8, -1,
		-1, -1, -1);
	//no division because sum = 0
	Mat dest;
	filter2D(src, dest, -1, kernel);
	imshow("EdgeDetection", dest);
}

void Sharpen(Mat src) {
	Mat kernel = (Mat_<double>(3, 3) <<
		0, -1, 0,
		-1, 5, -1,
		0, -1, 0);
	//no division because sum = 1
	Mat dest;
	filter2D(src, dest, -1, kernel);
	imshow("Sharpen", dest);
}

void BoxBlur(Mat src) {
	Mat kernel = (Mat_<double>(3, 3) <<
		1, 1, 1,
		1, 1, 1,
		1, 1, 1);
	kernel = kernel / 9;
	Mat dest;
	filter2D(src, dest, -1, kernel);
	imshow("BoxBlur", dest);
}

void GaussianBlur(Mat src) {
	Mat kernel = (Mat_<double>(3, 3) <<
		1, 2, 1,
		2, 4, 2,
		1, 2, 1);
	kernel = kernel / 16;
	Mat dest;
	filter2D(src, dest, -1, kernel);
	imshow("GaussianBlur", dest);
}

void GaussianBlurBigger(Mat src) {
	Mat kernel = (Mat_<double>(5, 5) <<
		1, 4, 6, 4, 1,
		4, 16, 24, 16, 4,
		6, 24, 36, 24, 6,
		4, 16, 24, 16, 4,
		1, 4, 6, 4, 1);
	kernel = kernel / 256;
	Mat dest;
	filter2D(src, dest, -1, kernel);
	imshow("GaussianBlurBigger", dest);
}