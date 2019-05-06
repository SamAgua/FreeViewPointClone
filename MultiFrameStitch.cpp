#include "opencv2/features2d.hpp"

#include <opencv2/core/types.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>  // cv::Canny()
#include <opencv2/stitching.hpp>
#include <iostream>
#include <vector>



using namespace cv;
using std::cout; using std::cerr; using std::endl; using std::vector;
using namespace std;

int main() {
	//VideoCapture capture(0);
	//VideoCapture capture2(1);
	std::vector<Mat> imgs(5);
	Mat pic1 = imread("pic1.jpg", IMREAD_COLOR);
	Mat pic2 = imread("pic2.jpg", IMREAD_COLOR);
	Mat pic3 = imread("pic3.jpg", IMREAD_COLOR);
	Mat pic4 = imread("pic4.jpg", IMREAD_COLOR);
	Mat pic5 = imread("pic5.jpg", IMREAD_COLOR);
	Mat3b result;
	
	Ptr<Stitcher> stitcher = Stitcher::create();
	
	
			imgs = { pic1, pic2, pic3, pic4, pic5 };
			Stitcher::Status status = stitcher->stitch(imgs, result);
			if (!result.empty()) {
				resize(result, result, Size(1080, 720), 0, 0);
				for (;;) {
					imshow("stitched", result);
					char key = waitKey(1);
					if (char(key) == 27/*ESC*/) {
						break;
					}
				}
			}
			else cout << "nope: not enough keypoints or images " << status << endl;
	}