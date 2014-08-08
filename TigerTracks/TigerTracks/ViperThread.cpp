#include "ViperThread.h"


ViperThread::ViperThread(QObject *parent) : QThread(parent){
	stop = true;
	frame = 0;

	threshold = 0.5;

	tracker = tld::TLD();
	initialized = false;
	tracking = false;
}


ViperThread::~ViperThread(void){
	mutex.lock();
	stop = true;
	initialized = false;
	tracking = false;
	disconnectCamera();
	tracker.release();
	wcondition.wakeOne();
	mutex.unlock();
	wait();
}

void ViperThread::connectCamera(int cam){
	vidcap.open(cam);
	if(vidcap.isOpened()){
		vidcap >> input;
		vidcap >> input;
		vidcap >> input;
		vidcap >> input;
	}
}

void ViperThread::disconnectCamera(void){
	vidcap.release();
}

void ViperThread::captureImage(void){
	vidcap.read(input);
	frame++;
}

void ViperThread::run(void){
	while(!stop){
		if(!vidcap.isOpened()){
			stop = true;
			break;
		}
		captureImage();
		processImage();
		emit ready(img, rect);
	}

}

void ViperThread::startCamera(void){
	if(!isRunning()){
		if(stop)
			stop = false;
		start(LowPriority);
	}
}

void ViperThread::stopCamera(void){
	stop = true;
}

void ViperThread::initializeTracker(){
	cvtColor(input, grey, CV_BGR2GRAY);
	tracker.detectorCascade->imgWidth = grey.cols;
	tracker.detectorCascade->imgHeight = grey.rows;
	tracker.detectorCascade->imgWidthStep = grey.step;
	tracker.selectObject(grey, &bb);
	initialized = true;
}

void ViperThread::setBB(const QRect &bb){
	if(!initialized)
		this->bb = cv::Rect(bb.x(), bb.y(), bb.width(), bb.height());
}

void ViperThread::processImage(void){
	if(!tracking) 
		return;
	cvtColor(input, grey, CV_BGR2GRAY);
	tracker.processImage(grey);
}

void ViperThread::convertOutput(void){
	cvtColor(input, tmp, CV_BGR2RGB);
	img = QImage((const unsigned char*)tmp.data, tmp.cols, tmp.rows, QImage::Format_RGB888);
	rect = QRect(tracker.currBB->x, tracker.currBB->y, tracker.currBB->width, tracker.currBB->height);
}

void ViperThread::toggleTracker(void){
	tracking = !tracking;
}