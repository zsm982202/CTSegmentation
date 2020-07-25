#include "vtk2opencv.h"

using namespace cv;
using namespace std;


void vtk2opencv::dicomRead(vtkSmartPointer<vtkImageThreshold> threshould, vector<Mat>& imgVector) {
    int dims[3];
    threshould->GetOutput()->GetDimensions(dims);

    for (int k = 0; k < dims[2]; k++) {
        Mat img;
        img.create(512, 512, CV_8UC1);
        for (int j = 0; j < dims[1]; j++) {
            for (int i = 0; i < dims[0]; i++) {
                int* pixel = (int*)(threshould->GetOutput()->GetScalarPointer(i, j, k));
                if (*pixel > 0)
                    img.at<uchar>(j, i) = 255;
                else
                    img.at<uchar>(j, i) = 0;
            }
        }
        imgVector.push_back(img);
    }
}

void vtk2opencv::getTwoContours(Mat img, vector<vector<Point>> &contours) {
    threshold(img, img, 120, 255, THRESH_BINARY_INV);

    floodFill(img, Point(10, 10), Scalar(0));
    floodFill(img, Point(img.cols - 10, 10), Scalar(0));
    floodFill(img, Point(10, img.rows - 10), Scalar(0));
    floodFill(img, Point(img.cols - 10, img.rows - 10), Scalar(0));

    for (int i = 0; i < img.rows; i++) {
        img.at<uchar>(i, int(img.cols * (0.5 - 10.0 / 510))) = 0;
        img.at<uchar>(i, int(img.cols * (0.5 + 10.0 / 510))) = 0;
        img.at<uchar>(i, int(img.cols * (0.5 - 20.0 / 510))) = 0;
        img.at<uchar>(i, int(img.cols * (0.5 + 20.0 / 510))) = 0;
    }

    findContours(img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    for (vector < vector<Point>>::iterator it = contours.begin(); it != contours.end();) {
        bool isErase = false;
        vector<Point> contour = *it;
        for (Point p : contour) {
            if (p.y < 256) {
                it = contours.erase(it);
                isErase = true;
                break;
            }
        }
        if (!isErase)
            ++it;
    }
        

    sort(contours.begin(), contours.end(),
         [](const vector<Point>& lhs, const vector<Point>& rhs) {
        return contourArea(lhs) > contourArea(rhs);
    });
    contours.resize(2);
}

void vtk2opencv::getVectorContours(vtkSmartPointer<vtkImageThreshold> threshould, vector<vector<vector<Point>>>& contoursVector) {
    vector<Mat> imgVector;
    dicomRead(threshould, imgVector);
    for (Mat img : imgVector) {
        vector<vector<Point>> contours;
        getTwoContours(img, contours);
        contoursVector.push_back(contours);
    }
}