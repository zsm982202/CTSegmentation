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

#include <io.h>

void dicomRead(std::string inputFilename, cv::Mat& img, vtkSmartPointer<vtkDICOMImageReader>& reader);
void dicomMat2GrayImage(cv::Mat src, cv::Mat& dst, int colorWindow = 3000, int colorLevel = 25);
void getFloderFiles(std::string path, std::vector<std::string>& pic_files);
void dicom2jpg(std::string dcm_folder_path, std::string jpg_folder_path, int colorWindow = 3000, int colorLevel = 25);