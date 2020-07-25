#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <cstdio>
#include <QtWidgets/QPushButton>
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkImageActor.h"
#include "vtkDICOMImageReader.h"
#include "vtkImageShiftScale.h"

#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"

#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkImageActor.h"
#include "vtkImageShiftScale.h"
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkAutoInit.h>
#include <vtkImageData.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);
#include "vtkVolume16Reader.h"  
#include "vtkRenderWindowInteractor.h"   
#include "vtkMarchingCubes.h"  
#include "vtkStripper.h"  
#include "vtkActor.h"  
#include "vtkPolyDataMapper.h"  
#include "vtkProperty.h"  
#include "vtkCamera.h"  
#include "vtkBoxWidget.h"  
#include "vtkSmartPointer.h"  
#include "vtkTriangleFilter.h"  
#include "vtkMassProperties.h" 

#include "vtkInteractorStyleTrackballCamera.h"
#include <vtkImageThreshold.h>
namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = 0);
	~MainWindow();

private:
	Ui::MainWindow* ui;
	vtkSmartPointer<vtkDICOMImageReader> reader;
	vtkSmartPointer<vtkImageViewer2> imageViewer0;
	vtkSmartPointer<vtkImageViewer2> imageViewer1;
	vtkSmartPointer<vtkImageViewer2> imageViewer2;
	vtkSmartPointer<vtkImageThreshold> threshould;

	vtkSmartPointer<vtkDICOMImageReader> original_data;

	QString myPath;
	double* spacing;
	int* extent;
	int High;
	int Low;

	bool flagA = false;
	bool flagC = false;
	bool flagS = false;
	bool flagReset = false;
	bool flagChangeTh = false;
	bool flagVolumeRender = false;
	bool flagSurfaceRender = false;
	bool flagDenoise = false;
	bool flagThreshould = false;
	bool flagContourSegment = false;

	vtkSmartPointer<vtkRenderer> aRenderer1;
	vtkSmartPointer<vtkRenderWindow> renWin1;
	vtkSmartPointer<vtkRenderWindowInteractor> iren1;
	vtkSmartPointer<vtkRenderer> aRenderer2;
	vtkSmartPointer<vtkRenderWindow> renWin2;
	vtkSmartPointer<vtkRenderWindowInteractor> iren2;
	vtkSmartPointer<vtkRenderer> aRenderer3;
	vtkSmartPointer<vtkRenderWindow> renWin3;
	vtkSmartPointer<vtkRenderWindowInteractor> iren3;


public slots:
	void slotUpdateAxialSliceIndex(int);
	void slotUpdateCornalSliceIndex(int);
	void slotUpdateSagittalSliceIndex(int);

	void changeTh(int);
	void changeThL(int);
	void startRegionGrow();
	void onReadButtonClicked();
	void onThreshouldButtonClicked();
	void onContourSegmentButtonClicked();

	void volumeRender();
	void surfaceRender();

	void medianFilter();
	int median(int, int, int);
private slots:

	void onResetButtonClicked();
	void slice();
	//void open();
};

#endif // MAINWINDOW_H
