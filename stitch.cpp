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
	const double nn_match_ratio = 0.8f; // Nearest-neighbour matching ratio
	Mat src;
	Mat src2;
	src = imread("iqbal1.png", IMREAD_COLOR);
	src2 = imread("iqbal2.png", IMREAD_COLOR);

	if (src.empty())
	{
		cout << "Could not open or find the image!\n" << endl;

		return -1;
	}
	
		//-- Step 1: Detect the keypoints using SURF Detector
		
		int minHessian = 500;
		Mat desc1, desc2;
		Ptr<ORB> detector = ORB::create();
		detector->setMaxFeatures(minHessian);
		Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");
		std::vector<KeyPoint> keypoints1, keypoints2;

		detector->detectAndCompute(src, noArray(), keypoints1, desc1);
		detector->detectAndCompute(src2,  noArray(), keypoints2, desc2);

		std::vector< std::vector<DMatch> > knn_matches;
		matcher->knnMatch(desc1, desc2, knn_matches, 2);
		//-- Filter matches using the Lowe's ratio test
	
		//std::vector< std::vector<DMatch> > good_matches;
		std::vector<KeyPoint> matched1, matched2;
		for (unsigned i = 0; i < knn_matches.size(); i++) {
			if (knn_matches[i][0].distance < nn_match_ratio * knn_matches[i][1].distance) {
				matched1.push_back(keypoints1[knn_matches[i][0].queryIdx]);
				matched2.push_back(keypoints2[knn_matches[i][0].trainIdx]);
			}
		}
		int max1 = 0;
		int max2 = 0;
		std::vector<KeyPoint>::const_iterator it = matched1.begin(), end = matched1.end();
		for (; it != end; ++it) {
			if (it->pt.x > max1) {
				max1 = it->pt.x;
			}
		}
		std::vector<KeyPoint>::const_iterator it2 = matched2.begin(), end2 = matched2.end();
		for (; it2 != end2; ++it2) {
			if (it2->pt.x > max2) {
				max2 = it2->pt.x;
			}
		}
		int left = max1 / matched1.size();
		int right = max2 / matched1.size();

		std::cout << max1 <<" " << max2 << std::endl;

		int h = 600;
		Mat test = cv::Mat::zeros(cv::Size(340*2, h), CV_8UC3);
		Mat small1 = cv::Mat(src, cv::Rect(0, 0, max1, src.rows));
		resize(small1, small1, cv::Size(340, h),0,0);
		//cv::Rect myROI(max2, 0, src2.cols, src2.rows);
		
		Mat small2 = src2(Rect(max2, 0, src2.cols - max2, src2.rows));
		resize(small2, small2, cv::Size(340, h),0,0);

		small1.copyTo(test(Rect(0, 0, small1.cols, h)));
		small2.copyTo(test(Rect(small1.cols, 0, small2.cols, small2.rows)));
		//drawMatches(src, matched1, src2, matched2, knn_matches, img_matches, Scalar(255,0,0),
		//	Scalar(255, 0, 0));
		//-- Show detected matches
		
		
		for (;;) {
			imshow("Good Matches", test);

			char key = waitKey(0);
			if (char(key) == 27)
				break;
		}
	return 0;
}
