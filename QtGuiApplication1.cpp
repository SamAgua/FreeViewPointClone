#include "QtGuiApplication1.h"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>  // cv::Canny()
#include <iostream>
#include <vector>
#include <thread>

using namespace cv;
using std::cout; using std::cerr; using std::endl; using std::vector;
using namespace std;
VideoCapture capture1(0);
Mat frame1;
bool pause = false;


QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QWidget(parent)
{
	// Create the button, make "this" the parent
	m_button = new QPushButton("Cam1", this);
	// set size and location of the button
	m_button->setGeometry(QRect(QPoint(100, 100),
		QSize(200, 50)));

	// Connect button signal to appropriate slot
	connect(m_button, SIGNAL(released()), this, SLOT(handleButton()));
}

void QtGuiApplication1::singleDisplay(VideoCapture capture, Mat frame) {
		pause = false;
		while (!pause) {
			if (capture.isOpened()) { //avoid reading from an unopened device

				capture >> frame;
				imshow("Camera Feed", frame); //Display Frame
			}
			else {
				break; // If no camera, breaks from method
			}
			int keypress = waitKey(1); //saving the pressed key
			if (keypress == 27) {//if pressed Esc key breaks from method
				pause = false;
				break;
			}
			if (keypress == 32) {//if Spacebar
				pause = true;
				break;
			}
		}
	}


void QtGuiApplication1::handleButton()
{
	singleDisplay(capture1, frame1);
}

