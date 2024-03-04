#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cin;
using std::cout;
using std::endl;
using namespace cv;

std::string image_path = "..\\..\\images\\image-1.jpg";

int main(int argc, char** argv)
{

	Mat image = imread(image_path, IMREAD_COLOR);
	if (image.empty())
	{
		cout << "Could not open or find the image!\n" << endl;
		cout << "Usage: " << argv[0] << " <Input image>" << endl;
		return -1;
	}
	imshow("Original Image", image);

	Mat new_image = Mat::zeros(image.size(), image.type());
	double alpha = 1.0; /*< Simple contrast control */
	int beta = 0; /*< Simple brightness control */
	cout << " Basic Linear Transforms " << endl;
	cout << "-------------------------" << endl;
	cout << "* Enter the alpha value [1.0-3.0]: "; cin >> alpha;
	cout << "* Enter the beta value [0-100]: "; cin >> beta;
	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			for (int c = 0; c < image.channels(); c++) {
				new_image.at<Vec3b>(y, x)[c] =
					saturate_cast<uchar>(alpha * image.at<Vec3b>(y, x)[c] + beta);
			}
		}
	}
	imshow("New Image", new_image);
	waitKey();
	return 0;
}
/* Vec3b is a vector with 3 bytes entries that rapresent the 3 challel BGR (RBG)
*  any Mat image can provide the Vect3b for each point of the image. every channel can be accessed as a normal vector
*
*  Brightness and contrast can be changed using the a simple formula
*  g(y,x) = alpha*f(y,x) + beta
*  alpha is the gain parameter and control the contrast of the image
*  beta is the bias parameter and control the brightnell of the image
*
*  saturete_cast function help casting the result of the formula into a value that is inside the boundaries of the provided data type
*  uchar a = saturate_cast<uchar>(-100); a = 0;
*  short b = saturate_cast<short>(33333,33333); b = 32767;
*  if the value is a floating point it is rounded and if needed clipped
*  for 32bit int no clipping is performed
*
*/