#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src, dst;

int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;
int const max_operator = 4;
int const max_elem = 2;
int const max_kernel_size = 21;

const char* window_name = "Morphology Transformations Demo";


void Morphology_Operations(int, void*);

  string image_path = "..\\..\\images\\image-1.jpg";

int main(int argc, char** argv)
{
    src = imread(image_path, IMREAD_COLOR);
    if (src.empty())
    {
        std::cout << "Could not open or find the image!\n" << std::endl;
        return EXIT_FAILURE;
    }

    namedWindow(window_name, WINDOW_AUTOSIZE); // Create window

    createTrackbar("Operator:\n 0: Opening - 1: Closing  \n 2: Gradient - 3: Top Hat \n 4: Black Hat", window_name, &morph_operator, max_operator, Morphology_Operations);

    createTrackbar("Element:\n 0: Rect - 1: Cross - 2: Ellipse", window_name,
        &morph_elem, max_elem,
        Morphology_Operations);

    createTrackbar("Kernel size:\n 2n +1", window_name,
        &morph_size, max_kernel_size,
        Morphology_Operations);

    Morphology_Operations(0, 0);

    waitKey(0);
    return 0;
}


void Morphology_Operations(int, void*)
{
    // Since MORPH_X : 2,3,4,5 and 6
    int operation = morph_operator + 2;

    Mat element = getStructuringElement(morph_elem, Size(2 * morph_size + 1, 2 * morph_size + 1), Point(morph_size, morph_size));

    morphologyEx(src, dst, operation, element);
    imshow(window_name, dst);
}

/*
* opening: erosion operation followed by an dilation
*   usefull for removing small objects (bright object on a dark foregroung)
* closing: dilation operation followed by an erosion
*   usefull to remove small holes in an image (dark object on a bright foreground)
* morphological gradient: difference between the dilation and the erosion of an image
*   usefull for finding the outline of an object
* top hat: difference between input image and its opening
* black hat: difference between closing and input image
*/
