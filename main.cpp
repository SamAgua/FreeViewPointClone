#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/stitching.hpp>
#include <opencv2/imgproc.hpp>  // cv::Canny()
#include <iostream>
#include <vector>
#include <thread>
using namespace cv;
using std::cout; using std::cerr; using std::endl; using std::vector;
using namespace std;
//Assigns cameras to variables

bool pause = false;
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
std::vector<Mat> matArray1 = {frame1, frame2};
std::vector<Mat> matArray2;
std::vector<Mat> matArray3;
std::vector<Mat> stitchedArray;
Mat finalFrame;
//Creates the frame to hold the feed
double frameRatio = 0.6;

void stitchFrames(std::vector<Mat> arr);

void stopStream()
{
	pause = true;
}

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

void setFrame(Mat frame, VideoCapture cap, int cam) {
	cap >> frame;
	switch (cam) {
	case 1:
		matArray1[0] = frame;
		break;
	case 2:
		matArray1[1] = frame;
		break;
	case 3:
		matArray2[0] = frame;
		break;
	case 4:
		matArray2[1] = frame;
		break;
	case 5:
		matArray3[0] = frame;
		break;
	case 6:
		matArray3[1] = frame;
		break;
	default:
		break;
	}
}



void stitchedView(int numCams) {
	while(true)
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
			thread t1(setFrame, frame1, capture1, 1);
			thread t2(setFrame, frame2, capture2, 2);
			t1.join();
			t2.join();

			stitchFrames(matArray1);
		
			imshow("Camera Feed", finalFrame);
			break;
		}
		case 3: {
			capture1 >> frame1;
			capture2 >> frame2;
			capture3 >> frame3;
			stitchedArray = { frame1, frame2, frame3 };
			//finalFrame = stitchFrames(stitchedArray);
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
			//finalFrame = stitchFrames(stitchedArray);
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
			//finalFrame = stitchFrames(stitchedArray);
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
			stitchFrames(stitchedArray);
			imshow("Camera Feed", finalFrame);
			break;
		}
		}
		char key = waitKey(1);
		if (char(key) == 27)
			break;
	}

}


void stitchFrames(std::vector<Mat> matArr) {
	Ptr<Stitcher> stitcher = Stitcher::create();
	Stitcher::Status status = stitcher->stitch(matArr, finalFrame);
	if (finalFrame.empty()) {
		cout << "Unable to pull from display " << endl;
	}
	if (status != Stitcher::OK) {
		cout << int(status) << endl;
	}
}
void singleDisplay(VideoCapture capture, Mat frame) {
	pause = false;
	while (!pause) {
		if (capture.isOpened()) { //avoid reading from an unopened device
			capture >> frame;
			imshow("Camera Feed", frame); //Display Frame
		}
		else {
			break; // If no camera, breaks from method
		}
		int keypress = waitKey(1); //saving the pressed key
		if (keypress == 27) {//if pressed Esc key breaks from method
			pause = false;
			break;
		}
		if (keypress == 32) {//if Spacebar
			pause = true;
			break;
		}
	}
}

int main(int, char**)
{
	int numCams = camCount();
	cout << "Open Cams = " << numCams << endl;
	//Instructions
	cout << "Once opened, press ESC to scroll through cameras" << endl;
	cout << "Press Spacebar to stop and start the stream" << endl;
	//Endlessly scroll through loop using ESC
	stitchedView(numCams);
	
	return 0;
}
