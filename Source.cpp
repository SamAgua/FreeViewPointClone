#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;
int main(int, char**)
{
	//Writing video files
	Mat src;
	// use default camera as video source
	VideoCapture cap(0);
	// check if we succeeded
	if (!cap.isOpened()) {
		cerr << "ERROR! Unable to open camera\n";
		return -1;
	}
	// get one frame from camera to know frame size and type
	cap >> src;
	// check if we succeeded
	if (src.empty()) {
		cerr << "ERROR! blank frame grabbed\n";
		return -1;
	}
	bool isColor = (src.type() == CV_8UC3);
	//--- INITIALIZE VIDEOWRITER
	VideoWriter writer;
	int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');  // select desired codec (must be available at runtime)
	double fps = 25.0;                          // framerate of the created video stream
	string filename = "./live.avi";             // name of the output video file
	writer.open(filename, codec, fps, src.size(), isColor);
	// check if we succeeded
	if (!writer.isOpened()) {
		cerr << "Could not open the output video file for write\n";
		return -1;
	}
	//--- GRAB AND WRITE LOOP
	cout << "Writing videofile: " << filename << endl
		<< "Press any key to terminate" << endl;
	for (;;)
	{
		// check if we succeeded
		if (!cap.read(src)) {
			cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		// encode the frame into the videofile stream
		writer.write(src);
		// show live and wait for a key with timeout long enough to show images
		imshow("Live", src);
		if (waitKey(5) >= 0)
			break;
	}

	int i = waitKey(5);
	


	//Reading video files
	//Reuses src
	VideoCapture cap1("./live.avi");

	// Check if camera opened successfully
	if (!cap1.isOpened()) {
		cout << "Error opening video stream or file" << endl;
		return -1;
	}

	for (;;) {

		// Capture frame-by-frame
		cap1 >> src;

		// If the frame is empty, break immediately
		if (src.empty())
			break;

		// Display the resulting frame
		imshow("Frame", src);

		// Press  ESC on keyboard to exit
		char c = (char)waitKey(25);

		if (c == 27)
			break;
	}
	// the videofile will be closed and released automatically in VideoWriter destructor

	return 0;
}