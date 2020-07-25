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

    // ͼ��Ļ�����Ϣ
    int dims[3];
    reader->GetOutput()->GetDimensions(dims);

    //ͼ�������ֵ
    for (int k = 0; k < dims[2]; k++) {
        for (int j = 0; j < dims[1]; j++) {
            for (int i = 0; i < dims[0]; i++) {
                int* pixel = (int*)(imageCast->GetOutput()->GetScalarPointer(i, j, k)); // ��i�е�j�е�����ֵ
                img.at<int>(j, i) = int(*pixel); // ��j�е�i�е�����ֵ
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
    //�ļ����  
    intptr_t hFile;
    //�ļ���Ϣ  
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            //�������,�����б�  
            if ((fileinfo.attrib & _A_SUBDIR)) {
                //int strcmp(const char* s1,const char* s2)
                //��s1<s2ʱ������Ϊ������
                //��s1==s2ʱ������ֵ= 0��
                //��s1>s2ʱ������������
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    //�����Ŀ¼,���� 
                    getFloderFiles(p.assign(path).append("\\").append(fileinfo.name), pic_files);
            } else {
                //�����б� 
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
        // ����dicomͼ,ʹ��OpenCV��Mat���ͷ���
        dicomRead(file_path, img, reader);
        flip(img, img, 0);
        //DICOMͼ��Ƚ�����,����ֵ��Χ�󣬲���ֱ��ʹ��imshow()����ȥ���ӻ�����Ҫ���м򵥵Ĵ�������һ��
        dicomMat2GrayImage(img, img, colorWindow, colorLevel);
        imwrite(jpg_folder_path + "\\" + file_name + ".jpg", img);
    }
}

//int main() {
//    //�ýӿڹ�4����������һ���Ǵ����dicom���ļ��У��ڶ������������jpg���ļ��У�
//    //��������CT����Ĭ��3000�����ĸ���CT��λ��Ĭ��25��
//    //dicom�ļ����µ��ļ�������dcm�ļ����ͣ�������ת��
//    dicom2jpg("dicom", "jpg");
//}