#pragma once
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>  // cv::Canny()
#include <iostream>
#include <vector>
#include <thread>
#include <QtWidgets/QWidget>
#include "ui_QtGuiApplication1.h"
using namespace cv;
using std::cout; using std::cerr; using std::endl; using std::vector;
using namespace std;
class QtGuiApplication1 : public QWidget
{
	Q_OBJECT
	 public:
		void singleDisplay(VideoCapture capture, Mat frame);
		explicit QtGuiApplication1(QWidget *parent = 0);
	 private slots:
		void handleButton();
	 private:
		QPushButton *m_button;
	};
