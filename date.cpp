#include "date.h"
#include <math.h>

// �������������� �������
// ���������� ���������� ����� �������

float date:: distance(Point a, Point b)
{
    float dx = a.x - b.x, dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// ����������� ������
date::date() 

{
    Id = 0;
    center = {};
}


Mat date::poisk_konturov(Mat fon, Mat frame) {
    Mat vichet;//������� ��� �������� ����������� ����� �� ����
    absdiff(frame, fon, vichet);
    Mat tresh; // ������� ��� ��������� �����������
    Mat gray_scale;// ������� ����������� � ��������� ������
    vector<vector<Point> > contours; //������ ��� �������� ��������
    vector<vector<int>> detections;
    //   �������������� ����������� � ���������� ��������� � ������� ������
    cvtColor(vichet, gray_scale, COLOR_BGR2GRAY);
    threshold(gray_scale, tresh, 50, 255, THRESH_BINARY); // ��������� ���������� �������� 
    findContours(tresh, contours, RETR_TREE, CHAIN_APPROX_SIMPLE); //����� ��������
    vector<vector<Point> > contours_poly(contours.size());
    vector<Rect> boundRect(contours.size());
    double maxArea = 0;
    int ind = 0;
    for (size_t i = 0; i < contours.size(); i++)
    {
        // ������� ������������ ������� ������� � ��� ������
        if (contourArea(contours[i]) > maxArea) {
            maxArea = contourArea(contours[i]);
            ind = i;
        }
        approxPolyDP(contours[i], contours_poly[i], 1, true); // ����������� ������� ��������
        boundRect[i] = boundingRect(contours_poly[i]);// �������� �������������� ����� ����� �������
    }
    

    for (size_t i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(0, 0, 0);// ���� ����� = �������
        // ���������� ������ ������������ ����� � ��������� ��������� �������
        if ((i == ind) && (contourArea(contours[i]) > 100)) {
            Scalar font_Color(0, 0, 0);//���� �������//
            Point y = boundRect[i].tl();
            Point x = boundRect[i].br();

            RotatedRect centr = minAreaRect(contours[i]); // ����� ������ ������� 
            Point r = centr.center;
            update(r);
            //��������� ������(������ ������ � � �)//
            int font_size = 1;//������ ������//
            
            int font_weight = 2;//������� �������//
            putText(frame,to_string(Id), (x, y), FONT_HERSHEY_COMPLEX, font_size, font_Color, font_weight);//��������� ������ �� �����������//
            rectangle(frame, boundRect[i].tl(), boundRect[i].br(), color, 2);
            circle(frame, centr.center,15, font_Color, FILLED); //����������� ������
            
            
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
        float dist; // ���������� ����� �������
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


