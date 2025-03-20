#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

string image_path = "..\\..\\images\\image-5.jpg";
Mat src, src_gray;

int thresh = 100;
RNG rng(12345);

void thresh_callback(int, void*);

int main()
{
    src = imread(image_path, IMREAD_COLOR);

    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));

    namedWindow("Convex Hull");

    const int max_thresh = 255;
    createTrackbar("Canny thresh:", "Convex Hull", &thresh, max_thresh, thresh_callback);
    thresh_callback(0, 0);

    waitKey();

}

void thresh_callback(int, void*) {
    Mat sample = src_gray;



   /* Mat sample;
    Canny(src_gray, sample, thresh, thresh * 2);*/
    vector<vector<Point>> contours;

    //use the contours provided by the canny function result
    findContours(sample, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> hull(contours.size());

    for (size_t i = 0; i < contours.size(); i++)
    {
        convexHull(contours[i], hull[i]);
    }
    Mat drawing = Mat::zeros(sample.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours, (int)i, color);
        drawContours(drawing, hull, (int)i, color);
    }
    imshow("Hull demo", drawing);
}

/*
* the convex hull is the smallest convex subset set that contains the set itself.
* The convex hull of a given set X may be defined as hte unique minimal convex set containing X
* 
* the canny threashold is usefull if we desire to find all the small contours of a complex image.
* if we need to find the convex hull of an object in an imege, for example a single object on a flat background,
* the canny thresholding does not guarantee good result because it will find out all the lines in the object itself
*/
