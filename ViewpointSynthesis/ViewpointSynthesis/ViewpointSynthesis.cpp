#include "ViewpointSynthesis.h"
//Video captures for up to 6 cameras
VideoCapture capture1(0);
VideoCapture capture2(1);
VideoCapture capture3(2);
VideoCapture capture4(3);
VideoCapture capture5(4);
VideoCapture capture6(5);
//Frames for capturing and size manipulation
Mat capturedFrame;
Mat resizedFrame;
Mat resize2;
//Sizes for the frames
Rect myROI(32, 24, 576, 432);
Rect myROI2(64, 48, 512, 384);
Rect myROI3(128, 96, 384, 288);
//Y Spacer
int ySpace = 480;
//Used for detirmining zoom
double zoom = 1.0;
//Used to detirmine if the stream is stopped or not
bool isStopped = false;

//Creates the buttons and space for the image display
ViewpointSynthesis::ViewpointSynthesis(QWidget *parent)
	: QWidget(parent)
{
	//Counts the number of active cameras
	int numCams = 0;
	for (int i = 0; i < 7; ++i) {
		VideoCapture capture0(i);
		if (capture0.isOpened()) {
			numCams++;
		}
	}
	//Creates a label that will be used to display the captured images
	myLabel = new QLabel("", this);
	myLabel->setGeometry(QRect(QPoint(275, 0),
		QSize(500, 500)));
	//Creates a button for each active camera
	if (numCams >= 1) {
		cam1Button = new QPushButton("Cam1", this);
		cam1Button->setGeometry(QRect(QPoint(50, 50 + ySpace),
			QSize(100, 50)));
		connect(cam1Button, SIGNAL(released()), this, SLOT(handleCam1Button()));
	}
	if (numCams >= 2) {
		cam2Button = new QPushButton("Cam2", this);
		cam2Button->setGeometry(QRect(QPoint(50, 100 + ySpace),
			QSize(100, 50)));
		connect(cam2Button, SIGNAL(released()), this, SLOT(handleCam2Button()));
	}
	if (numCams >= 3) {
		cam3Button = new QPushButton("Cam3", this);
		cam3Button->setGeometry(QRect(QPoint(50, 150 + ySpace),
			QSize(100, 50)));
		connect(cam3Button, SIGNAL(released()), this, SLOT(handleCam3Button()));
	}
	if (numCams >= 4) {
		cam4Button = new QPushButton("Cam4", this);
		cam4Button->setGeometry(QRect(QPoint(150, 50 + ySpace),
			QSize(100, 50)));
		connect(cam4Button, SIGNAL(released()), this, SLOT(handleCam4Button()));
	}
	if (numCams >= 5) {
		cam5Button = new QPushButton("Cam5", this);
		cam5Button->setGeometry(QRect(QPoint(150, 100 + ySpace),
			QSize(100, 50)));
		connect(cam5Button, SIGNAL(released()), this, SLOT(handleCam5Button()));
	}
	if (numCams >= 6) {
		cam6Button = new QPushButton("Cam6", this);
		cam6Button->setGeometry(QRect(QPoint(150, 150 + ySpace),
			QSize(100, 50)));
		connect(cam6Button, SIGNAL(released()), this, SLOT(handleCam6Button()));
	}
	
	//Creates a button for the stitched view function
	stitchedViewCam = new QPushButton("StitchedView", this);
	stitchedViewCam->setGeometry(QRect(QPoint(270, 100 + ySpace),
		QSize(100, 50)));
	connect(stitchedViewCam, SIGNAL(released()), this, SLOT(handleStitchedView()));

	//Creates a button for the start stream function
	startStream = new QPushButton("Start Stream", this);
	startStream->setGeometry(QRect(QPoint(420, 100 + ySpace),
		QSize(100, 50)));
	connect(startStream, SIGNAL(released()), this, SLOT(handleStartStream()));

	//Creates a button for the stop stream function
	stopStream = new QPushButton("Stop Stream", this);
	stopStream->setGeometry(QRect(QPoint(540, 100 + ySpace),
		QSize(100, 50)));
	connect(stopStream, SIGNAL(released()), this, SLOT(handleStopStream()));

	//Creates a button for the zoom in function
	zoomIn = new QPushButton("Zoom In", this);
	zoomIn->setGeometry(QRect(QPoint(690, 100 + ySpace),
		QSize(100, 50)));
	connect(zoomIn, SIGNAL(released()), this, SLOT(handleZoomIn()));

	//Creates a button for the zoom in function
	zoomOut = new QPushButton("Zoom Out", this);
	zoomOut->setGeometry(QRect(QPoint(810, 100 + ySpace),
		QSize(100, 50)));
	connect(zoomOut, SIGNAL(released()), this, SLOT(handleZoomOut()));

	//Creates a button for the exit function
	exitButton = new QPushButton("Exit", this);
	exitButton->setGeometry(QRect(QPoint(950, 50 + ySpace),
		QSize(200, 150)));
	connect(exitButton, SIGNAL(released()), this, SLOT(handleExitButton()));
}


//Single display is the function that is called when one of the single view buttons is pressed
//It accepts a video capture as an argument
//The video capture takes frames from a given camera and sets them in a variable "capturedFrame"
//The frame is resized to fit the gui and then calls convert image to return a pixmap
//The pixmap is then inserted into the label and displayed on the screen
void ViewpointSynthesis::singleDisplay(VideoCapture capture) {
	zoom = 1.0;
	isStopped = false;
	capture >> capturedFrame;
	resizedFrame = capturedFrame(myROI);
	myLabel->setGeometry(QRect(QPoint(275, 0),
		QSize(resizedFrame.cols, resizedFrame.rows)));
	for (;;) {
		if (capture.isOpened()) { //avoid reading from an unopened device
			capture >> capturedFrame;
			myLabel->setPixmap(convertImage(capturedFrame));
		}
		else {
			QMessageBox::information(this, "Warning",
				"No Cam Found");
			break; // If no camera, breaks from method
		}
		int keypress = waitKey(1); //Prevent infinite loop
		while (isStopped) {
			int keypress = waitKey(1); //Prevent infinite loop
		}
	}

}

//convertImage converts an OpenCV Mat image to a QT pixmap image and returns the pixmap
//This functions takes an OpenCV mat as an argument
QPixmap ViewpointSynthesis::convertImage(Mat capturedFrame) {
	//Resizes the frame according to the amount of zoom that is currently being applied
	cv::resize(resizedFrame, resize2, Size(capturedFrame.cols, capturedFrame.rows));
	//converts the mat to RGB for qt
	cvtColor(resize2, resize2, COLOR_RGB2BGR);
	//Create a new image using the capturedFrame frame data
	QImage img((uchar*)resize2.data, resize2.cols, resize2.rows, QImage::Format_RGB888);
	//Sets a pixel map to the image
	QPixmap pixmap = QPixmap::fromImage(img);
	return pixmap;
}

//Handlers for buttons cam1-cam6
void ViewpointSynthesis::handleCam1Button()
{
	singleDisplay(capture1);
}
void ViewpointSynthesis::handleCam2Button()
{
	singleDisplay(capture2);
}
void ViewpointSynthesis::handleCam3Button()
{
	singleDisplay(capture3);
}
void ViewpointSynthesis::handleCam4Button()
{
	singleDisplay(capture4);
}
void ViewpointSynthesis::handleCam5Button()
{
	singleDisplay(capture5);
}
void ViewpointSynthesis::handleCam6Button()
{
	singleDisplay(capture6);
}

//Stops the stream by setting isStopped to true
//If already stopped displays an error message
void ViewpointSynthesis::handleStopStream()
{
	if (isStopped == true) {
		QMessageBox::information(this, "Warning",
			"Stream already stopped");
	}
	isStopped = true;
}
//Starts the stream by setting isStopped to false
//If currently running displays an error message
void ViewpointSynthesis::handleStartStream()
{
	if (isStopped == false) {
		QMessageBox::information(this, "Warning",
			"Stream already running");
	}
	isStopped = false;
}
void ViewpointSynthesis::handleStitchedView()
{
	QMessageBox::information(this, "Warning",
		"Button in progress");
}
//Handles the zoom out button and sets the proper zoom value
//If zoomed out too much, an error message will appear
void ViewpointSynthesis::handleZoomOut()
{
	if (zoom == 1) {
		QMessageBox::information(this, "Warning",
			"Cannot zoom out any further");
	}
	else {
		if (zoom == 3) {
			resizedFrame = capturedFrame(myROI2);
			myLabel->setPixmap(convertImage(capturedFrame));
			zoom = 2;
		}
		else {
			resizedFrame = capturedFrame(myROI);
			myLabel->setPixmap(convertImage(capturedFrame));
			zoom = 1;
		}

	}
}

//Handles the zoom in button and sets the proper zoom value
//If zoomed out too much, an error message will appear
void ViewpointSynthesis::handleZoomIn()
{
	if (zoom == 3) {
		QMessageBox::information(this, "Warning",
			"Cannot zoom in any further");
	}
	else {
		if (zoom == 1.0) {
			resizedFrame = capturedFrame(myROI2);
			myLabel->setPixmap(convertImage(capturedFrame));
			zoom = 2;
		}
		else {
			resizedFrame = capturedFrame(myROI3);
			myLabel->setPixmap(convertImage(capturedFrame));
			zoom = 3;
		}

	}
}

//This handles the exit button and releases the camera data and exits the program
void ViewpointSynthesis::handleExitButton()
{
	capture1.release();
	capture2.release();
	capture3.release();
	capture4.release();
	capture5.release();
	capture6.release();
	exit(0);
}