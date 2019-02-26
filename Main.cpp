/**
  @file videocapture_basic.cpp
  @brief A very basic sample for using VideoCapture and VideoWriter
  @author PkLab.net
  @date Aug 24, 2016
*/

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;
//Assigns cameras to variables
VideoCapture cap0(0);
VideoCapture cap1(1);
VideoCapture cap2(2);
VideoCapture cap3(3);
VideoCapture cap4(4);
VideoCapture cap5(5);
//Creates the frame to hold the feed
Mat cameraFrame;

//cam0 - cam5 methods for displaying individual camera feeds. This can be used later for camera selection GUI
void cam0() {
	while (true) {
		if (cap0.isOpened()) { //avoid reading from an unopened device
			cap0.read(cameraFrame); //Reads frame
			imshow("cam1", cameraFrame); //Display Frame
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
void cam1() {
	while (true) {
		if (cap1.isOpened()) { //avoid reading from an unopened device
			cap1.read(cameraFrame); //Reads frame
			imshow("cam1", cameraFrame); //Display Frame
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
		if (cap2.isOpened()) { //avoid reading from an unopened device
			cap2.read(cameraFrame); //Reads frame
			imshow("cam1", cameraFrame); //Display Frame
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
		if (cap3.isOpened()) { //avoid reading from an unopened device
			cap3.read(cameraFrame); //Reads frame
			imshow("cam1", cameraFrame); //Display Frame
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
		if (cap4.isOpened()) { //avoid reading from an unopened device
			cap4.read(cameraFrame); //Reads frame
			imshow("cam1", cameraFrame); //Display Frame
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
		if (cap5.isOpened()) { //avoid reading from an unopened device
			cap5.read(cameraFrame); //Reads frame
			imshow("cam1", cameraFrame); //Display Frame
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

int main(int, char**)
{
	//Notify if a camera is not working
	if (!cap0.isOpened())  
		cout << "Cannot open web cam " << 0 << endl;
	if (!cap1.isOpened())
		cout << "Cannot open web cam " << 1 << endl;
	if (!cap2.isOpened())
		cout << "Cannot open web cam " << 2 << endl;
	if (!cap3.isOpened())
		cout << "Cannot open web cam " << 3 << endl;
	if (!cap4.isOpened())
		cout << "Cannot open web cam " << 4 << endl;
	if (!cap5.isOpened())
		cout << "Cannot open web cam " << 5 << endl;
	//Instructions
	cout << "Once opened, press ESC to scroll through cameras" << endl;

	//Endlessly scroll through loop using ESC
	while (true) {
		cam0();
		cam1();
		cam2();
		cam3();
		cam4();
		cam5();
	}
	return 0;
}
