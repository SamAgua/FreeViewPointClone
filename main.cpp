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
	int numCams = 0;
	double frameRatio = 0.6;
	cout << "checking for cams" << endl;
	
	for (int i = 0; i < 7; ++i) {
		VideoCapture capture0(i);
		if (capture0.isOpened()) {
			numCams++;
		}
	}
	
	numCams--;
	cout << "numCams: " << numCams << endl;
	cout << "Opening cams ..." << endl;

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
	Mat3b finalFrame;
	

	for (;;)
	{
		blueFrame = imread("Bb_blue.jpg", IMREAD_COLOR);
		//Mat3b finalFrame;
		switch (numCams) {
		case 0: cout << "no cams detected" << endl;
			exit(0);
			break;
		case 1: {
			capture1;
			
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
			//namedWindow("cam1", WINDOW_AUTOSIZE);
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
			//namedWindow("cam1", WINDOW_AUTOSIZE);
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
			//namedWindow("cam1", WINDOW_AUTOSIZE);
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
			//namedWindow("cam1", WINDOW_AUTOSIZE);
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
			//namedWindow("cam1", WINDOW_AUTOSIZE);
			imshow("cams6", finalFrame);
			break;
			}
		}
		char key = waitKey(1);
		if (char(key) == 27/*ESC*/)
			break;
	}
	return 0;
}
