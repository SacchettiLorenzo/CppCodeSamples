#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

int threshold_value = 0;
int threshold_type = 3;

int const max_value = 255;
int const max_type = 4;
int const max_binary_value = 255;


string image_path = "..\\..\\images\\image-3.jpg";
Mat src, src_gray, dst;
const char* window_name = "Threshold Demo";

const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";

static void Threshold_Demo(int, void*)
{
    /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
    */
    threshold(src_gray, dst, threshold_value, max_binary_value, threshold_type);
    imshow(window_name, dst);
}

int main()
{
    src = imread(image_path, IMREAD_COLOR);
    if (src.empty())
    {
        std::cout << "Could not open or find the image!\n" << std::endl;
        return EXIT_FAILURE;
    }

    cvtColor(src, src_gray, COLOR_BGR2GRAY); // Convert the image to Gray

    namedWindow(window_name, WINDOW_AUTOSIZE); // Create a window to display results

    createTrackbar(trackbar_type,
        window_name, &threshold_type,
        max_type, Threshold_Demo); // Create a Trackbar to choose type of Threshold

    createTrackbar(trackbar_value,
        window_name, &threshold_value,
        max_value, Threshold_Demo); // Create a Trackbar to choose Threshold value

    Threshold_Demo(0, 0); // Call the function to initialize

    waitKey();
    return 0;
}

//threasholding is used when we want to separate different regions of an image based on the variation of the intensity between the objects pixels
//binary threshold:
//  if the intensity is above a certain value the pixel intensity is set to maxVal. Otherwise is set to 0
//binary threshold inverted
//truncate:
//  the maximum intensity value is a constant X. every value greater than X is truncated to X
//threshold to zero:
//  if the pixel value is lower than X the pixel value is set to 0
//threshold to zero inverted
