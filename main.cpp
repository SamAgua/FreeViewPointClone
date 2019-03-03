#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>  // cv::Canny()
#include <iostream>
#include <vector>
#include <thread>          

using namespace std;
using namespace cv;

//global variables
bool pause = true;
VideoCapture cap1;
Mat frame;

//dummy method for testing purposes
Mat getView() {
	cap1 >> frame;
	return frame;
}

//stops stream
void stopStream()
{
	pause = true;
}

//thread for running stream
void runStream()
{
	pause = false;
	while (!pause) {
		Mat viewFrame = getView(); //assumes getView() returns the viewing frame
		imshow("Play/Pause view", viewFrame);
	}
}

int main() {
	cap1.isOpened();
	cout << "Press spacebar to start and stop stream" << endl << "Press Esc to exit program" << endl;
	while (true) {
		char key = waitKey(1);
		switch (key) {
		case 32: {
			if (pause == true)
				runStream();
			else
				stopStream();
			break;
		}
		case 27: {
			return 0;
		}
		}
	}
}