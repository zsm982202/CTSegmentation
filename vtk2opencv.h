#pragma once
#include <iostream>
#include <string>
#include <vector>
//
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkImageCast.h>
#include <vtkDICOMImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageData.h>
#include <vtkCoordinate.h>
#include <vtkImageThreshold.h>

#include <io.h>


class vtk2opencv {
public:
	void dicomRead(vtkSmartPointer<vtkImageThreshold> threshould, std::vector<cv::Mat>& imgVector);
	//void dicomMat2GrayImage(cv::Mat src, cv::Mat& dst, int colorWindow = 3000, int colorLevel = 25);
	void getTwoContours(cv::Mat img, std::vector<std::vector<cv::Point>>& contours);
	void getFloderFiles(std::string path, std::vector<std::string>& pic_files);
	void getVectorContours(vtkSmartPointer<vtkImageThreshold> threshould, std::vector<std::vector<std::vector<cv::Point>>>& contoursVector);
};