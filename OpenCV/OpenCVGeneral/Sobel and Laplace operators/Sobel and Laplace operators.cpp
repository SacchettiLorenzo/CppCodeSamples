#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

string image_path = "..\\..\\images\\image-1.jpg";

//this values could be adjusted
int ksize = 1;
int scale = 1;
int delta = 0;
int ddepth = CV_16S;

int main()
{
    Mat src, blurred;
    src = imread(image_path, IMREAD_COLOR);
    imshow("Source", src);

    if (src.empty())
    {
        printf("Error opening image: %s\n");
        return EXIT_FAILURE;
    }

    

    //remove noise with gaus filter
    GaussianBlur(src, blurred, Size(3, 3), 0, 0, BORDER_DEFAULT);

    waitKey(0);
    imshow("Blurred", blurred);

    Mat blurred_gray;
    cvtColor(blurred, blurred_gray, COLOR_BGR2GRAY);

    waitKey(0);
    imshow("Blurred Grey", blurred_gray);

    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    Mat grad;
    
    Sobel(blurred_gray, grad_x, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    waitKey(0);
    imshow("abs_grad_x", abs_grad_x);

    Sobel(blurred_gray, grad_y, ddepth, 1, 0, ksize, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);
    waitKey(0);
    imshow("abs_grad_y", abs_grad_y);

    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    waitKey(0);
    imshow("Sobel final", abs_grad_y);

    waitKey(0);

    destroyAllWindows();

    Mat laplacian, laplacian_abs;
    int kernel_size = 3;

    Laplacian(blurred_gray, laplacian, ddepth, kernel_size, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(laplacian, laplacian_abs);
    imshow("LAPLACIAN", laplacian_abs);

    waitKey(0);
}

/*
* sobel operator is a way to apply derivative to an image with the objective of enhanching the conours.
* the sobel kernel are applied for both horizontal and vertical changes.
* at each point the result image is an approximation of the gradient combining both result.
* an edge in an image is a strong variation of intensity that can be shown  using derivative 
* 
* laplacian derivarive is a way to apply second derivative and finding the zero of the function
* that describe the image in a partigular dimension. the zero if where the image show an edge
*/