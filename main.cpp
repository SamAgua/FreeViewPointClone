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
	/*
	Mat frame1;
	Mat frame2;
	cout << "Opening camera..." << endl;
	VideoCapture capture0(0); // open the first camera
	VideoCapture capture1(1);
	*/

	//VideoCapture capture0(0);

	std::vector<int> cams{ 0,0,0,0,0,0 };
	int numCams = 0;

	for (int i = 0; i < 2; ++i) {
		VideoCapture capture0(i);
		if (capture0.isOpened()) {
			cams[i] = 1;
			numCams++;
			cout << "after emplace i = " << i << endl;
			cout << "after emplace numCams = " << numCams << endl;
		}
	}
	//vector<Mat3b> feedArray;
	//Mat3b finalFrame;
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
	Mat finalFrame;
	

	for (;;)
	{
		//Mat3b finalFrame;
		switch (numCams) {
		case 0: cout << "no cams detected" << endl;
			exit(0);
			break;
		case 1: {
			capture1 >> frame1;
			imshow("oneFrame", frame1);
			break;
		}
		case 2: {
			
			capture1;
			capture2;
			
			
			capture1 >> frame1;
			capture2 >> frame2;
			std::vector<Mat> matArray = { frame1, frame2 };
			hconcat(matArray, finalFrame);
			imshow("twoFrame", finalFrame);
			}
		}
		
		char key = waitKey(1);
		if (char(key) == 27/*ESC*/) break;
	}
	cams.clear();
	return 0;
}
