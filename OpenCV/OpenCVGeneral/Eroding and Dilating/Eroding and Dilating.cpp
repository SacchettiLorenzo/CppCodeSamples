
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src, erosion_dst, dilation_dst;

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;

void Erosion(int, void*);
void Dilation(int, void*);

string image_path = "..\\..\\images\\image-1.jpg";

int main()
{
    src = imread(image_path, IMREAD_COLOR);

    if (src.empty()) {
        cout << "Unable to open image" << endl;
        return -1;
    }

    namedWindow("Erosion Demo", WINDOW_AUTOSIZE);
    namedWindow("Dilation Demo", WINDOW_AUTOSIZE);
    moveWindow("Dilation Demo", src.cols, 0);

    createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
        &erosion_elem, max_elem,
        Erosion);

    createTrackbar("Kernel size:\n 2n +1", "Erosion Demo",
        &erosion_size, max_kernel_size,
        Erosion);

    createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
        &dilation_elem, max_elem,
        Dilation);

    createTrackbar("Kernel size:\n 2n +1", "Dilation Demo",
        &dilation_size, max_kernel_size,
        Dilation);

    Erosion(0, 0);
    Dilation(0, 0);

    waitKey(0);
    return 0;


}

void Erosion(int, void*) {
    int erosion_type = 0;
    if (erosion_elem == 0) {
        erosion_type = MORPH_RECT;
    }
    else if (erosion_elem == 1) {
        erosion_type = MORPH_CROSS;
    }
    else if (erosion_elem == 2) {
        erosion_type = MORPH_ELLIPSE;
    }

    //return the kernel that perform the erodion operation
    Mat element = getStructuringElement(erosion_type, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));

    erode(src, erosion_dst, element);
    imshow("Erosion Demo", erosion_dst);

}

void Dilation(int, void*) {
    int dilation_type = 0;
    if (dilation_elem == 0) { dilation_type = MORPH_RECT; }
    else if (dilation_elem == 1) { dilation_type = MORPH_CROSS; }
    else if (dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

    //return the kernel that perform the dilation operation
    Mat element = getStructuringElement(dilation_type,
        Size(2 * dilation_size + 1, 2 * dilation_size + 1),
        Point(dilation_size, dilation_size));

    dilate(src, dilation_dst, element);
    imshow("Dilation Demo", dilation_dst);
}

//Dilation consisit of convolving an image with some kernel that compute the maximal pixel value of the region overlapped by the kernel itself.
//The kernel anchor point (center of the kernel) is replaced by the maximal pixel value found before.

//Erosion is the same operation but using the minimal pixel value in the region overlapped by the kernel.

