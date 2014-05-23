#include "OpenCVCam.h"


OpenCVCam::OpenCVCam(void)
{
	camnum = 0;
	connected = false;
	frame = 0;
}

OpenCVCam::~OpenCVCam(void){
	if(connected)
		disconnect();
}

void OpenCVCam::connect(void){
	vidcap.open(camnum);
	if(vidcap.isOpened()){
		vidcap >> inc;
		vidcap >> inc;
		vidcap >> inc;
		vidcap >> inc;
		connected = true;
		frame = 0;
	} else
		connected = false;
}

void OpenCVCam::disconnect(void){
	vidcap.release();
	connected = false;
}

void OpenCVCam::capture(void){
	vidcap.read(inc);
	if(inc.channels() == 3)
	{
		cv::cvtColor(inc, rgb, cv::COLOR_BGR2RGB);
		current = QImage((const unsigned char*)rgb.data, rgb.cols, rgb.rows, QImage::Format_RGB888); 
	} else
		current = QImage((const unsigned char*)inc.data, inc.cols, inc.rows, QImage::Format_Indexed8);
	frame++;
}

QImage OpenCVCam::advance(void){
	capture();
	return current;
}
