/* 
Multiple Camera Feed Display
FreeViewpoint Group 1
Author: Samuel Aguayo
Date: March 11, 2019

This program takes all current available Video Cameras at the start of the program,
and will display six different feeds. If less than 6 Cameras are detected, a blue 
screen will replace the feed. This program does not handle plug and play functionalites:All
cameras must be connected before starting up the program to be displayed. If a camera is 
disconnected during runtime, the program will terminate.
*/

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>  // cv::Canny()
#include <iostream>
#include <vector>

using namespace cv;
using std::cout; using std::cerr; using std::endl; using std::vector;



int main(int, char**)
{
	int numCams = 0;				// number of cameras to be detected
	double frameRatio = 0.6;			// variable size for output display of frames. 1 is original size, 0.5 is half original. 
	cout << "checking for cams" << endl;

	//Run through devices. If a camera is detecable and capable of pulling frames, increment numCams
	for (int i = 0; i < 7; ++i) {
		VideoCapture capture0(i);
		if (capture0.isOpened()) {
			numCams++;
		}
	}

	//If system detects 1 more camera than actual (which is common), add numCams-- to avaoid crash.
	//numCams--;
	cout << "numCams: " << numCams << endl;
	cout << "Opening cams ..." << endl;

	/* Attempt to open 6 cameras. This will open all available cameras once to avoid
	constant openning and closing, slowing tdown the program*/
	VideoCapture capture1(0);
	VideoCapture capture2(1);
	VideoCapture capture3(2);
	VideoCapture capture4(3);
	VideoCapture capture5(4);
	VideoCapture capture6(5);

	//Create frames that will display
	Mat blueFrame;
	Mat frame1;
	Mat frame2;
	Mat frame3;
	Mat frame4;
	Mat frame5;
	Mat frame6;
	Mat top;
	Mat bot;

	// Vectors that will hold _Mat_ types to be stitched
	std::vector<Mat> matArray1;
	std::vector<Mat> matArray2;

	//Frame to be displayed to user
	Mat3b finalFrame;

	//Run until manual break from user
	for (;;)
	{
		//Read blue image, save as frame
		blueFrame = imread("Bb_blue.jpg", IMREAD_COLOR);
		
		/*switch on numCams. This won't allow for plug and play, but optimizes for realtime display of 
		camera feeds. */
		switch (numCams) {
		case 0: cout << "no cams detected" << endl; //if no video cameras were found, display err msg, terminate program.
			exit(0);
			break;
		case 1: {
			//call all cameras available for display
			capture1;

			//capture single frame from all cameras, send to _Mat_ type
			capture1 >> frame1;

			//All feeds will be resized with respect to camera one size*frameRatio
			resize(frame1, frame1, Size(), frameRatio, frameRatio);
			resize(blueFrame, blueFrame, Size(frame1.cols, frame1.rows), 0, 0);	//resize bluescreen

			//all unavailble feeds will be replaced with a blue frame
			frame2 = blueFrame;
			frame3 = blueFrame;
			frame4 = blueFrame;
			frame5 = blueFrame;
			frame6 = blueFrame;

			//add cams 1, 2, 3 and 4, 5, 6 into vectors
			//stitch frames in vectors to create top and bot
			//stitch top and bot to create one single frame, as to display one window to user
			matArray1 = { frame1, frame2, frame3 };
			matArray2 = { frame4, frame5, frame6 };
			hconcat(matArray1, top);
			hconcat(matArray2, bot);
			vconcat(top, bot, finalFrame);

			// display all to user, cameras and bluescreen all in one window
			imshow("cam1", finalFrame);
			break;
		}
		case 2: {

			capture1;
			capture2;

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
			
			imshow("cam2", finalFrame);
			break;
		}
		case 3: {
			capture1;
			capture2;
			capture3;

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
			
			imshow("cams3", finalFrame);
			break;
		}
		case 4: {
			capture1;
			capture2;
			capture3;
			capture4;


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
			
			imshow("cams4", finalFrame);
			break;
		}
		case 5: {
			capture1;
			capture2;
			capture3;
			capture4;
			capture5;

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
			
			imshow("cams5", finalFrame);
			break;
		}
		case 6: {
			capture1;
			capture2;
			capture3;
			capture4;
			capture5;
			capture6;

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
			
			imshow("cams6", finalFrame);
			break;
		}
		}
		//user ends program with esc key press
		char key = waitKey(1);
		if (char(key) == 27/*ESC*/)
			break;
	}
	return 0;
}
