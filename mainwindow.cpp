#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"

#include <opencv2/opencv.hpp>
#include "vtk2opencv.h"

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


#include "vtkSmartPointer.h"
#include "vtkPNGReader.h"


#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkActor.h>
// headers needed for this example
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>

#include <vtkImageThreshold.h>

#include <vtkBMPReader.h>
using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);
	connect(ui->readButton, SIGNAL(clicked()), this, SLOT(onReadButtonClicked()));
	connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(onResetButtonClicked()));
	connect(ui->threshouldButton, SIGNAL(clicked()), this, SLOT(onThreshouldButtonClicked()));
	connect(ui->contourSegmentButton, SIGNAL(clicked()), this, SLOT(onContourSegmentButtonClicked()));

	connect(ui->volumeRenderButton, SIGNAL(clicked()), this, SLOT(volumeRender()));
	connect(ui->surfaceRenderButton, SIGNAL(clicked()), this, SLOT(surfaceRender()));

	connect(ui->denoiseButton, SIGNAL(clicked()), this, SLOT(medianFilter()));
	
	connect(ui->horizontalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(changeTh(int)));
	//connect(ui->horizontalScrollBar_2, SIGNAL(valueChanged(int)), this, SLOT(changeThL(int)));

	connect(ui->verticalScrollBar_3, SIGNAL(valueChanged(int)), this, SLOT(slotUpdateAxialSliceIndex(int)));
	connect(ui->verticalScrollBar_2, SIGNAL(valueChanged(int)), this, SLOT(slotUpdateCornalSliceIndex(int)));
	connect(ui->verticalScrollBar, SIGNAL(valueChanged(int)), this, SLOT(slotUpdateSagittalSliceIndex(int)));
}


MainWindow::~MainWindow() {
	delete ui;
}

QString GetFileDirDLG() {
	char* title = "Select Directory";
	char* defaultPath = "F:\\vs_c++_workspace\\opencv\\dicom2jpg\\dicom1";
	char* defaultDIR = defaultPath;
	return QFileDialog::getExistingDirectory(
		0,
		QString::fromLocal8Bit(title),
		QString::fromLocal8Bit(defaultDIR)
	);
}

void MainWindow::onReadButtonClicked() {
	myPath = GetFileDirDLG();

	VTK_MODULE_INIT(vtkRenderingOpenGL2);
	VTK_MODULE_INIT(vtkInteractionStyle);
	VTK_MODULE_INIT(vtkRenderingFreeType);
	//VTK_MODULE_INIT(vtkInteractionStyle);
	// Read all the DICOM files in the specified directory.
	reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	reader->SetDirectoryName(myPath.toStdString().c_str());//myPath.toStdString().c_str()E:\\medicalimages\\lung00
	reader->Update();

	int dims[3];
	reader->GetOutput()->GetDimensions(dims);

	if (dims[2] == 0) {
		ui->textBrowser->setText("Dicom files open failed");
		return;
	}

	extent = reader->GetOutput()->GetExtent();
	ui->verticalScrollBar_3->setMaximum(extent[5]);
	ui->horizontalScrollBar->setMaximum(1024);
	ui->horizontalScrollBar->setMinimum(-1024);
	High = -512;
	Low = -1024;
	ui->horizontalScrollBar->setValue(High);
	
	original_data = vtkSmartPointer<vtkDICOMImageReader>::New();
	original_data = reader;

	threshould = vtkSmartPointer<vtkImageThreshold>::New();
	threshould->SetInputConnection(reader->GetOutputPort());

	aRenderer1 = vtkSmartPointer< vtkRenderer >::New();
	renWin1 = ui->qvtkWidget_Volume_4->GetRenderWindow();
	iren1 = vtkSmartPointer< vtkRenderWindowInteractor >::New();
	iren1->SetRenderWindow(renWin1);
	aRenderer2 = vtkSmartPointer< vtkRenderer >::New();
	renWin2 = ui->qvtkWidget_Volume_3->GetRenderWindow();
	iren2 = vtkSmartPointer< vtkRenderWindowInteractor >::New();
	iren2->SetRenderWindow(renWin2);
	aRenderer3 = vtkSmartPointer< vtkRenderer >::New();
	renWin3 = ui->qvtkWidget_Volume_2->GetRenderWindow();
	iren3 = vtkSmartPointer< vtkRenderWindowInteractor >::New();
	iren3->SetRenderWindow(renWin3);
	imageViewer0 = vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer0->SetInputConnection(threshould->GetOutputPort());
	imageViewer0->SetSliceOrientationToXY();//修改参数为0，1，2可分别得到不同方向的切片
	imageViewer0->SetupInteractor(iren1);
	imageViewer0->SetRenderWindow(renWin1);
	imageViewer0->SetRenderer(aRenderer1);
	imageViewer0->SetColorLevel(25);
	imageViewer0->SetColorWindow(3000);
	imageViewer0->GetRenderer()->ResetCamera();
	imageViewer0->GetRenderer()->GetActiveCamera()->Roll(0);
	imageViewer0->GetRenderer()->GetActiveCamera()->Yaw(180);
	imageViewer0->GetRenderer()->GetActiveCamera()->Elevation(180);
	imageViewer0->GetRenderer()->GetActiveCamera()->Zoom(6.0);

	imageViewer1 = vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer1->SetInputConnection(threshould->GetOutputPort());
	imageViewer1->SetSliceOrientation(1);//修改参数为0，1，2可分别得到不同方向的切片
	imageViewer1->SetupInteractor(iren2);
	imageViewer1->SetRenderWindow(renWin2);
	imageViewer1->SetRenderer(aRenderer2);
	imageViewer1->SetColorLevel(25);
	imageViewer1->SetColorWindow(3000);
	imageViewer1->GetRenderer()->ResetCamera();
	imageViewer1->GetRenderer()->GetActiveCamera()->Roll(180);
	imageViewer1->GetRenderer()->GetActiveCamera()->ParallelProjectionOn();
	imageViewer1->GetRenderer()->GetActiveCamera()->Elevation(180);
	imageViewer1->GetRenderer()->GetActiveCamera()->Zoom(1.0);

	imageViewer2 = vtkSmartPointer<vtkImageViewer2>::New();
	imageViewer2->SetInputConnection(threshould->GetOutputPort());
	imageViewer2->SetSliceOrientation(0);//修改参数为0，1，2可分别得到不同方向的切片
	imageViewer2->SetupInteractor(iren3);
	imageViewer2->SetRenderWindow(renWin3);
	imageViewer2->SetRenderer(aRenderer3);
	imageViewer2->SetColorLevel(25);
	imageViewer2->SetColorWindow(3000);
	imageViewer2->GetRenderer()->ResetCamera();
	imageViewer2->GetRenderer()->GetActiveCamera()->Roll(180);
	imageViewer2->GetRenderer()->GetActiveCamera()->ParallelProjectionOn();
	imageViewer2->GetRenderer()->GetActiveCamera()->Elevation(180);
	imageViewer2->GetRenderer()->GetActiveCamera()->Zoom(1.0);
	slice();

	flagReset = true;
	flagChangeTh = true;
	flagVolumeRender = true;
	flagSurfaceRender = true;
	flagThreshould = true;
	flagContourSegment = true;

	ui->textBrowser->setText("Image has been load successfully");
}

void MainWindow::onResetButtonClicked() {
	if (!flagReset)
		return;

	reader->SetDirectoryName(myPath.toStdString().c_str());
	reader->Update();
	threshould = vtkSmartPointer<vtkImageThreshold>::New();
	threshould->SetInputConnection(reader->GetOutputPort());

	slice();
	ui->textBrowser->setText("Reset OK");
}

void MainWindow::slice() {
	/////////////////////////////////////////////以下为切面显示
	// Visualize
	spacing = reader->GetDataSpacing();
	flagA = true;
	imageViewer0->SetInputConnection(threshould->GetOutputPort());
	imageViewer0->SetSliceOrientationToXY();//修改参数为0，1，2可分别得到不同方向的切片,2
	imageViewer0->Render();
	imageViewer0->SetSlice(extent[5] / 2);
	ui->verticalScrollBar_3->setValue(extent[5] / 2);

	///====================================
	flagC = true;
	imageViewer1->SetInputConnection(threshould->GetOutputPort());
	imageViewer1->SetSliceOrientationToXZ();//修改参数为0，1，2可分别得到不同方向的切片,1

	imageViewer1->Render();
	imageViewer1->SetSlice(extent[3] / 2);
	ui->verticalScrollBar_2->setValue(extent[3] / 2);

	//===========================================
	flagS = true;
	imageViewer2->SetInputConnection(threshould->GetOutputPort());
	//imageViewer2->SetSliceOrientation(0);//修改参数为0，1，2可分别得到不同方向的切片,0
	imageViewer2->SetSliceOrientationToYZ();

	imageViewer2->Render();
	imageViewer2->SetSlice(extent[1] / 2);
	ui->verticalScrollBar->setValue(extent[1] / 2);
}



void MainWindow::slotUpdateAxialSliceIndex(int a) {
	if (flagA) {
		imageViewer0->SetSlice(a);
	}
}

void MainWindow::slotUpdateCornalSliceIndex(int a) {
	if (flagC) {
		imageViewer1->SetSlice(a);
	}
}

void MainWindow::slotUpdateSagittalSliceIndex(int a) {
	if (flagS) {
		imageViewer2->SetSlice(a);
	}
}

void MainWindow::onContourSegmentButtonClicked() {
	if (!flagContourSegment)
		return;

	threshould->ThresholdByUpper(High);
	threshould->SetInValue(1024);
	threshould->SetOutValue(-1024);
	threshould->Update();

	int dims[3];
	threshould->GetOutput()->GetDimensions(dims);

	vector<vector<vector<Point>>> contoursVector;
	vtk2opencv v;
	v.getVectorContours(threshould, contoursVector);

	for (int k = 0; k < dims[2]; k++) {
		for (int j = 0; j < dims[1]; j++) {
			for (int i = 0; i < dims[0]; i++) {
				int* pixel = (int*)(threshould->GetOutput()->GetScalarPointer(i, j, k));
				*pixel = -1024;
				*(pixel + 1) = -1024;
				*(pixel + 2) = -1024;
			}
		}
	}
	
	for (int k = 0; k < contoursVector.size(); k++) {
		vector<vector<Point>> contours = contoursVector[k];
		for (vector<Point> contour : contours) {
			for (Point p : contour) {
				int* pixel = (int*)(threshould->GetOutput()->GetScalarPointer(p.x, p.y, k));
				*pixel = 1024;
				*(pixel + 1) = 1024;
				*(pixel + 2) = 1024;
			}
		}
	}

	threshould->Update();

	slotUpdateAxialSliceIndex(0);
	slotUpdateCornalSliceIndex(0);
	slotUpdateSagittalSliceIndex(0);

	slice();
	ui->textBrowser->setText("Segment OK");
}

void MainWindow::medianFilter() {
	if (!flagDenoise)
		return;

	int dims[3];
	int upperNum, upperNum2, upperNum3, upperNum4;
	QString upper, upper2, upper3, upper4;
	upper = ui->textEdit->document()->toPlainText();
	upperNum = upper.toInt();
	upper2 = ui->textEdit_2->document()->toPlainText();
	upperNum2 = upper2.toInt();
	upper3 = ui->textEdit_3->document()->toPlainText();
	upperNum3 = upper3.toInt();
	upper4 = ui->textEdit_4->document()->toPlainText();
	upperNum4 = upper4.toInt();
	reader->GetOutput()->GetDimensions(dims);

	for (int k = 0; k < dims[2]; k++) {
		for (int j = 0; j < dims[1]; j++) {
			for (int i = 0; i < dims[0]; i++) {

				short* pixel = (short*)(threshould->GetOutput()->GetScalarPointer(i, j, k));
				if (j < upperNum2 || j > upperNum4)
					*pixel = -1024;
				if (i < upperNum || i > upperNum3)
					*pixel = -1024;

				if ((j > 5) && (j < dims[1] - 6)) {
					short* pixel2 = (short*)(threshould->GetOutput()->GetScalarPointer(i, j + 5, k));
					short* pixel3 = (short*)(threshould->GetOutput()->GetScalarPointer(i, j - 5, k));
					if ((*pixel2 < -500) && (*pixel3 < -500))
						*pixel = -1024;
				}
			}

		}
	}
	threshould->Update();
	slice();
}

int MainWindow::median(int i, int j, int k) {
	int num_one, num_zero;
	num_one = 0;
	num_zero = 0;
	for (int x = i - 1; x < i + 2; x++) {
		for (int y = j - 1; y < j + 2; y++) {
			for (int z = k - 1; z < k + 2; z++) {
				short* pixel = (short*)(threshould->GetOutput()->GetScalarPointer(x, y, z));
				if (*pixel == 0)
					num_zero++;
				else
					num_one++;

			}
		}

	}
	if (num_one > num_zero)
		return 1;
	return 0;
}

void MainWindow::onThreshouldButtonClicked() {
	if (!flagThreshould)
		return;

	ui->textBrowser->setText("Threshold OK");
	threshould->ThresholdByUpper(High);
	threshould->SetInValue(1024);
	threshould->SetOutValue(-1024);
	threshould->Update(); //算法执行后必须添加更新消息
	slice();
}
void MainWindow::changeTh(int a) {
	if (!flagChangeTh)
		return;

	High = a;
	threshould->SetInputConnection(reader->GetOutputPort());
	threshould->ThresholdByUpper(High);
	threshould->SetInValue(1024);
	threshould->SetOutValue(-1024);
	const QString str = QString::number(a);
	ui->textBrowser_2->setText(str);
	threshould->Update(); //算法执行后必须添加更新消息！！！
	// slice();
}

void MainWindow::changeThL(int a) {
	if (!flagChangeTh)
		return;

	Low = a;
	threshould->SetInputConnection(reader->GetOutputPort());
	threshould->ThresholdByLower(Low);
	threshould->SetInValue(1024);
	threshould->SetOutValue(-1024);
	const QString str = QString::number(a);
	threshould->Update(); //算法执行后必须添加更新消息！！！
	// slice();
}

#include <vtkSmartPointer.h>  
#include <vtkStructuredPoints.h>  
#include <vtkStructuredPointsReader.h>  
#include <vtkFixedPointVolumeRayCastMapper.h>  
#include <vtkColorTransferFunction.h>  
#include <vtkPiecewiseFunction.h>  
#include <vtkRenderer.h>  
#include <vtkRenderWindow.h>  
#include <vtkRenderWindowInteractor.h>  
#include <vtkVolumeProperty.h>  
#include <vtkAxesActor.h>  
#include <vtkOrientationMarkerWidget.h>  

void MainWindow::volumeRender() {
	if (!flagVolumeRender)
		return;

	VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);
	vtkSmartPointer<vtkFixedPointVolumeRayCastMapper> volumeMapper =
		vtkSmartPointer<vtkFixedPointVolumeRayCastMapper>::New();
	//volumeMapper->SetInputData(reader->GetOutput());
	volumeMapper->SetInputConnection(threshould->GetOutputPort());
	volumeMapper->SetBlendModeToComposite();
	volumeMapper->SetSampleDistance(0.3);
	volumeMapper->AutoAdjustSampleDistancesOff();

	//设置光线采样距离  
	//volumeMapper->SetSampleDistance(volumeMapper->GetSampleDistance()*4);  
	//设置图像采样步长  
	//volumeMapper->SetAutoAdjustSampleDistances(0);  
	//volumeMapper->SetImageSampleDistance(4);  
	/*************************************************************************/
	vtkSmartPointer<vtkVolumeProperty> volumeProperty =
		vtkSmartPointer<vtkVolumeProperty>::New();
	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->ShadeOn();  //打开或者关闭阴影测试  
	volumeProperty->SetAmbient(0.2);
	volumeProperty->SetDiffuse(1.2);  //漫反射  
	volumeProperty->SetSpecular(0.1); //镜面反射  
	volumeProperty->SetSpecularPower(10);
	//设置不透明度  
	vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity =
		vtkSmartPointer<vtkPiecewiseFunction>::New();
	//compositeOpacity->AddPoint(-500, 0.1);
	compositeOpacity->AddPoint(70, 0.00);
	compositeOpacity->AddPoint(90, 0.40);
	compositeOpacity->AddPoint(180, 0.60);

	//double mAirShiftValue = 0;
	//double opacity = 1.0;
	//compositeOpacity->AddPoint(-584.658874 + mAirShiftValue, opacity);
	//compositeOpacity->AddPoint(-382.6592407 + mAirShiftValue, opacity);
	//compositeOpacity->AddPoint(-237.658386230468754 + mAirShiftValue, opacity);
	volumeProperty->SetScalarOpacity(compositeOpacity); //设置不透明度传输函数  
	//设置梯度不透明属性  

	vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity =
		vtkSmartPointer<vtkPiecewiseFunction>::New();
	volumeGradientOpacity->AddPoint(10, 0.0);
	volumeGradientOpacity->AddPoint(90, 0.5);
	volumeGradientOpacity->AddPoint(100, 1.0);
	volumeProperty->SetGradientOpacity(volumeGradientOpacity);//设置梯度不透明度效果对比  
	//设置颜色属性  
	vtkSmartPointer<vtkColorTransferFunction> color =
		vtkSmartPointer<vtkColorTransferFunction>::New();
	//color->AddRGBPoint(0.000, 0.00, 0.00, 0.00);
	color->AddRGBPoint(64.00, 1.00, 0.52, 0.30);
	//color->AddRGBPoint(190.0, 1.00, 1.00, 1.00);
	//color->AddRGBPoint(220.0, 0.20, 0.20, 0.20);
	volumeProperty->SetColor(color);
	/********************************************************************************/
	vtkSmartPointer<vtkVolume> volume =
		vtkSmartPointer<vtkVolume>::New();
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);

	vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();
	ren->SetBackground(0, 0, 0);
	ren->AddVolume(volume);

	vtkSmartPointer<vtkRenderWindow> rw = ui->qvtkWidget_Volume_6->GetRenderWindow();
	rw->AddRenderer(ren);
	rw->Render();

	vtkSmartPointer<vtkRenderWindowInteractor> rwi =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	rwi->SetRenderWindow(rw);

	vtkInteractorStyleTrackballCamera* st =       //设置交互方式
		vtkInteractorStyleTrackballCamera::New();
	rwi->SetInteractorStyle(st);
	/********************************************************************************/
	ren->ResetCamera();
	rw->Render();
}

void MainWindow::surfaceRender() {
	if (!flagSurfaceRender)
		return;

	//抽取等值面为骨头的信息  
	vtkSmartPointer< vtkMarchingCubes > boneExtractor =
		vtkSmartPointer< vtkMarchingCubes >::New();
	boneExtractor->SetInputConnection(threshould->GetOutputPort());
	//boneExtractor->SetValue(0, 500); //设置提取的等值信息
	boneExtractor->SetValue(0, 1024);
	boneExtractor->SetNumberOfContours(1);
	boneExtractor->Update();

	//剔除旧的或废除的数据单元，提高绘制速度(可略去这一步)  
	vtkSmartPointer< vtkStripper > boneStripper =
		vtkSmartPointer< vtkStripper >::New(); //三角带连接  
	boneStripper->SetInputConnection(boneExtractor->GetOutputPort());
	boneStripper->Update();

	//建立映射  
	vtkSmartPointer< vtkPolyDataMapper > boneMapper =
		vtkSmartPointer< vtkPolyDataMapper >::New();
	boneMapper->SetInputData(boneStripper->GetOutput());
	boneMapper->ScalarVisibilityOff();

	//建立角色  
	vtkSmartPointer< vtkActor > bone =
		vtkSmartPointer< vtkActor >::New();
	bone->SetMapper(boneMapper);
	bone->GetProperty()->SetDiffuseColor(.1, .94, .52);
	bone->GetProperty()->SetSpecular(.3);
	bone->GetProperty()->SetSpecularPower(20);
	bone->GetProperty()->SetOpacity(1.0);
	bone->GetProperty()->SetColor(1, 1, 1);
	bone->GetProperty()->SetRepresentationToSurface();
	//定义绘制器  
	vtkSmartPointer< vtkRenderer > aRenderer =
		vtkSmartPointer< vtkRenderer >::New();
	//定义绘制窗口  
	vtkSmartPointer< vtkRenderWindow > renWin = ui->qvtkWidget_Volume->GetRenderWindow();
	//vtkSmartPointer< vtkRenderWindow >::New();
	renWin->AddRenderer(aRenderer);
	renWin->Render();

	//定义窗口交互器  
	vtkSmartPointer< vtkRenderWindowInteractor > iren =
		vtkSmartPointer< vtkRenderWindowInteractor >::New();
	iren->SetRenderWindow(renWin);

	//创建一个camera  
	vtkSmartPointer< vtkCamera > aCamera =
		vtkSmartPointer< vtkCamera >::New();
	aCamera->SetViewUp(0, 0, -1);
	aCamera->SetPosition(0, 1, 0);
	aCamera->SetFocalPoint(0, 0, 0);

	aRenderer->AddActor(bone);
	aRenderer->SetActiveCamera(aCamera);
	aRenderer->ResetCamera();
	aCamera->Dolly(1.5);
	aRenderer->SetBackground(0, 0, 0);
	aRenderer->ResetCameraClippingRange();

	aRenderer->ResetCamera();
	renWin->Render();
	vtkInteractorStyleTrackballCamera* style =       //设置交互方式
		vtkInteractorStyleTrackballCamera::New();
	iren->SetInteractorStyle(style);
	iren->Initialize();
	iren->Start();
}

//#include "RegionGrowing.h"
void MainWindow::startRegionGrow() {
	//
	//int dims[3];
	//reader->GetOutput()->GetDimensions(dims);
	//int x[3];
	//x[0] = 152;
	//x[1] = 244;
	//x[2] = 165;
	//RegionGrowing mRegion;
	//Point3D p(x[0] , x[1] , x[2]);
	//mRegion.SetInputData(reader, dims[1], dims[2], dims[0]);
	//mRegion.SetSeedPoint(p);
	//short *pixel = (short *)reader->GetOutput()->GetScalarPointer(p.x, p.y, p.z);
	//mRegion.SetThreshold(200, 200);
	//mRegion.Setpixel(pixel[0]);
	//bool flag = mRegion.RegionGrow3D();
	//reader->Update();
	slice();
}

