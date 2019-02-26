#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>  // cv::Canny()
#include <iostream>
#include <vector>

using namespace cv;
using std::cout; using std::cerr; using std::endl; using std::vector;

class Feed{
public:
	int cameraNo;
	Mat3b frame;
	
	Feed(int c_no)
		:cameraNo(c_no)
	{
	}
	void setFrame(int i, std::vector<cv::Mat3b>* feedArray);
	
	~Feed();
};
void Feed::setFrame(int i, std::vector<cv::Mat3b>* feedArray) {
	VideoCapture capture(i);
	capture >> frame;
	feedArray->push_back(frame);
	return;
}
Feed::~Feed() {
}

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
	
	
	std::vector<Feed> cams;
	
	for (int i = 0; i < 2; ++i) {
		VideoCapture capture0(i);
		if (capture0.isOpened()) {
			cams.emplace_back(i);
			cout << "after emplace i = " << i << endl;
		}
	}
	//if (!capture0.isOpened())
	//{
	//	cerr << "ERROR: Can't initialize camera capture" << endl;
	//	return 1;
	//}
	vector<Mat3b> feedArray;
	Mat3b finalFrame;

	for (;;)
	{
		for (auto i : cams) {
			cout << "cams i.no" << i.cameraNo << endl;
			i.setFrame(i.cameraNo, &feedArray);

		}
		hconcat(feedArray, finalFrame);
		if (finalFrame.empty())
		{
			cerr << "ERROR: Can't grab camera frame." << endl;
			break;
		}
		imshow("Frame", finalFrame);
		feedArray.clear();
		char key = waitKey(1);
		if (char(key) == 27/*ESC*/) break;
	}
	cams.clear();
	return 0;
}
