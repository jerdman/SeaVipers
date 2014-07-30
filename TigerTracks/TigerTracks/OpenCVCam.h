#pragma once
#include <QtGui/QImage>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class OpenCVCam{
	cv::VideoCapture vidcap;
	int camnum;

	// frame number
	int frame;

	cv::Mat inc, rgb;

	QImage current;
	bool connected;

public:
	// from Device
	void connect(void);
	void disconnect(void);

	// from CameraDevice
	void capture(void);

	// new members
	OpenCVCam(void);
	~OpenCVCam(void);

	void setCamNum(int num){
		camnum = num;
	}
	int getCamNum(void){
		return camnum;
	}
	QImage getCurrentImage(void){
		return current;
	}
	cv::Mat getCurrentMat(void){
		return inc;
	}
	bool isConnected(void){
		return connected;
	}
};

