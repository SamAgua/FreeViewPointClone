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

Mat src = imread("iqbal1.png", IMREAD_COLOR);
Mat src2 = imread("iqbal2.png", IMREAD_COLOR);

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
int numCams = 0;
//Creates the buttons and space for the image display
ViewpointSynthesis::ViewpointSynthesis(QWidget *parent)
	: QWidget(parent)
{
	//Counts the number of active cameras
	
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

Mat ViewpointSynthesis::stitchImages() {
	const double nn_match_ratio = 0.8f; // Nearest-neighbour matching ratio
	capture1 >> src;
	capture3 >> src2;

	//-- Step 1: Detect the keypoints using SURF Detector
	int minHessian = 500;
	Mat desc1, desc2;
	Ptr<ORB> detector = ORB::create();
	detector->setMaxFeatures(minHessian);
	Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
	std::vector<KeyPoint> keypoints1, keypoints2;

	detector->detectAndCompute(src, noArray(), keypoints1, desc1);
	detector->detectAndCompute(src2, noArray(), keypoints2, desc2);

	std::vector< std::vector<DMatch> > knn_matches;
	matcher->knnMatch(desc1, desc2, knn_matches, 2);
	//-- Filter matches using the Lowe's ratio test

	//std::vector< std::vector<DMatch> > good_matches;
	std::vector<KeyPoint> matched1, matched2;
	for (unsigned i = 0; i < knn_matches.size(); i++) {
		if (knn_matches[i][0].distance < nn_match_ratio * knn_matches[i][1].distance) {
			matched1.push_back(keypoints1[knn_matches[i][0].queryIdx]);
			matched2.push_back(keypoints2[knn_matches[i][0].trainIdx]);
		}
	}
	int max1 = 0;
	int max2 = 0;
	std::vector<KeyPoint>::const_iterator it = matched1.begin(), end = matched1.end();
	for (; it != end; ++it) {
		if (it->pt.x > max1) {
			max1 = it->pt.x;
		}
	}
	std::vector<KeyPoint>::const_iterator it2 = matched2.begin(), end2 = matched2.end();
	for (; it2 != end2; ++it2) {
		if (it2->pt.x > max2) {
			max2 = it2->pt.x;
		}
	}
	int left = max1 / matched1.size();
	int right = max2 / matched1.size();
		std::cout << max1 << " " << max2 << std::endl;

		int h = 600;
	Mat test = cv::Mat::zeros(cv::Size(340 * 2, h), CV_8UC3);
	Mat small1 = cv::Mat(src, cv::Rect(0, 0, max1, src.rows));
	cv::resize(small1, small1, cv::Size(340, h), 0, 0);
	//cv::Rect myROI(max2, 0, src2.cols, src2.rows);

	Mat small2 = src2(Rect(max2, 0, src2.cols - max2, src2.rows));
	cv::resize(small2, small2, cv::Size(340, h), 0, 0);

	small1.copyTo(test(Rect(0, 0, small1.cols, h)));
	small2.copyTo(test(Rect(small1.cols, 0, small2.cols, small2.rows)));
	//drawMatches(src, matched1, src2, matched2, knn_matches, img_matches, Scalar(255,0,0),
	//	Scalar(255, 0, 0));
	//-- Show detected matches
	return test;
}
void ViewpointSynthesis::stitchedDisplay() {
	zoom = 1.0;
	isStopped = false;
	capturedFrame = stitchImages();
	resizedFrame = capturedFrame(myROI);
	if (numCams < 2) {
		QMessageBox::information(this, "Warning",
			"Not enough cameras");
	}
	else {
		for (;;) {
			capturedFrame = stitchImages();
			resizedFrame = capturedFrame(myROI);
			myLabel->setGeometry(QRect(QPoint(275, 0),
				QSize(resizedFrame.cols, resizedFrame.rows)));
			myLabel->setPixmap(convertImage(capturedFrame));
			int keypress = waitKey(1); //Prevent infinite loop
			while (isStopped) {
				int keypress = waitKey(1); //Prevent infinite loop
			}
		}
	}
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
	stitchedDisplay();
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