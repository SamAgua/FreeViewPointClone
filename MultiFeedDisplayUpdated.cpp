//Multifeed display implemented with zoomin/zoomout functionalities into the methods


#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
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
Mat resize1;
Mat resize2;
Mat resize3;
Mat resize4;
Mat resize5;
Mat resize6;
std::vector<Mat> matArray1;
std::vector<Mat> matArray2;
Mat3b finalFrame;
//Creates the frame to hold the feed
double frameRatio = 0.6;
Rect myROI(32, 24, 576, 432);
//640x480 norm
Rect myROI2(64, 48, 512, 384);
Rect myROI3(128, 96, 384, 288);
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
		if (char(key) == 27/*ESC*/)
			break;
	}

}
//cam0 - cam5 methods for displaying individual camera feeds. This can be used later for camera selection GUI
// currently arrow keys (0) and spacebar (32) are placeholders for button click
void cam1() {
	double count = 1.0;
	double dec = .1;
	int zm = 0;

	while (true) {
		if (capture1.isOpened()) { //avoid reading from an unopened device
			capture1.read(frame1); //Reads frame
			imshow("Camera Feed", frame1); //Display Frame
		}
		else {
			break; // If no camera, breaks from method
		}
		int keypress = waitKey(1); //saving the pressed key
		if (keypress == 0) { // if arrow keys pressed (placeholder for button click)
			
			zm++; //counter for incrementing which zoom frame
			while (true) {

				if (capture1.isOpened()) {
				ZoomIn:
					if (zm == 1) { //for first zoom in frame
						capture1.isOpened();
						capture1.read(frame1);
						resize1 = frame1(myROI);
						resize(resize1, resize2, Size(frame1.cols, frame1.rows));
						imshow("Zooming In", resize2);
					}

					else if (zm == 2) { //for second zoom in frame
						capture1.isOpened();
						capture1.read(frame1);
						resize1 = frame1(myROI2);
						resize(resize1, resize2, Size(frame1.cols, frame1.rows));
						imshow("Zooming In", resize2);
					}

					else if (zm == 3) { //for third zoom in frame
						capture1.isOpened();
						capture1.read(frame1);
						resize1 = frame1(myROI3);
						resize(resize1, resize2, Size(frame1.cols, frame1.rows));
						imshow("Zooming In", resize2);

					}
				}
				else {
					break;
				}
					int keypress = waitKey(1);
					if (keypress == 0) { //pressing to zoom in again
						if (zm == 3) {
							zm = 0;
						}
						zm++;
						goto ZoomIn; //send back to zoomin jump placeholder
					}
					if (keypress == 27) { //exits zooming in window
						destroyWindow("Zooming In");
						break;
					}
					if (keypress == 32) { //sends to zooming out function with spacebar (placeholder for button click)
						destroyWindow("Zooming In");
						goto ZoomOut;
					}
				}
			}
			if (keypress == 32) { //if spacebar(32) pressed it zooms out window. Currently placeholder for button click.
				count -= dec; //counter for decrementing
				while (true) {

					if (capture1.isOpened()) {
					ZoomOut:
						capture1.isOpened();
						
						capture1.read(frame1);
						resize(frame1, resize1, Size(frame1.cols * count, frame1.rows * count)); //resizing frame for zooming out winbdow
						imshow("Zooming Out", resize1);
					}
					else {
						break;
					}
					int keypress = waitKey(1);
					if (keypress == 32) {//if spacebar continuously selected then will continue to zoom out
						count -= dec; //dec counter
						if (count < .6 || count > 1.0) {////checks for certain magnification to reset if too large or small
							count = 1.0;
						}
						goto ZoomOut;
					}
					if (keypress == 27) { // destroys zooming out window
						destroyWindow("Zooming Out");
						break;
					}
					if (keypress == 0) { //sends to zooming In function with arrow keys (placeholder for button click)
						destroyWindow("Zooming Out");
						goto ZoomIn;
				
			}
		}
	}
	if (keypress == 27) {//if pressed Esc key breaks from method
		break;
	}

}
}
void cam2() {
	double count = 1.0;
	double dec = .1;
	int zm = 0;

	while (true) {
		if (capture2.isOpened()) { //avoid reading from an unopened device
			capture2.read(frame2); //Reads frame
			imshow("Camera Feed", frame2); //Display Frame
		}
		else {
			break; // If no camera, breaks from method
		}
		int keypress = waitKey(1); //saving the pressed key
		if (keypress == 0) { // if arrow keys pressed (placeholder for button click)

			zm++; //counter for incrementing which zoom frame
			while (true) {

				if (capture2.isOpened()) {
				ZoomIn:
					if (zm == 1) { //for first zoom in frame
						capture2.isOpened();
						capture2.read(frame2);
						resize3 = frame2(myROI);
						resize(resize3, resize4, Size(frame1.cols, frame1.rows));
						imshow("Zooming In", resize4);
					}

					else if (zm == 2) { //for second zoom in frame
						capture2.isOpened();
						capture2.read(frame2);
						resize3 = frame1(myROI2);
						resize(resize3, resize4, Size(frame1.cols, frame1.rows));
						imshow("Zooming In", resize4);
					}

					else if (zm == 3) { //for third zoom in frame
						capture2.isOpened();
						capture2.read(frame2);
						resize3 = frame1(myROI3);
						resize(resize3, resize4, Size(frame1.cols, frame1.rows));
						imshow("Zooming In", resize4);

					}
				}
				else {
					break;
				}
				int keypress = waitKey(1);
				if (keypress == 0) { //pressing to zoom in again
					if (zm == 3) {
						zm = 0;
					}
					zm++;
					goto ZoomIn; //send back to zoomin jump placeholder
				}
				if (keypress == 27) { //exits zooming in window
					destroyWindow("Zooming In");
					break;
				}
				if (keypress == 32) { //sends to zooming out function with spacebar (placeholder for button click)
					destroyWindow("Zooming In");
					goto ZoomOut;
				}
			}
		}
		if (keypress == 32) { //if spacebar(32) pressed it zooms out window. Currently placeholder for button click.
			count -= dec; //counter for decrementing
			while (true) {

				if (capture1.isOpened()) {
				ZoomOut:
					capture1.isOpened();
					
					capture1.read(frame1);
					resize(frame1, resize1, Size(frame1.cols * count, frame1.rows * count)); //resizing frame for zooming out winbdow
					imshow("Zooming Out", resize1);
				}
				else {
					break;
				}
				int keypress = waitKey(1);
				if (keypress == 32) {//if spacebar continuously selected then will continue to zoom out
					count -= dec; //dec counter
					if (count < .6 || count > 1.0) {////checks for certain magnification to reset if too large or small
						count = 1.0;
					}
					goto ZoomOut;
				}
				if (keypress == 27) { // destroys zooming out window
					destroyWindow("Zooming Out");
					break;
				}
				if (keypress == 0) { //sends to zooming In function with arrow keys (placeholder for button click)
					destroyWindow("Zooming Out");
					goto ZoomIn;

				}
			}
		}
		if (keypress == 27) {//if pressed Esc key breaks from method
			break;
		}

	}
}
void cam3() {

	double count = 1.0;
	double inc = .2;
	double dec = .1;

	while (true) {
		if (capture3.isOpened()) { //avoid reading from an unopened device
			capture3.read(frame3); //Reads frame
			imshow("Camera Feed", frame3); //Display Frame
		}
		else {
			break; // If no camera, breaks from method
		}
		int keypress = waitKey(1); //saving the pressed key
		if (keypress == 0) { // if arrow keys pressed (placeholder for button click)
			count += inc; //counter for incrementing
			while (true) {

				if (capture3.isOpened()) {
					capture3.isOpened();
				ZoomIn: //zoom in jump placeholder when switching between zooming in and out
					capture3.read(frame3);
					resize(frame3, resize3, Size(frame1.cols * count, frame1.rows * count)); //resizing of the window
					imshow("Zooming In", resize3);
				}
				else {
					break;
				}
				int keypress = waitKey(1);
				if (keypress == 0) { //for further zooming in
					count += inc;
					if (count < 1.0 || count > 1.6) { //checks for certain magnification to reset if too large or small
						count = 1.2;
					}
					goto ZoomIn; //send back to zoomin jump placeholder
				}
				if (keypress == 27) { //exits zooming in window
					destroyWindow("Zooming In");
					break;
				}
				if (keypress == 32) { //sends to zooming out function with spacebar (placeholder for button click)
					destroyWindow("Zooming In");
					goto ZoomOut;
				}
			}
		}
		if (keypress == 32) { //if spacebar(32) pressed it zooms out window. Currently placeholder for button click.
			count -= dec; //counter for decrementing
			while (true) {

				if (capture3.isOpened()) {
					capture3.isOpened();
				ZoomOut: //jump area for zooming out from other window/loop
					capture3.read(frame3);
					resize(frame3, resize3, Size(frame1.cols * count, frame1.rows * count)); //resizing frame for zooming out winbdow
					imshow("Zooming Out", resize3);
				}
				else {
					break;
				}
				int keypress = waitKey(1);
				if (keypress == 32) {//if spacebar continuously selected then will continue to zoom out
					count -= dec; //dec counter
					if (count < .6 || count > 1.0) {////checks for certain magnification to reset if too large or small
						count = 1.0;
					}
					goto ZoomOut;
				}
				if (keypress == 27) { // destroys zooming out window
					destroyWindow("Zooming Out");
					break;
				}
				if (keypress == 0) { //sends to zooming In function with arrow keys (placeholder for button click)
					destroyWindow("Zooming Out");
					goto ZoomIn;
				}
			}
		}

		if (keypress == 27) {//if pressed Esc key breaks from method
			break;
		}
	}
}
void cam4() {

	double count = 1.0;
	double inc = .2;
	double dec = .1;

	while (true) {
		if (capture4.isOpened()) { //avoid reading from an unopened device
			capture4.read(frame4); //Reads frame
			imshow("Camera Feed", frame4); //Display Frame
		}
		else {
			break; // If no camera, breaks from method
		}
		int keypress = waitKey(1); //saving the pressed key
		if (keypress == 0) { // if arrow keys pressed (placeholder for button click)
			count += inc; //counter for incrementing
			while (true) {

				if (capture4.isOpened()) {
					capture4.isOpened();
				ZoomIn: //zoom in jump placeholder when switching between zooming in and out
					capture4.read(frame4);
					resize(frame4, resize4, Size(frame1.cols * count, frame1.rows * count)); //resizing of the window
					imshow("Zooming In", resize4);
				}
				else {
					break;
				}
				int keypress = waitKey(1);
				if (keypress == 0) { //for further zooming in
					count += inc;
					if (count < 1.0 || count > 1.6) { //checks for certain magnification to reset if too large or small
						count = 1.2;
					}
					goto ZoomIn; //send back to zoomin jump placeholder
				}
				if (keypress == 27) { //exits zooming in window
					destroyWindow("Zooming In");
					break;
				}
				if (keypress == 32) { //sends to zooming out function with spacebar (placeholder for button click)
					destroyWindow("Zooming In");
					goto ZoomOut;
				}
			}
		}
		if (keypress == 32) { //if spacebar(32) pressed it zooms out window. Currently placeholder for button click.
			count -= dec; //counter for decrementing
			while (true) {

				if (capture4.isOpened()) {
					capture4.isOpened();
				ZoomOut: //jump area for zooming out from other window/loop
					capture4.read(frame4);
					resize(frame4, resize4, Size(frame1.cols * count, frame1.rows * count)); //resizing frame for zooming out winbdow
					imshow("Zooming Out", resize4);
				}
				else {
					break;
				}
				int keypress = waitKey(1);
				if (keypress == 32) {//if spacebar continuously selected then will continue to zoom out
					count -= dec; //dec counter
					if (count < .6 || count > 1.0) {////checks for certain magnification to reset if too large or small
						count = 1.0;
					}
					goto ZoomOut;
				}
				if (keypress == 27) { // destroys zooming out window
					destroyWindow("Zooming Out");
					break;
				}
				if (keypress == 0) { //sends to zooming In function with arrow keys (placeholder for button click)
					destroyWindow("Zooming Out");
					goto ZoomIn;
				}
			}
		}

		if (keypress == 27) {//if pressed Esc key breaks from method
			break;
		}
	}
}
void cam5() {

	double count = 1.0;
	double inc = .2;
	double dec = .1;

	while (true) {
		if (capture5.isOpened()) { //avoid reading from an unopened device
			capture5.read(frame5); //Reads frame
			imshow("Camera Feed", frame5); //Display Frame
		}
		else {
			break; // If no camera, breaks from method
		}
		int keypress = waitKey(1); //saving the pressed key
		if (keypress == 0) { // if arrow keys pressed (placeholder for button click)
			count += inc; //counter for incrementing
			while (true) {

				if (capture5.isOpened()) {
					capture5.isOpened();
				ZoomIn: //zoom in jump placeholder when switching between zooming in and out
					capture5.read(frame5);
					resize(frame5, resize5, Size(frame1.cols * count, frame1.rows * count)); //resizing of the window
					imshow("Zooming In", resize5);
				}
				else {
					break;
				}
				int keypress = waitKey(1);
				if (keypress == 0) { //for further zooming in
					count += inc;
					if (count < 1.0 || count > 1.6) { //checks for certain magnification to reset if too large or small
						count = 1.2;
					}
					goto ZoomIn; //send back to zoomin jump placeholder
				}
				if (keypress == 27) { //exits zooming in window
					destroyWindow("Zooming In");
					break;
				}
				if (keypress == 32) { //sends to zooming out function with spacebar (placeholder for button click)
					destroyWindow("Zooming In");
					goto ZoomOut;
				}
			}
		}
		if (keypress == 32) { //if spacebar(32) pressed it zooms out window. Currently placeholder for button click.
			count -= dec; //counter for decrementing
			while (true) {

				if (capture5.isOpened()) {
					capture5.isOpened();
				ZoomOut: //jump area for zooming out from other window/loop
					capture5.read(frame5);
					resize(frame5, resize5, Size(frame1.cols * count, frame1.rows * count)); //resizing frame for zooming out winbdow
					imshow("Zooming Out", resize5);
				}
				else {
					break;
				}
				int keypress = waitKey(1);
				if (keypress == 32) {//if spacebar continuously selected then will continue to zoom out
					count -= dec; //dec counter
					if (count < .6 || count > 1.0) {////checks for certain magnification to reset if too large or small
						count = 1.0;
					}
					goto ZoomOut;
				}
				if (keypress == 27) { // destroys zooming out window
					destroyWindow("Zooming Out");
					break;
				}
				if (keypress == 0) { //sends to zooming In function with arrow keys (placeholder for button click)
					destroyWindow("Zooming Out");
					goto ZoomIn;
				}
			}
		}

		if (keypress == 27) {//if pressed Esc key breaks from method
			break;
		}
	}
}
void cam6() {

	double count = 1.0;
	double inc = .2;
	double dec = .1;

	while (true) {
		if (capture6.isOpened()) { //avoid reading from an unopened device
			capture6.read(frame6); //Reads frame
			imshow("Camera Feed", frame6); //Display Frame
		}
		else {
			break; // If no camera, breaks from method
		}
		int keypress = waitKey(1); //saving the pressed key
		if (keypress == 0) { // if arrow keys pressed (placeholder for button click)
			count += inc; //counter for incrementing
			while (true) {

				if (capture6.isOpened()) {
					capture6.isOpened();
				ZoomIn: //zoom in jump placeholder when switching between zooming in and out
					capture6.read(frame6);
					resize(frame6, resize6, Size(frame1.cols * count, frame1.rows * count)); //resizing of the window
					imshow("Zooming In", resize6);
				}
				else {
					break;
				}
				int keypress = waitKey(1);
				if (keypress == 0) { //for further zooming in
					count += inc;
					if (count < 1.0 || count > 1.6) { //checks for certain magnification to reset if too large or small
						count = 1.2;
					}
					goto ZoomIn; //send back to zoomin jump placeholder
				}
				if (keypress == 27) { //exits zooming in window
					destroyWindow("Zooming In");
					break;
				}
				if (keypress == 32) { //sends to zooming out function with spacebar (placeholder for button click)
					destroyWindow("Zooming In");
					goto ZoomOut;
				}
			}
		}
		if (keypress == 32) { //if spacebar(32) pressed it zooms out window. Currently placeholder for button click.
			count -= dec; //counter for decrementing
			while (true) {

				if (capture6.isOpened()) {
					capture6.isOpened();
				ZoomOut: //jump area for zooming out from other window/loop
					capture6.read(frame6);
					resize(frame6, resize6, Size(frame1.cols * count, frame1.rows * count)); //resizing frame for zooming out winbdow
					imshow("Zooming Out", resize6);
				}
				else {
					break;
				}
				int keypress = waitKey(1);
				if (keypress == 32) {//if spacebar continuously selected then will continue to zoom out
					count -= dec; //dec counter
					if (count < .6 || count > 1.0) {////checks for certain magnification to reset if too large or small
						count = 1.0;
					}
					goto ZoomOut;
				}
				if (keypress == 27) { // destroys zooming out window
					destroyWindow("Zooming Out");
					break;
				}
				if (keypress == 0) { //sends to zooming In function with arrow keys (placeholder for button click)
					destroyWindow("Zooming Out");
					goto ZoomIn;
				}
			}
		}

		if (keypress == 27) {//if pressed Esc key breaks from method
			break;
		}
	}
}
*/
int main(int, char**)
{
	int numCams = camCount();
	cout << "Open Cams = " << numCams << endl;
	//Instructions
	cout << "Once opened, press ESC to scroll through cameras" << endl;
	//Endlessly scroll through loop using ESC
	while (true) {
		displayCams(numCams);
		cam1();
		//cam2();
		//cam3();
		//cam4();
		//cam5();
		//cam6();
	}
	return 0;
}