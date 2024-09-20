#include "date.h"
#include <math.h>

// всомогательные функции
// нахождение расстояния между точками

float date:: distance(Point a, Point b)
{
    float dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// конструктор класса
date::date() 

{
    Id = 0;
    center = {};
}


Mat date::poisk_konturov(Mat fon, Mat frame) {
    Mat vichet;//матрица для хранения вычитаемого кодра из фона
    absdiff(frame, fon, vichet);
    Mat tresh; // матрица для бинарного изображения
    Mat gray_scale;// матрица изображения в градациях серого
    vector<vector<Point> > contours; //вектор для хранения контуров
    vector<vector<int>> detections;
    //   Преобразование изображения с движущемся человеком в оттенки серого
    cvtColor(vichet, gray_scale, COLOR_BGR2GRAY);
    threshold(gray_scale, tresh, 50, 255, THRESH_BINARY); // Настройка порогового значения 
    findContours(tresh, contours, RETR_TREE, CHAIN_APPROX_SIMPLE); //поиск контуров
    vector<vector<Point> > contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    double maxArea = 0;
    int ind = 0;
    for (size_t i = 0; i < contours.size(); i++)
    {
        // находим максимальную площадь контура и его индекс
        if (contourArea(contours[i]) > maxArea) {
            maxArea = contourArea(contours[i]);
            ind = i;
        }
        approxPolyDP(contours[i], contours_poly[i], 1, true); // приближение крайних контуров
        boundRect[i] = boundingRect(contours_poly[i]);// Получаем ограничивающую рамку этого контура
    }
    

    for (size_t i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(0, 0, 0);// цвет рамки = зеленый
        // изображаем только максимальную рамку и отсеиваем маленькие контуры
        if ((i == ind) && (contourArea(contours[i]) > 100)) {
            Scalar font_Color(0, 0, 0);//цвет надписи//
            Point y = boundRect[i].tl();
            Point x = boundRect[i].br();

            RotatedRect centr = minAreaRect(contours[i]); // поиск центра контура 
            Point r = centr.center;
            update(r);
            //Положение текста(начало запичи х и у)//
            int font_size = 1;//Размер шрифта//
            
            int font_weight = 2;//толщина надписи//
            putText(frame,to_string(Id), (x, y), FONT_HERSHEY_COMPLEX, font_size, font_Color, font_weight);//Нанесение текста на изображение//
            rectangle(frame, boundRect[i].tl(), boundRect[i].br(), color, 2);
            circle(frame, centr.center,15, font_Color, FILLED); //изображение центра
            
            
        }

    }

    return frame;
}

int date::update(Point r) {
    if (center.empty()) {
        center.emplace_back(r);
        return Id;
    }
    else {
        float dist; // расстояние между точками
        dist = distance(r, center.back());
        if (dist < 100) {
            center.emplace_back(r);
            return Id;
        }
        else {
            Id += 1;
            center.clear();
            return Id;
        }
    }
    
}

void date::print()

{
	imshow("picture", frame);
	waitKey();
}


