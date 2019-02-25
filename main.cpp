#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>  // cv::Canny()
#include <iostream>
#include <vector>

using namespace cv;
using std::cout; using std::cerr; using std::endl;

class Feed{
public:
	int cameraNo;
	Mat frame;
	
	Feed(int c_no)
		:cameraNo(c_no)
	{
	}
	void setFrame(int i, std::vector<cv::Mat> *feedArray);
	
	~Feed() {

	}
};
void Feed::setFrame(int i, std::vector<cv::Mat> *feedArray) {
	VideoCapture capture(i);
	capture >> frame;
	feedArray->push_back(frame);
	
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
	Mat finalFrame;
	VideoCapture capture0(0);
	//int cams[] = { 0, 0, 0, 0, 0, 0 };
	std::vector<cv::Mat> feedArray;
	std::vector<Feed> cams;
	
	for (int i = 0; i < 2; ++i) {
		VideoCapture capture0(i);
		if (capture0.isOpened()) {
			cams.emplace_back(i);
			cout << "after emplace i = " << i << endl;
		}
	}
	if (!capture0.isOpened())
	{
		cerr << "ERROR: Can't initialize camera capture" << endl;
		return 1;
	}

	for (;;)
	{
		for (auto i : cams) {
			cout << "cams i.no" << i.cameraNo << endl;
			i.setFrame(i.cameraNo, &feedArray);

		}
		/*capture0 >> frame1; // read the next frame from camera
		capture1 >> frame2;*/

		hconcat(feedArray, finalFrame);
		if (finalFrame.empty())
		{
			cerr << "ERROR: Can't grab camera frame." << endl;
			break;
		}
		imshow("Frame", finalFrame);
		
		int key = waitKey(1);
		if (key == 27/*ESC*/)
			break;
	}
	
	return 0;
}
