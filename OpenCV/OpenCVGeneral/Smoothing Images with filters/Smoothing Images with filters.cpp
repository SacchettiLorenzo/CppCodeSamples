#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

string image_path = "..\\..\\images\\image-1.jpg";

int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;
Mat src; Mat dst;
char window_name[] = "Smoothing Demo";
int display_caption(const char* caption);
int display_dst(int delay);

/*  Each filter perform the operation with a kernel of size "Size(n*n)"
*   The object "Point(-1, -1)" rapresent the anchor point of the kernel
*   in this case "(-1 , -1)" rapresent the center of the kernel (read documentation)
*/

int main()
{
    namedWindow(window_name, WINDOW_AUTOSIZE);
    src = imread(samples::findFile(image_path), IMREAD_COLOR);

    if (src.empty())
    {
        printf(" Error opening image\n");
        return EXIT_FAILURE;
    }

    if (display_caption("Original Image") != 0)
    {
        return 0;
    }

    dst = src.clone();

    if (display_dst(DELAY_CAPTION) != 0)
    {
        return 0;
    }

    if (display_caption("Homogeneous Blur") != 0)
    {
        return 0;
    }

    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        blur(src, dst, Size(i, i), Point(-1, -1));
        if (display_dst(DELAY_BLUR) != 0)
        {
            return 0;
        }
    }

    if (display_caption("Gaussian Blur") != 0)
    {
        return 0;
    }
     // gaussian blur require the standard deviation for X and Y axes
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        GaussianBlur(src, dst, Size(i, i), 0, 0);
        if (display_dst(DELAY_BLUR) != 0)
        {
            return 0;
        }
    }

    if (display_caption("Median Blur") != 0)
    {
        return 0;
    }

    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        medianBlur(src, dst, i);
        if (display_dst(DELAY_BLUR) != 0)
        {
            return 0;
        }
    }
    if (display_caption("Bilateral Blur") != 0)
    {
        return 0;
    }

    //bilateral field require the standard deviation of the color space and in the coordinate space
    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        bilateralFilter(src, dst, i, i * 2, i / 2);
        if (display_dst(DELAY_BLUR) != 0)
        {
            return 0;
        }
    }
    display_caption("Done!");
    return 0;
}

int display_caption(const char* caption)
{
    dst = Mat::zeros(src.size(), src.type());
    putText(dst, caption,
        Point(src.cols / 4, src.rows / 2),FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
    return display_dst(DELAY_CAPTION);
}

int display_dst(int delay)
{
    imshow(window_name, dst);
    int c = waitKey(delay);
    if (c >= 0) { return -1; }
    return 0;
}


