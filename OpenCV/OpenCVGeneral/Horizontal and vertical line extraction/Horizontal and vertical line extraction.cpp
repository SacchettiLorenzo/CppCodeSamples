#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void show_wait_destroy(const char* winname, cv::Mat img);

Mat src, dst;

string image_path = "..\\..\\images\\image-3.jpg";

int main(int argc, char** argv)
{
    src = imread(image_path, IMREAD_COLOR);
    if (src.empty())
    {
        std::cout << "Could not open or find the image!\n" << std::endl;
        std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
        return EXIT_FAILURE;
    }

    // Show source image
    imshow("src", src);

    //transform source image to greyscale image
    Mat gray;

    if (src.channels() == 3) {
        cvtColor(src, gray, COLOR_BGR2GRAY);
    }
    else {
        gray = src;
    }

    show_wait_destroy("gray", gray);

    Mat bw;
    //grayscale to binary image
    //ADAPTIVE_THRESH_MEAN_C: The threshold value is the mean of the neighbourhood area minus the constant C (-1)
    //THRESH_BINARY: binary threshold, the output will be either white or balck (0 or 1)
    //~ bitweise not (overloaded operator for Mat object)
    adaptiveThreshold(~gray, bw, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, -1);

    show_wait_destroy("binary", bw);

    Mat horizontal = bw.clone();
    Mat vertical = bw.clone();

    //the constant value act as a sort of sensitivity value
    int horizontal_size = horizontal.cols / 30;

    //rectangular structuring element with size 1 as height and cols/30 width
    Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(horizontal_size, 1));

    //opening morphological operation
    erode(horizontal, horizontal, horizontalStructure, Point(-1, -1));
    dilate(horizontal, horizontal, horizontalStructure, Point(-1, -1));

    show_wait_destroy("horizontal", horizontal);

    int vertical_size = vertical.rows / 30;

    Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, vertical_size));

    erode(vertical, vertical, verticalStructure, Point(-1, -1));
    dilate(vertical, vertical, verticalStructure, Point(-1, -1));

    show_wait_destroy("vertical", vertical);

    waitKey(0);
    return 0;
}

void show_wait_destroy(const char* winname, cv::Mat img) {
    imshow(winname, img);
    moveWindow(winname, 500, 0);
    waitKey(0);
    destroyWindow(winname);
}

