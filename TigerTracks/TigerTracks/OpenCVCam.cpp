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
	frame++;
}

