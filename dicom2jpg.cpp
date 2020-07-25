#include "dicom2jpg.h"

using namespace cv;
using namespace std;

void dicomRead(string inputFilename, Mat& img, vtkSmartPointer<vtkDICOMImageReader>& reader) {
    img.create(512, 512, CV_32SC1);
    vtkSmartPointer<vtkImageCast> imageCast = vtkSmartPointer<vtkImageCast>::New();
    reader->SetFileName(inputFilename.c_str());
    reader->Update();

    imageCast->SetInputConnection(reader->GetOutputPort());
    imageCast->SetOutputScalarTypeToInt();
    imageCast->Update();

    // 图像的基本信息
    int dims[3];
    reader->GetOutput()->GetDimensions(dims);

    //图像的像素值
    for (int k = 0; k < dims[2]; k++) {
        for (int j = 0; j < dims[1]; j++) {
            for (int i = 0; i < dims[0]; i++) {
                int* pixel = (int*)(imageCast->GetOutput()->GetScalarPointer(i, j, k)); // 第i列第j行的像素值
                img.at<int>(j, i) = int(*pixel); // 第j行第i列的像素值
            }
        }
    }
}

void dicomMat2GrayImage(Mat src, Mat& dst, int colorWindow /*= 3000*/, int colorLevel /*= 25*/) {
    if (colorLevel - colorWindow / 2 < -1000)
        colorWindow = 2050;
    float a = 256.0 / colorWindow;
    float b = 128.0 - 256.0 * colorLevel / colorWindow + a;
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            src.at<int>(i, j) = a * src.at<int>(i, j) + b;
        }
    }
    src.convertTo(dst, CV_8UC1);
}

void getFloderFiles(string path, vector<string>& pic_files) {
    //文件句柄  
    intptr_t hFile;
    //文件信息  
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            //如果不是,加入列表  
            if ((fileinfo.attrib & _A_SUBDIR)) {
                //int strcmp(const char* s1,const char* s2)
                //当s1<s2时，返回为负数；
                //当s1==s2时，返回值= 0；
                //当s1>s2时，返回正数。
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    //如果是目录,迭代 
                    getFloderFiles(p.assign(path).append("\\").append(fileinfo.name), pic_files);
            } else {
                //加入列表 
                pic_files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

void dicom2jpg(string dcm_folder_path, string jpg_folder_path, int colorWindow /*= 3000*/, int colorLevel /*= 25*/) {
    vector<string> files_path;
    getFloderFiles(dcm_folder_path, files_path);
    int size = files_path.size();
    for (int i = 0; i < size; i++) {
        string file_path = files_path[i];
        if (file_path.rfind(".") == -1)
            continue;
        string file_extension = file_path.substr(file_path.rfind(".") + 1);
        if (file_extension != "dcm")
            continue;
        string file_name = file_path.substr(file_path.rfind("\\") + 1, file_path.rfind(".") - file_path.rfind("\\") - 1);
        Mat img;
        vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
        // 读入dicom图,使用OpenCV的Mat类型返回
        dicomRead(file_path, img, reader);
        flip(img, img, 0);
        //DICOM图像比较特殊,像素值范围大，不能直接使用imshow()函数去可视化，需要进行简单的处理。量化一下
        dicomMat2GrayImage(img, img, colorWindow, colorLevel);
        imwrite(jpg_folder_path + "\\" + file_name + ".jpg", img);
    }
}

//int main() {
//    //该接口共4个参数，第一个是存放着dicom的文件夹，第二个是用来存放jpg的文件夹，
//    //第三个是CT窗宽，默认3000，第四个是CT窗位，默认25。
//    //dicom文件夹下的文件必须是dcm文件类型，否则不能转换
//    dicom2jpg("dicom", "jpg");
//}