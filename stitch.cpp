#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"

using namespace cv;
using namespace cv::xfeatures2d;
using std::cout;
using std::endl;
int main(int argc, char* argv[])
{

	Mat src;
	src = imread("iqbal1.png", IMREAD_COLOR);
	if (src.empty())
	{
		cout << "Could not open or find the image!\n" << endl;

		return -1;
	}
	
		//-- Step 1: Detect the keypoints using SURF Detector
		
		int minHessian = 400;
		Ptr<SURF> detector = SURF::create(minHessian);
		//detector->setHessianThreshold(minHessian);
		std::vector<KeyPoint> keypoints;
		detector->detect(src, keypoints);
		//-- Draw keypoints
		Mat img_keypoints;
		drawKeypoints(src, keypoints, img_keypoints);
		//-- Show detected (drawn) keypoints
		for (;;) {
			imshow("SURF Keypoints", img_keypoints);

			char key = waitKey(0);
			if (char(key) == 27/*ESC*/)
				break;
		}
	return 0;
}
