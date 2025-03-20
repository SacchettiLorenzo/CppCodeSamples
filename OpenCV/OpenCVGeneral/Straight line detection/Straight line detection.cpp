#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

string image_path = "..\\..\\images\\image-1.jpg";
string image_path_lines = "..\\..\\images\\image-4.png";

int lowThreshold = 0;
const int max_lowThreshold = 100;
const int ratio_ = 3;
const int kernel_size = 3;

static void CannyThreshold(int,void*);
    Mat src;
    Mat gray;
    Mat detected_edges;
    Mat dst;

    Mat src_lines;

int main()
{
    src = imread(image_path, IMREAD_COLOR);
    src_lines = imread(image_path_lines, IMREAD_COLOR);

    cvtColor(src, gray, COLOR_BGR2GRAY);

    namedWindow("canny threashold", WINDOW_AUTOSIZE);

    createTrackbar("Min Threshold:", "canny threashold", &lowThreshold, max_lowThreshold, CannyThreshold);

    CannyThreshold(0, 0);

    waitKey(0);

    Canny(src_lines, dst, 50, 200, 3);
    vector<Vec2f>lines;
    HoughLines(dst, lines, 1, CV_PI / 180, 150, 0, 0); // runs the actual detection

    //draw lines
    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (-a));
        pt2.x = cvRound(x0 + 1000 * (-b));
        pt2.y = cvRound(y0 + 1000 * (-a));
        line(dst, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
    }

    imshow("Detected Lines (in red) - Standard Hough Line Transform", dst);

    waitKey(0);
}
static void CannyThreshold(int, void*) {
    blur(gray, detected_edges, Size(3, 3));
    Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio_, kernel_size);
    dst = Scalar::all(0);
    src.copyTo(dst, detected_edges);
    imshow("edges", dst);
}


/*
* Canny edge detection work by looking the value of the pixel gradient and comparing it with an upperbound and a lowerbound threshold
* pixel in between are accepted only if connected with a pixel that is above the upper threshold
*/

/*
* The Hough Line Transform is a transform used to detect straight lines.
* This operation consider the falmily of lines that can go through a point (considering colors),
* if adjacent points shares one line of the previously calculated family means that they are on the same line.
* the operation is performed plotting the family on line and finding intersection ()
*/
