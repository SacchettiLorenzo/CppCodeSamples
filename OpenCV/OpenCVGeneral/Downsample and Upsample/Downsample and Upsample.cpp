#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;


string image_path = "..\\..\\images\\image-1.jpg";

int main()
{
    Mat src = imread(image_path, IMREAD_COLOR);
    if (src.empty())
    {
        std::cout << "Could not open or find the image!\n" << std::endl;
        return EXIT_FAILURE;
    }

    cout << "\n Zoom In-Out demo \n "
        "------------------  \n"
        " * [i] -> Zoom in   \n"
        " * [o] -> Zoom out  \n"
        " * [ESC] -> Close program \n" << endl;

    for (;;) {
        imshow("pyramids demo", src);
        char c = (char)waitKey(0);

        if (c == 27) {
            break;
        }
        else if (c == 'i') {
            pyrUp(src, src, Size(src.cols * 2, src.rows * 2));
        }
        else if (c == 'o') {
            pyrDown(src, src, Size(src.cols / 2, src.rows / 2));
        }
    }

    return EXIT_SUCCESS;
}

//downscaling is performed using a collection of images all arising from a single original image
//the images are one smaller that the other forming a pyramid

//(downsize)the gaussian pyramid convolve the imager with a gaussian kernel then remove all the even-numbered rows and column to adjust the size of the result image
//(upsize)the image is upsized adding new rows and columns then a gaussian multiplied by 4 is applied 
//the procedure "create and destroy" pixel so upsizing then downsize (or opposite) will produce a different image than the original one