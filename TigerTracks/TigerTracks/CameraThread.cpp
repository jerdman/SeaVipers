#include "CameraThread.h"


CameraThread::CameraThread(QObject *parent) : QThread(parent)
{
	stop = true;
	camera.setCamNum(1);
}

CameraThread::~CameraThread(void)
{
	mutex.lock();
	stop = true;
	camera.disconnect();
	condition.wakeOne();
	mutex.unlock();
	wait();
}

void CameraThread::run(void){
	while(!stop){
		if(!camera.isConnected()){
			stop = true;
			break;
		}
		camera.capture();
		emit readyMat(camera.getCurrentMat());
		emit readyImg(camera.getCurrentImage());
		// 33 milliseconds = 1/30 seconds
		// 111 milliseconds = 1/9 seconds
		msleep(111);  
	}
}

bool CameraThread::openCamera(void){
	camera.connect();
	return camera.isConnected();
}

void CameraThread::playVideo(void){
	if(!isRunning()){
		if(isStopped())
			stop = false;
		start(LowPriority);
	}
}

void CameraThread::stopVideo(void){
	stop = true;
}

bool CameraThread::isStopped(void) const{
	return this->stop;
}

cv::Mat CameraThread::getCurrentMat(void){
	return this->camera.getCurrentMat();
}