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
		const float ratio_thresh = 0.7f;
		std::vector<DMatch> good_matches;
		for (size_t i = 0; i < knn_matches.size(); i++)
		{
			if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
			{
				good_matches.push_back(knn_matches[i][0]);
			}
		}

		Mat img_matches;
		drawMatches(src, keypoints1, src2, keypoints2, good_matches, img_matches, Scalar::all(-1),
			Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::DEFAULT);
		//-- Show detected matches
		

		for (;;) {
			imshow("Good Matches", img_matches);

			char key = waitKey(0);
			if (char(key) == 27/*ESC*/)
				break;
		}
	return 0;
}
