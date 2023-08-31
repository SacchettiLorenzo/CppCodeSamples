#include <iostream>
#include <unordered_map>
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <deque>

using namespace cv;

struct Color {
    uchar R, G, B;

    Color() {
        R = 0;
        G = 0;
        B = 0;
    }

    bool operator == (const Color& c) const {
        return (R == c.R && G == c.G && B == c.B);
    }

};

template <>
struct std::hash<Color>
{
    std::size_t operator()(const Color& k) const
    {
        using std::hash;
        // Compute individual hash values for first,
        // second and third and combine them using XOR
        // and bit shifting:
        return ((hash<uchar>()(k.B)
            ^ (hash<uchar>()(k.G) << 1)) >> 1)
            ^ (hash<uchar>()(k.R) << 1);
    }
};

struct ColorAmmount {
    Color c;
    int ammount;

    ColorAmmount(Color k, int a) : c(k), ammount(a) {}
};

//std::string file_path = "C:\\Users\\VGpc\\Pictures\\Image samples\\800x600\\image_6.jpg";
void createLookupTable(uchar* lookupTable, int lookupTableLenght, int ratio);
void applyLookupTable(uchar* LookupTable, Mat& img);
void fetchColors(Mat& img, std::unordered_map<Color, int>& colorList);
void findGreatestColors(std::deque<ColorAmmount>& colorQue, std::unordered_map<Color, int> colorList, int numOfColours);
void drawQue(Mat& img, Mat& result, std::deque<ColorAmmount>& colorQue, int imgincrease);

int main(int argc, char* argv[])
{
    const char* file_path;
    int ratio = 40;
    int numOfDifferentColors = 10;


    if (argc >= 2) file_path = argv[1];
    else return 0;
    if (argc >= 3) ratio = atoi(argv[2]);
    if (argc >= 4) numOfDifferentColors = atoi(argv[3]);

    Mat img = imread(file_path, IMREAD_ANYCOLOR);
    int imgincrease = img.rows / 15;
    Mat result = Mat(img.rows + imgincrease, img.cols, img.type());
    img.copyTo(result(Rect(Point(0, 0), Point(img.cols, img.rows))));

    namedWindow("Result", WINDOW_AUTOSIZE);

    //imshow("Original image" , img);

    uchar lookupTable[256];

    createLookupTable(lookupTable, 256, ratio);
    applyLookupTable(lookupTable, img);

    std::unordered_map<Color, int> colorList;

    fetchColors(img, colorList);

    std::deque<ColorAmmount> que;

    findGreatestColors(que, colorList, numOfDifferentColors);

    drawQue(img, result, que, imgincrease);

    imshow("Result", result);

    std::vector<int> compression_params;
    compression_params.push_back(IMWRITE_JPEG_OPTIMIZE);
    compression_params.push_back(9);
    try
    {
        result = imwrite("result.jpg", result, compression_params);
    }
    catch (const cv::Exception& ex)
    {
        std::cout << "Exception converting image to PNG format: " << ex.what() << std::endl;
    }


    waitKey(0);
    return 0;

}



void createLookupTable(uchar* lookupTable, int lookupTableLenght, int ratio) {
    if (ratio == 0)ratio = 1;
    for (size_t i = 0; i < lookupTableLenght; i++)
    {
        lookupTable[i] = (uchar)(ratio * (i / ratio));
    }
}

void applyLookupTable(uchar* LookupTable, Mat& img) {

    int rows = img.rows;
    int cols = img.cols * img.channels();

    if (img.isContinuous()) {
        cols *= rows;
        rows = 1;
    }

    uchar* p;
    for (size_t i = 0; i < rows; i++)
    {
        p = img.ptr<uchar>(i);
        for (size_t j = 0; j < cols; j++)
        {
            p[j] = LookupTable[p[j]];
        }
    }
}

void fetchColors(Mat& img, std::unordered_map<Color, int>& colorList) {
    int rows = img.rows;
    int cols = img.cols;

    std::unordered_map<Color, int>::iterator it;

    for (size_t i = 0; i < rows; i++)
    {

        for (size_t j = 0; j < cols; j++)
        {
            Color c;
            c.B = img.at<Vec3b>(i, j)[0];
            c.G = img.at<Vec3b>(i, j)[1];
            c.R = img.at<Vec3b>(i, j)[2];

            it = colorList.find(c);
            if (it == colorList.end()) {
                colorList.insert(std::make_pair(c, 1));
            }
            else {
                it->second = it->second + 1;
            }
        }
    }
}

void findGreatestColors(std::deque<ColorAmmount>& colorQue, std::unordered_map<Color, int> colorList, int numOfColours) {

    Color currentGreatestColor = Color();
    int currentGreatestColorAmmount = 0;

    if (colorList.size() >= numOfColours)
        for (size_t i = 0; i < numOfColours + 1; i++)
        {
            for (auto i : colorList) {
                if (i.second > currentGreatestColorAmmount) {
                    currentGreatestColorAmmount = i.second;
                    currentGreatestColor = i.first;
                }
            }
            colorList.erase(colorList.find(currentGreatestColor));
            colorQue.push_back(ColorAmmount(currentGreatestColor, currentGreatestColorAmmount));
            currentGreatestColor = Color();
            currentGreatestColorAmmount = 0;
        }

}

void drawQue(Mat& img, Mat& result, std::deque<ColorAmmount>& colorQue, int imgincrease) {

    int totalAmmount = 0;
    for (auto i : colorQue) {
        totalAmmount += i.ammount;
    }

    int partial = 0;
    Point a = Point(0, img.rows);
    Point b = Point(0, img.rows + imgincrease);
    for (auto i : colorQue) {
        partial = nearbyint(i.ammount * static_cast<float>(100) / totalAmmount);
        partial = img.cols / 100 * partial;
        b = Point(b.x + partial, b.y);
        rectangle(result, a, b, Scalar(i.c.B, i.c.G, i.c.R), -1, LineTypes::LINE_AA);
        a = Point(a.x + partial, a.y);
        b = Point(b.x + partial, b.y);
    }
}

