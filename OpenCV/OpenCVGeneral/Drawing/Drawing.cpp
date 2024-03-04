#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

#include <iostream>

#define w 400

int main()
{
	Point p1;
	p1.x = 10;
	p1.y = 8;

	Point p2 = Point(200, 160);

	Scalar s = Scalar(255, 255, 255, 1); //BGRalpha

	Mat img = Mat::zeros(w, w, CV_8UC3);

	line(img, p1, p2, s);
	// a line can be drawed providing 2 points, a scalar with color 

	Point p3;
	p3.x = 300;
	p3.y = 8;

	Point p4 = Point(200, 160);

	line(img, p3, p4, s, 5, LineTypes::LINE_AA);
	// a line can be drawn providing 2 points, a scalar with color , the thickness, and the line type LINE_AA = line with anti alising

	int thickness = 2;
	int lineType = 8;
	int angle = 0;

	ellipse(img, Point(w / 2, w / 2), Size(w / 4, w / 16), angle, 0, 360, Scalar(255, 0, 0), thickness, lineType);

	//the ellipse can be drawn providing: the center, the size, the orientation angle, start angle, end angle, scalar for the color, thickness and line type

	circle(img, Point(100, 100), w / 32, Scalar(0, 0, 255), FILLED, LINE_AA);

	// the circle can be drawn providing: center, radius, scalar for the color, fill or not option, line type

	rectangle(img, Point(15, 60), Point(90, 100), Scalar(255, 0, 0), -1, LineTypes::LINE_AA);

	// rectagle can be drawn providing: two veritices, scalar for the color, fill or not option, line type

	Rect r = Rect(Point(30, 60), Point(200, 180));

	rectangle(img, r, Scalar(0, 255, 0), 1, LineTypes::LINE_AA);

	Point rookPoint[1][3];
	rookPoint[0][0] = p1;
	rookPoint[0][1] = p2;
	rookPoint[0][2] = p3;

	const Point* ppt[1] = { rookPoint[0] };
	int npt[] = { 20 };

	fillPoly(img, ppt, npt, 1, Scalar(0, 0, 255), LineTypes::LINE_AA);

	//image, text, origin, font type, scale, color, text thickness
	putText(img, "Testing text rendering", Point(20, 350), 0.8, 2, Scalar(0, 0, 255), 2, LineTypes::LINE_AA);

	//in open cv it is possible to get the final text size before rendering it with the function getTextSize

	//a poligon is a set of points, the fillPoly function need a pointer to the first element of the Point array, the number of points, scalar for the color, line type

	imshow("#", img);
	waitKey(0);
	return 0;
}

