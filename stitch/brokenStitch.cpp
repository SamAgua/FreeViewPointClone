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

	Mat src, src2;

	Ptr<Stitcher> stitcher = Stitcher::create();


	VideoCapture cap1("./cam1.avi");
	VideoCapture cap2("./cam2.avi");
	VideoWriter writer;
	Mat test;
	Mat3b test2;
	std::vector<Mat> imgs(2);
	bool isColor = (src.type() == CV_8UC3);

	int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');  // select desired codec (must be available at runtime)
	double fps = 25.0;                          // framerate of the created video stream
	string filename = "./result.avi";             // name of the output video file
	writer.open(filename, codec, fps, Size(720, 480), isColor);
	// check if we succeeded
	if (!writer.isOpened()) {
		cerr << "Could not open the output video file for write\n";

	}
	for (int i = 0; i <= 10; i++) {
		cap1 >> src;

		cap2 >> src2;
		if (!src2.empty()) {


			cout << "ran" << endl;


			imgs = { src, src2 };
			Stitcher::Status status = stitcher->stitch(imgs, test);
			if (!test.empty()) {
				cv::resize(test, test2, Size(720, 480), 0, 0);
				break;
			}

			//writer.write(test);
			//imshow("result", test2);

			
		}
		else {
			cout << "didnt" << endl;
			break;
		}

	}
}
