#include "QtGuiApplication1.h"

using namespace cv;
using std::cout; using std::cerr; using std::endl; using std::vector;
using namespace std;
VideoCapture capture1(0);
VideoCapture capture2(1);
VideoCapture capture3(2);
VideoCapture capture4(3);
VideoCapture capture5(4);
VideoCapture capture6(5);
Mat frame1;
Mat frame2;
Mat frame3;
Mat frame4;
Mat frame5;
Mat frame6;
Mat blueFrame = imread("Bb_blue.jpg", IMREAD_COLOR);


bool pause = false;




QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QWidget(parent)
{
	int numCams = 0;
	for (int i = 0; i < 7; ++i) {
		VideoCapture capture0(i);
		if (capture0.isOpened()) {
			numCams++;
		}
	}
	// Create the button, make "this" the parent
	cam1Button = new QPushButton("Cam1", this);
	cam1Button->setGeometry(QRect(QPoint(50, 50),
		QSize(100, 50)));
	connect(cam1Button, SIGNAL(released()), this, SLOT(handleCam1Button()));

	cam2Button = new QPushButton("Cam2", this);
	cam2Button->setGeometry(QRect(QPoint(50, 100),
		QSize(100, 50)));
	connect(cam2Button, SIGNAL(released()), this, SLOT(handleCam2Button()));


	// Create the button, make "this" the parent
	cam3Button = new QPushButton("Cam3", this);
	cam3Button->setGeometry(QRect(QPoint(50, 150),
		QSize(100, 50)));
	connect(cam3Button, SIGNAL(released()), this, SLOT(handleCam3Button()));

	cam4Button = new QPushButton("Cam4", this);
	cam4Button->setGeometry(QRect(QPoint(150, 50),
		QSize(100, 50)));
	connect(cam4Button, SIGNAL(released()), this, SLOT(handleCam4Button()));


	// Create the button, make "this" the parent
	cam5Button = new QPushButton("Cam5", this);
	cam5Button->setGeometry(QRect(QPoint(150, 100),
		QSize(100, 50)));
	connect(cam5Button, SIGNAL(released()), this, SLOT(handleCam5Button()));

	cam6Button = new QPushButton("Cam6", this);
	cam6Button->setGeometry(QRect(QPoint(150, 150),
		QSize(100, 50)));
	connect(cam6Button, SIGNAL(released()), this, SLOT(handleCam6Button()));


	stitchedViewCam = new QPushButton("StitchedView", this);
	stitchedViewCam->setGeometry(QRect(QPoint(270, 100),
		QSize(100, 50)));
	connect(stitchedViewCam, SIGNAL(released()), this, SLOT(handleStitchedView()));

	// Connect button signal to appropriate slot
	startStream = new QPushButton("Start Stream", this);
	startStream->setGeometry(QRect(QPoint(420, 100),
		QSize(100, 50)));
	connect(startStream, SIGNAL(released()), this, SLOT(handleStartStream()));

	// Connect button signal to appropriate slot
	stopStream = new QPushButton("Stop Stream", this);
	stopStream->setGeometry(QRect(QPoint(540, 100),
		QSize(100, 50)));
	connect(stopStream, SIGNAL(released()), this, SLOT(handleStopStream()));

	// Connect button signal to appropriate slot
	zoomIn = new QPushButton("Zoom In", this);
	zoomIn->setGeometry(QRect(QPoint(690, 100),
		QSize(100, 50)));
	connect(zoomIn, SIGNAL(released()), this, SLOT(handleZoomIn()));

	// Connect button signal to appropriate slot
	zoomOut = new QPushButton("Zoom Out", this);
	zoomOut->setGeometry(QRect(QPoint(810, 100),
		QSize(100, 50)));
	connect(zoomOut, SIGNAL(released()), this, SLOT(handleZoomOut()));

	// Connect button signal to appropriate slot
	distanceGauge = new QPushButton("Distance Gauge", this);
	distanceGauge->setGeometry(QRect(QPoint(950, 50),
		QSize(100, 50)));
	connect(distanceGauge, SIGNAL(released()), this, SLOT(handleSoundToggle()));
	// Connect button signal to appropriate slot

	soundToggle = new QPushButton("Alert Sound", this);
	soundToggle->setGeometry(QRect(QPoint(950, 150),
		QSize(100, 50)));
	connect(soundToggle, SIGNAL(released()), this, SLOT(handleDistanceGauge()));

	// Connect button signal to appropriate slot
	exitButton = new QPushButton("Exit", this);
	exitButton->setGeometry(QRect(QPoint(1100, 50),
		QSize(200, 150)));
	connect(exitButton, SIGNAL(released()), this, SLOT(handleExitButton()));
}


void QtGuiApplication1::singleDisplay(VideoCapture capture, Mat frame) {
	pause = false;
	for (;;) {
		if (capture.isOpened()) { //avoid reading from an unopened device

			capture >> frame;
			imshow("Camera Feed", frame); //Display Frame
		}
		else {
			QMessageBox::information(this, "Warning",
				"No Cam Found");
			break; // If no camera, breaks from method
		}
		int keypress = waitKey(1); //saving the pressed key
		while (pause) {
			int keypress = waitKey(1); //saving the pressed key
		}
	}
}

void QtGuiApplication1::handleCam1Button()
{
	singleDisplay(capture1, frame1);
}
void QtGuiApplication1::handleCam2Button()
{
	singleDisplay(capture2, frame2);
}
void QtGuiApplication1::handleCam3Button()
{
	singleDisplay(capture3, frame3);
}
void QtGuiApplication1::handleCam4Button()
{
	singleDisplay(capture4, frame4);
}
void QtGuiApplication1::handleCam5Button()
{
	singleDisplay(capture5, frame5);
}
void QtGuiApplication1::handleCam6Button()
{
	singleDisplay(capture6, frame6);
}
void QtGuiApplication1::handleStopStream()
{
	if (pause == true) {
		QMessageBox::information(this, "Warning",
			"Stream already stopped");
	}
	pause = true;
}
void QtGuiApplication1::handleStartStream()
{
	if (pause == false) {
		QMessageBox::information(this, "Warning",
			"Stream already running");
	}
	pause = false;
}
void QtGuiApplication1::handleStitchedView()
{
	QMessageBox::information(this, "Warning",
		"Button in progress");
}
void QtGuiApplication1::handleZoomOut()
{
	QMessageBox::information(this, "Warning",
		"Button in progress");
}
void QtGuiApplication1::handleZoomIn()
{
	QMessageBox::information(this, "Warning",
		"Button in progress");
}
void QtGuiApplication1::handleDistanceGauge()
{
	QMessageBox::information(this, "Warning",
		"Button in progress");
}
void QtGuiApplication1::handleSoundToggle()
{
	QMessageBox::information(this, "Warning",
		"Button in progress");
}
void QtGuiApplication1::handleExitButton()
{
	capture1.release();
	capture2.release();
	capture3.release();
	capture4.release();
	capture5.release();
	capture6.release();
	exit(0);
}

