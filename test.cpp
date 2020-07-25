#include "dicom2jpg.h"

int main() {
    //该接口共4个参数，第一个是存放着dicom的文件夹，第二个是用来存放jpg的文件夹，
    //第三个是CT窗宽，默认3000，第四个是CT窗位，默认25。
    //dicom文件夹下的文件必须是dcm文件类型，否则不能转换
    dicom2jpg("dicom", "jpg");
}