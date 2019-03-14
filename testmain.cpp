#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/stitching.hpp>
#include <opencv2/imgproc.hpp>  // cv::Canny()
#include <iostream>
#include <vector>

using namespace cv;
using std::cout; using std::cerr; using std::endl; using std::vector;
using namespace std;
//Assigns cameras to variables

VideoCapture capture1(0);
VideoCapture capture2(1);
VideoCapture capture3(2);
VideoCapture capture4(3);
VideoCapture capture5(4);
VideoCapture capture6(5);
Mat blueFrame;
Mat frame1;
Mat frame2;
Mat frame3;
Mat frame4;
Mat frame5;
Mat frame6;
Mat top;
Mat bot;
std::vector<Mat> matArray1;
std::vector<Mat> matArray2;
std::vector<Mat> matArray3;
std::vector<Mat> stitchedArray;
Mat finalFrame;
//Creates the frame to hold the feed
double frameRatio = 0.6;

Mat stitchFrames(std::vector<Mat> arr);

int camCount() {
	int numCams = 0;
	double frameRatio = 0.6;
	cout << "checking for cams" << endl;

	for (int i = 0; i < 7; ++i) {
		VideoCapture capture0(i);
		if (capture0.isOpened()) {
			numCams++;
		}
	}
	return numCams;
}

void displayCams(int numCams) {
	blueFrame = imread("Bb_blue.jpg", IMREAD_COLOR);
	for (;;)
	{
		//Mat3b finalFrame;
		switch (numCams) {
		case 0: cout << "no cams detected" << endl;
			exit(0);
			break;
		case 1: {
			capture1 >> frame1;
			resize(frame1, frame1, Size(), frameRatio, frameRatio);
			resize(blueFrame, blueFrame, Size(frame1.cols, frame1.rows), 0, 0);
			frame2 = blueFrame;
			frame3 = blueFrame;
			frame4 = blueFrame;
			frame5 = blueFrame;
			frame6 = blueFrame;
			matArray1 = { frame1, frame2, frame3 };
			matArray2 = { frame4, frame5, frame6 };
			hconcat(matArray1, top);
			hconcat(matArray2, bot);
			vconcat(top, bot, finalFrame);
			//namedWindow("cam1", WINDOW_AUTOSIZE);
			imshow("Camera Feed", finalFrame);
			break;
		}
		case 2: {
			capture1 >> frame1;
			capture2 >> frame2;
			resize(frame1, frame1, Size(), frameRatio, frameRatio);
			resize(blueFrame, blueFrame, Size(frame1.cols, frame1.rows), 0, 0);
			resize(frame2, frame2, Size(frame1.cols, frame1.rows), 0, 0);
			frame3 = blueFrame;
			frame4 = blueFrame;
			frame5 = blueFrame;
			frame6 = blueFrame;
			matArray1 = { frame1, frame2, frame3 };
			matArray2 = { frame4, frame5, frame6 };
			hconcat(matArray1, top);
			hconcat(matArray2, bot);
			vconcat(top, bot, finalFrame);
			//namedWindow("cam1", WINDOW_AUTOSIZE);
			imshow("Camera Feed", finalFrame);
			break;
		}
		case 3: {
			capture1 >> frame1;
			capture2 >> frame2;
			capture3 >> frame3;
			resize(frame1, frame1, Size(), frameRatio, frameRatio);
			resize(blueFrame, blueFrame, Size(frame1.cols, frame1.rows), 0, 0);
			resize(frame2, frame2, Size(frame1.cols, frame1.rows), 0, 0);
			resize(frame3, frame3, Size(frame1.cols, frame1.rows), 0, 0);
			frame4 = blueFrame;
			frame5 = blueFrame;
			frame6 = blueFrame;
			matArray1 = { frame1, frame2, frame3 };
			matArray2 = { frame4, frame5, frame6 };
			hconcat(matArray1, top);
			hconcat(matArray2, bot);
			vconcat(top, bot, finalFrame);
			//namedWindow("cam1", WINDOW_AUTOSIZE);
			imshow("Camera Feed", finalFrame);
			break;
		}
		case 4: {
			capture1 >> frame1;
			capture2 >> frame2;
			capture3 >> frame3;
			capture4 >> frame4;
			resize(frame1, frame1, Size(), frameRatio, frameRatio);
			resize(blueFrame, blueFrame, Size(frame1.cols, frame1.rows), 0, 0);
			resize(frame2, frame2, Size(frame1.cols, frame1.rows), 0, 0);
			resize(frame3, frame3, Size(frame1.cols, frame1.rows), 0, 0);
			resize(frame4, frame4, Size(frame1.cols, frame1.rows), 0, 0);
			frame5 = blueFrame;
			frame6 = blueFrame;
			matArray1 = { frame1, frame2, frame3 };
			matArray2 = { frame4, frame5, frame6 };
			hconcat(matArray1, top);
			hconcat(matArray2, bot);
			vconcat(top, bot, finalFrame);
			//namedWindow("cam1", WINDOW_AUTOSIZE);
			imshow("Camera Feed", finalFrame);
			break;
		}
		case 5: {
			capture1 >> frame1;
			capture2 >> frame2;
			capture3 >> frame3;
			capture4 >> frame4;
			capture5 >> frame5;
			resize(frame1, frame1, Size(), frameRatio, frameRatio);
			resize(blueFrame, blueFrame, Size(frame1.cols, frame1.rows), 0, 0);
			resize(frame2, frame2, Size(frame1.cols, frame1.rows), 0, 0);
			resize(frame3, frame3, Size(frame1.cols, frame1.rows), 0, 0);
			resize(frame4, frame4, Size(frame1.cols, frame1.rows), 0, 0);
			resize(frame5, frame5, Size(frame1.cols, frame1.rows), 0, 0);
			frame6 = blueFrame;
			matArray1 = { frame1, frame2, frame3 };
			matArray2 = { frame4, frame5, frame6 };
			hconcat(matArray1, top);
			hconcat(matArray2, bot);
			vconcat(top, bot, finalFrame);
			//namedWindow("cam1", WINDOW_AUTOSIZE);
			imshow("Camera Feed", finalFrame);
			break;
		}
		case 6: {
			capture1 >> frame1;
			capture2 >> frame2;
			capture3 >> frame3;
			capture4 >> frame4;
			capture5 >> frame5;
			capture6 >> frame6;
			resize(frame1, frame1, Size(), frameRatio, frameRatio);
			resize(frame2, frame2, Size(frame1.cols, frame1.rows), 0, 0);
			resize(frame3, frame3, Size(frame1.cols, frame1.rows), 0, 0);
			resize(frame4, frame4, Size(frame1.cols, frame1.rows), 0, 0);
			resize(frame5, frame5, Size(frame1.cols, frame1.rows), 0, 0);
			resize(frame6, frame6, Size(frame1.cols, frame1.rows), 0, 0);
			matArray1 = { frame1, frame2, frame3 };
			matArray2 = { frame4, frame5, frame6 };
			hconcat(matArray1, top);
			hconcat(matArray2, bot);
			vconcat(top, bot, finalFrame);
			//namedWindow("cam1", WINDOW_AUTOSIZE);
			imshow("Camera Feed", finalFrame);
			break;
		}
		}
		char key = waitKey(1);
		if (char(key) == 27) 
			break;
	}

}
//cam0 - cam5 methods for displaying individual camera feeds. This can be used later for camera selection GUI

void cam1() {
	while (true) {
		if (capture1.isOpened()) { //avoid reading from an unopened device
			capture1.read(frame1); //Reads frame
			imshow("Camera Feed", frame1); //Display Frame
		}
		else {
			break; // If no camera, breaks from method
		}
		int keypress = waitKey(1); //saving the pressed key
		if (keypress == 27) {//if pressed Esc key breaks from method
			break;
		}
	}
}
void cam2() {
	while (true) {
		if (capture2.isOpened()) { //avoid reading from an unopened device
			capture2.read(frame2); //Reads frame
			imshow("Camera Feed", frame2); //Display Frame
		}
		else {
			break; // If no camera, breaks from method
		}
		int keypress = waitKey(1); //saving the pressed key
		if (keypress == 27) {//if pressed Esc key breaks from method
			break;
		}
	}
}
void cam3() {
	while (true) {
		if (capture3.isOpened()) { //avoid reading from an unopened device
			capture3.read(frame3); //Reads frame
			imshow("Camera Feed", frame3); //Display Frame
		}
		else {
			break; // If no camera, breaks from method
		}
		int keypress = waitKey(1); //saving the pressed key
		if (keypress == 27) {//if pressed Esc key breaks from method
			break;
		}
	}
}
void cam4() {
	while (true) {
		if (capture4.isOpened()) { //avoid reading from an unopened device
			capture4.read(frame4); //Reads frame
			imshow("Camera Feed", frame4); //Display Frame
		}
		else {
			break; // If no camera, breaks from method
		}
		int keypress = waitKey(1); //saving the pressed key
		if (keypress == 27) {//if pressed Esc key breaks from method
			break;
		}
	}
}
void cam5() {
	while (true) {
		if (capture5.isOpened()) { //avoid reading from an unopened device
			capture5.read(frame5); //Reads frame
			imshow("Camera Feed", frame5); //Display Frame
		}
		else {
			break; // If no camera, breaks from method
		}
		int keypress = waitKey(1); //saving the pressed key
		if (keypress == 27) {//if pressed Esc key breaks from method
			break;
		}
	}

}
void cam6() {
	while (true) {
		if (capture6.isOpened()) { //avoid reading from an unopened device
			capture6.read(frame6); //Reads frame
			imshow("Camera Feed", frame6); //Display Frame
		}
		else {
			break; // If no camera, breaks from method
		}
		int keypress = waitKey(1); //saving the pressed key
		if (keypress == 27) {//if pressed Esc key breaks from method
			break;
		}
	}
}

void stitchedView(int numCams) {
	Mat finalFrame;

	for (;;)
	{
		switch (numCams) {
		case 0: cout << "no cams detected" << endl;
			exit(0);
			break;
		case 1: {
			capture1 >> frame1;
			imshow("Camera Feed", frame1);
			break;
		}
		case 2: {
			capture1 >> frame1;
			capture2 >> frame2;
			stitchedArray = { frame1, frame2};
			finalFrame = stitchFrames(stitchedArray);
			imshow("Camera Feed", finalFrame);
			break;
		}
		case 3: {
			capture1 >> frame1;
			capture2 >> frame2;
			capture3 >> frame3;
			stitchedArray = { frame1, frame2, frame3 };
			finalFrame = stitchFrames(stitchedArray);
			imshow("Camera Feed", finalFrame);
			break;
		}
		case 4: {
			capture1 >> frame1;
			capture2 >> frame2;
			capture3 >> frame3;
			capture4 >> frame4;
			matArray1 = { frame1, frame2 };
			matArray2 = { frame3, frame4 };
			finalFrame = stitchFrames(stitchedArray);
			imshow("Camera Feed", finalFrame);
			break;
		}
		case 5: {
			capture1 >> frame1;
			capture2 >> frame2;
			capture3 >> frame3;
			capture4 >> frame4;
			capture5 >> frame5;
			matArray1 = { frame1, frame2 };
			matArray2 = { frame3, frame4, frame5 };
			finalFrame = stitchFrames(stitchedArray);
			imshow("Camera Feed", finalFrame);
			break;
		}
		case 6: {
			capture1 >> frame1;
			capture2 >> frame2;
			capture3 >> frame3;
			capture4 >> frame4;
			capture5 >> frame5;
			capture6 >> frame6;
			matArray1 = { frame1, frame2 };
			matArray2 = { frame3, frame4 };
			matArray3 = { frame5, frame6 };
			finalFrame = stitchFrames(stitchedArray);
			imshow("Camera Feed", finalFrame);
			break;
		}
		}
		char key = waitKey(1);
		if (char(key) == 27)
			break;
	}

}


Mat stitchFrames(std::vector<Mat> matArr) {
	Mat sFrame;
	Ptr<Stitcher> stitcher = Stitcher::create();
	Stitcher::Status status = stitcher->stitch(matArr, sFrame);
	if (sFrame.empty()) {
		cout << "Unable to pull from display " << endl;
	}
	if (status != Stitcher::OK) {
		cout << int(status) << endl;
	}

	return sFrame;
}

int main(int, char**)
{
	int numCams = camCount();
	cout << "Open Cams = " << numCams << endl;

	//Instructions
	cout << "Once opened, press ESC to scroll through cameras" << endl;
	//Endlessly scroll through loop using ESC
	while (true) {
		//displayCams(numCams);
		stitchedView(numCams);
		cam1();
		cam2();
		cam3();
		cam4();
		cam5();
		cam6();
	}
	return 0;
}
