// this example do not work with all the kernel
//

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
using namespace std;
using namespace cv;

string image_path = "..\\..\\images\\Faces\\001_a.png";

int main()
{
	Mat src;
	src = imread(image_path, IMREAD_COLOR);
	imshow("Source", src);
	//int key = waitKey(0);

	/*Mat kernel = (Mat_<float>(3, 3) <<
		1, 2, 1,
		2, 4, 2,
		1, 2, 1);
	kernel = kernel / 16;*/

	/*Mat kernel = (Mat_<float>(3, 3) <<
		0, -1, 0,
		-1, 4, -1,
		0, -1, 0);*/


	/*Mat kernel = (Mat_<float>(3, 3) <<
		1, 1, 1,
		1, 1, 1,
		1, 1, 1);
	kernel = kernel / 9;*/

	//this one give a not expected result
	Mat kernel = (Mat_<float>(3, 3) <<
		-1, -1, -1,
		-1, 8, -1,
		-1, -1, -1);
	
	

	int kernelSum = 1;
	int span = kernel.cols / 2;
	int srcChannels = src.channels();

	Mat dest = src.clone();
	dest.zeros(src.rows, src.cols, src.type());
	int type = dest.type();

	float tmp;
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			for (int c = 0; c < srcChannels; c++)
			{
				tmp = 0;
				
				
				for (int ki = 0; ki < kernel.rows; ki++)
				{
					for (int kj = 0; kj < kernel.rows; kj++)
					{
						if (i - span + ki >= 0 && j - span + kj >= 0 && i - span + ki < src.rows && j - span + kj < src.cols) {
							tmp += src.at<Vec3b>(i-span+ki,j-span+kj).val[c] * kernel.at<float>(ki, kj);
						}
					}
				}

				if (tmp < 0)tmp = 0;
				if (tmp > 255)tmp = 255;
				
				dest.at<Vec3b>(i, j).val[c] = tmp;
			}
		}

	}

	cout << type << endl;
	imshow("Dest", dest);
	int k = waitKey(0);
}
