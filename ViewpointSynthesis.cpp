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
//Grid View Mats
Mat blueFrame;
Mat resize1;
Mat frame1;
Mat frame2;
Mat frame3;
Mat frame4;
Mat frame5;
Mat frame6;
Mat top;
Mat bot;
Mat3b gridFrame;
Mat Hom;
double frameRatio = 0.6;

std::vector<Mat> matArray1;
std::vector<Mat> matArray2;

Mat src;
Mat src2;

//Sizes for the frames
Rect blankROI(32, 24, 576, 432);
Rect myROI(32, 24, 576, 432);
Rect myROIs(18, 24, 687, 432);
Rect myROI2(64, 48, 512, 384);
Rect myROI3(128, 96, 384, 288);

// timer
auto start = std::chrono::system_clock::now();
bool runOnce = true;
int left1 = 0;
int right1 = 0;
int counter = 0;


//Y Spacer
int ySpace = 480;
//Used for detirmining zoom
double zoom = 1.0;
//Used to detirmine if the stream is stopped or not
bool isStopped = false;
int numCams = 0;
//Creates the buttons and space for the image display
ViewpointSynthesis::ViewpointSynthesis(QWidget* parent)
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
	myLabel->setGeometry(QRect(QPoint(100, 0),
		QSize(720, 480)));
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
	stitchedViewCam = new QPushButton("Stitched View", this);
	stitchedViewCam->setGeometry(QRect(QPoint(270, 50 + ySpace),
		QSize(100, 50)));
	connect(stitchedViewCam, SIGNAL(released()), this, SLOT(handleStitchedView()));

	//Creates a button for the grid view function
	gridView = new QPushButton("Grid View", this);
	gridView->setGeometry(QRect(QPoint(270, 150 + ySpace),
		QSize(100, 50)));
	connect(gridView, SIGNAL(released()), this, SLOT(handleGridView()));

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
	if (numCams < 2) {
		stitchedViewCam->setEnabled(false);
	}
}


//Single display is the function that is called when one of the single view buttons is pressed
//It accepts a video capture as an argument
//The video capture takes frames from a given camera and sets them in a variable "capturedFrame"
//The frame is resized to fit the gui and then calls convert image to return a pixmap
//The pixmap is then inserted into the label and displayed on the screen
void ViewpointSynthesis::singleDisplay(VideoCapture capture) {
	zoomIn->setEnabled(true);
	zoomOut->setEnabled(true);
	zoom = 1.0;
	isStopped = false;
	capture >> capturedFrame;
	resizedFrame = capturedFrame(myROI);
	myLabel->setGeometry(QRect(QPoint(250, 0),
		QSize(720, 480)));
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

void ViewpointSynthesis::gridDisplay() {
	zoomIn->setEnabled(false);
	zoomOut->setEnabled(false);
	zoom = 1.0;
	isStopped = false;
	blueFrame = imread("Bb_blue.jpg", IMREAD_COLOR);
	for (;;) {
		if (numCams != 0) { //avoid reading from an unopened device
			myLabel->setGeometry(QRect(QPoint(250, 0),
				QSize(720, 480)));
			resizedFrame = setGrid();
			myLabel->setPixmap(convertImage(resizedFrame));
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
	cv::resize(resizedFrame, resize2, Size(720, 480));
	//converts the mat to RGB for qt
	cvtColor(resize2, resize2, COLOR_RGB2BGR);
	//Create a new image using the capturedFrame frame data
	QImage img((uchar*)resize2.data, 720, 480, QImage::Format_RGB888);
	//Sets a pixel map to the image
	QPixmap pixmap = QPixmap::fromImage(img);
	return pixmap;
}

//Set grid sets all of the accessable camera feeds in a displayable grid Mat image
Mat ViewpointSynthesis::setGrid() {
	switch (numCams) {
	case 0: {
		QMessageBox::information(this, "Warning",
			"No Cam Found");
		return blueFrame;
		break;
	}
	case 1: {
		capture1 >> frame1;
		cv::resize(frame1, frame1, Size(240, 240));
		cv::resize(blueFrame, blueFrame, Size(240, 240));
		frame2 = blueFrame;
		frame3 = blueFrame;
		frame4 = blueFrame;
		frame5 = blueFrame;
		frame6 = blueFrame;
		matArray1 = { frame1, frame2, frame3 };
		matArray2 = { frame4, frame5, frame6 };
		hconcat(matArray1, top);
		hconcat(matArray2, bot);
		vconcat(top, bot, gridFrame);
		break;
	}
	case 2: {
		capture1 >> frame1;
		capture2 >> frame2;
		cv::resize(frame1, frame1, Size(), frameRatio, frameRatio);
		cv::resize(blueFrame, blueFrame, Size(frame1.cols, frame1.rows), 0, 0);
		cv::resize(frame2, frame2, Size(frame1.cols, frame1.rows), 0, 0);
		frame3 = blueFrame;
		frame4 = blueFrame;
		frame5 = blueFrame;
		frame6 = blueFrame;
		matArray1 = { frame1, frame2, frame3 };
		matArray2 = { frame4, frame5, frame6 };
		hconcat(matArray1, top);
		hconcat(matArray2, bot);
		vconcat(top, bot, gridFrame);
		break;
	}
	case 3: {
		capture1 >> frame1;
		capture2 >> frame2;
		capture3 >> frame3;
		cv::resize(frame1, frame1, Size(), frameRatio, frameRatio);
		cv::resize(blueFrame, blueFrame, Size(frame1.cols, frame1.rows), 0, 0);
		cv::resize(frame2, frame2, Size(frame1.cols, frame1.rows), 0, 0);
		cv::resize(frame3, frame3, Size(frame1.cols, frame1.rows), 0, 0);
		frame4 = blueFrame;
		frame5 = blueFrame;
		frame6 = blueFrame;
		matArray1 = { frame1, frame2, frame3 };
		matArray2 = { frame4, frame5, frame6 };
		hconcat(matArray1, top);
		hconcat(matArray2, bot);
		vconcat(top, bot, gridFrame);
		break;
	}
	case 4: {
		capture1 >> frame1;
		capture2 >> frame2;
		capture3 >> frame3;
		capture4 >> frame4;
		cv::resize(frame1, frame1, Size(), frameRatio, frameRatio);
		cv::resize(blueFrame, blueFrame, Size(frame1.cols, frame1.rows), 0, 0);
		cv::resize(frame2, frame2, Size(frame1.cols, frame1.rows), 0, 0);
		cv::resize(frame3, frame3, Size(frame1.cols, frame1.rows), 0, 0);
		cv::resize(frame4, frame4, Size(frame1.cols, frame1.rows), 0, 0);
		frame5 = blueFrame;
		frame6 = blueFrame;
		matArray1 = { frame1, frame2, frame3 };
		matArray2 = { frame4, frame5, frame6 };
		hconcat(matArray1, top);
		hconcat(matArray2, bot);
		vconcat(top, bot, gridFrame);

		break;
	}
	case 5: {
		capture1 >> frame1;
		capture2 >> frame2;
		capture3 >> frame3;
		capture4 >> frame4;
		capture5 >> frame5;
		cv::resize(frame1, frame1, Size(), frameRatio, frameRatio);
		cv::resize(blueFrame, blueFrame, Size(frame1.cols, frame1.rows), 0, 0);
		cv::resize(frame2, frame2, Size(frame1.cols, frame1.rows), 0, 0);
		cv::resize(frame3, frame3, Size(frame1.cols, frame1.rows), 0, 0);
		cv::resize(frame4, frame4, Size(frame1.cols, frame1.rows), 0, 0);
		cv::resize(frame5, frame5, Size(frame1.cols, frame1.rows), 0, 0);
		frame6 = blueFrame;
		matArray1 = { frame1, frame2, frame3 };
		matArray2 = { frame4, frame5, frame6 };
		hconcat(matArray1, top);
		hconcat(matArray2, bot);
		vconcat(top, bot, gridFrame);

		break;
	}
	case 6: {
		capture1 >> frame1;
		capture2 >> frame2;
		capture3 >> frame3;
		capture4 >> frame4;
		capture5 >> frame5;
		capture6 >> frame6;
		cv::resize(frame1, frame1, Size(), frameRatio, frameRatio);
		cv::resize(frame2, frame2, Size(frame1.cols, frame1.rows), 0, 0);
		cv::resize(frame3, frame3, Size(frame1.cols, frame1.rows), 0, 0);
		cv::resize(frame4, frame4, Size(frame1.cols, frame1.rows), 0, 0);
		cv::resize(frame5, frame5, Size(frame1.cols, frame1.rows), 0, 0);
		cv::resize(frame6, frame6, Size(frame1.cols, frame1.rows), 0, 0);
		matArray1 = { frame1, frame2, frame3 };
		matArray2 = { frame4, frame5, frame6 };
		hconcat(matArray1, top);
		hconcat(matArray2, bot);
		vconcat(top, bot, gridFrame);
		break;
	}
	}
	return gridFrame;
}

Mat ViewpointSynthesis::stitchImages(int& left, int& right) {
	blueFrame = imread("Bb_blue.jpg", IMREAD_COLOR);
	if (numCams >= 2) {
		const double nn_match_ratio = 0.75f; // Nearest-neighbour matching ratio
		capture2 >> src;
		capture1 >> src2;


		//-- Step 1: Detect the keypoints using SURF Detector
		int minHessian = 800;
		Mat desc1, desc2;
		Ptr<ORB> detector = ORB::create();
		detector->setMaxFeatures(minHessian);
		Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE_HAMMING);
		std::vector<KeyPoint> keypoints1, keypoints2;

		detector->detectAndCompute(src, noArray(), keypoints1, desc1);
		detector->detectAndCompute(src2, noArray(), keypoints2, desc2);

		std::vector< std::vector<DMatch> > knn_matches;
		bool catcher;
		matcher->knnMatch(desc1, desc2, knn_matches, 2);
		//-- Filter matches using the Lowe's ratio test
		std::vector<DMatch> good_matches;
		for (size_t i = 0; i < knn_matches.size(); i++)
		{
			if (knn_matches[i][0].distance < nn_match_ratio * knn_matches[i][1].distance)
			{
				good_matches.push_back(knn_matches[i][0]);
			}
		}

			//std::vector< std::vector<DMatch> > good_matches;
		std::vector<Point2f> obj;
		std::vector<Point2f> scene;
		for (size_t i = 0; i < good_matches.size(); i++)
		{
			//-- Get the keypoints from the good matches
			obj.push_back(keypoints1[good_matches[i].queryIdx].pt);
			scene.push_back(keypoints2[good_matches[i].trainIdx].pt);
		}
		
		auto endtime = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_secs = endtime - start;
		if (elapsed_secs.count() >= 2 || runOnce == true) {
			Hom = findHomography(obj, scene, RANSAC);

			runOnce = false;
			start = std::chrono::system_clock::now();
		}
		//std::cout << left << " " << right << std::endl;

		int h = 480;
		Mat3b merge(720*2, h);
		cv::warpPerspective(src, merge, Hom, Size(src.cols + src2.cols, 480));

		src2.copyTo(merge(Rect(0, 0, src2.cols, 480)));
		cv::resize(merge, merge, Size(720, 480), 0, 0);
			
			
		//drawMatches(src, matched1, src2, matched2, knn_matches, img_matches, Scalar(255,0,0),
		//	Scalar(255, 0, 0));
		//-- Show detected matches
		return merge;
		
	}else {
		QMessageBox::information(this, "Warning",
			"Not enough cameras");
		return blueFrame;
	}
}

void ViewpointSynthesis::stitchedDisplay() {
	zoomIn->setEnabled(true);
	zoomOut->setEnabled(true);
	zoom = 1.0;
	isStopped = false;
	capturedFrame = stitchImages(left1, right1);
	blankROI = myROIs;
	resizedFrame = capturedFrame(myROIs);
	if (zoom == 2) {
		blankROI = myROI2;
	}
	if (numCams < 2) {
		QMessageBox::information(this, "Warning",
			"Not enough cameras");
	}
	else {
		for (;;) {
			capturedFrame = stitchImages(left1, right1);
			resizedFrame = capturedFrame(blankROI);
			myLabel->setGeometry(QRect(QPoint(250, 0),
				QSize(720, 480)));
			myLabel->setPixmap(convertImage(resizedFrame));
			int keypress = waitKey(1); //Prevent infinite loop
			while (isStopped) {
				int keypress = waitKey(1); //Prevent infinite loop
			}
		}
	}
}
//Handlers for buttons cam1-cam6
void ViewpointSynthesis::handleGridView()
{
	gridDisplay();
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
