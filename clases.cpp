#include <iostream>
#include <opencv2/opencv.hpp>
#include <string.h>
#include "date.h"
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main()
{
    string path_f3 = "C:/Users/user/Desktop/fon4.png";
    Mat fon = imread(path_f3);//изображение без человека
    string path = "C:/Users/user/Desktop/chelovek.png";
    Mat chelovek = imread(path);//изображение без человека
    int id = 0;
    date Tracker;
    Mat frame;
    VideoCapture cap("C:/Users/user/Desktop/4.Camera 2017-05-29 16-23-04_137 [3m3s].avi");
    while (true) {
        cap.read(frame);
        Mat f=Tracker.poisk_konturov(fon, frame);
        imshow("vivep", f);
        waitKey(1);
    }


    return 0;
}

