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
	// int delay = (1000/frameRate);
	while(!stop){
		if(!camera.isConnected()){
			stop = true;
			break;
		}
		emit imageReady(camera.advance());
		msleep(10); // 33 milliseconds = 1/30 seconds 
		// use delay for msleep?
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