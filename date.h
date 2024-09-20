#ifndef DATE_H
#define DATE_H



#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <opencv2/opencv.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


class date

{

private:

    int Id;
    Mat frame;
    Mat fon;
    vector<Point>  center;
    float distance(Point a, Point b);

public:

    date();
    Mat poisk_konturov(Mat fon, Mat frame); //обработка кадра
    void print();
    int update(Point r);// обновление ID

};
#endif // !DATE_H