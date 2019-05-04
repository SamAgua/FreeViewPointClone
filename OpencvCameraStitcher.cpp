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
	VideoCapture capture(0);
	VideoCapture capture2(1);
	std::vector<Mat> imgs(3);
	Mat pic1; //= imread("pic1.jpg", IMREAD_COLOR);
	Mat pic2; //= imread("pic2.jpg", IMREAD_COLOR);
	//Mat pic3 = imread("pic3.jpg", IMREAD_COLOR);
	Mat3b result;
	
	Ptr<Stitcher> stitcher = Stitcher::create();
	for (;;) {
	
		
			capture >> pic1;
			capture2 >> pic2;
			imgs = { pic1, pic2 };
			Stitcher::Status status = stitcher->stitch(imgs, result);
			if (!result.empty()) {
				resize(result, result, Size(1080, 720), 0, 0);
				imshow("stitched", result);
				char key = waitKey(1);
				if (char(key) == 27/*ESC*/) {
					break;
				}
			}
			else {
				cout << "nope: " << status << endl;
				break;
			}
	}
	
}
