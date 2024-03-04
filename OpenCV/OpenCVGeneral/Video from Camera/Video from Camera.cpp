#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int delay = (1000/30);

int main()
{
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "Cannot open Camera" << endl;
    }

    cout << delay << endl;

    namedWindow("Camera", WINDOW_AUTOSIZE);

    Mat frame;
    while (true)
    {
        
        cap >> frame;
        if (frame.empty()) {
            cout << "problems!!!" << endl;
            exit(EXIT_FAILURE);
        }

        cv::imshow("Camera", frame);
        cv::waitKey(delay);
    }

}

