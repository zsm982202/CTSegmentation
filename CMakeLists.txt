cmake_minimum_required (VERSION 3.8)

project ("dicom2jpg")

set(CMAKE_CXX_FLAGS "-std=c++11")

set(OpenCV_DIR "F:/opencv3/source/opencv-3.4.10/build")
find_package(OpenCV 3 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

add_executable (${PROJECT_NAME} "test.cpp" "dicom2jpg.h" "dicom2jpg.cpp")
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${VTK_LIBRARIES})

