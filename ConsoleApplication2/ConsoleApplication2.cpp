#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void main()
{
    Mat frame;
    VideoCapture cap("C:/Users/user/Desktop/st/4.Camera 2017-05-29 16-23-04_137 [3m3s].avi");
    double alpha = 0.9;
    bool FirstTime = true;
    double beta = (1.0 - alpha);
    while (true) {
        Mat GrayFrame, CopyFrame, Fon, dst;
        cap.read(frame);
//Вычитание фона
        Mat copy = frame.clone();
        cvtColor(copy, GrayFrame, COLOR_RGB2GRAY);
//Устанавливаем первый кадр как фон, после изменяем фон с ипользованием смешивания
        if (FirstTime) {
            Fon = GrayFrame.clone();
            FirstTime = false;
        }
        else {
            addWeighted(GrayFrame, (1 - alpha), Fon, alpha, 0, Fon);
        }
        // Вычисляем изображение переднего плана
        absdiff(GrayFrame, Fon, dst);
        imshow("Camera 4", frame);
        //
        waitKey(1);
    }
    
}

