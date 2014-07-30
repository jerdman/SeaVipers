#include "TrackerInterface.h"


TrackerInterface::TrackerInterface(void)
{
	threshold = 0.5; // quality required for target match
	use_small_frame = true; // for speedup
	resize_factor = 0.33;
	hist_norm = false;
	print_result = false; // posibly add text window later

	tld_tracker = new TLD();
}

void TrackerInterface::Initialize(Mat frame_in, Rect rect_in){
	// resize if necessary
	if(use_small_frame){
		resize(frame_in, frame, cv::Size(), resize_factor, resize_factor);
		cv::GaussianBlur(frame, tmp, cv::Size(0, 0), 15);
		swap(frame, tmp);
		bb = Rect(rect_in.x * resize_factor, rect_in.y * resize_factor, rect_in.width * resize_factor, rect_in.height * resize_factor);
	} else {
		frame = frame_in; 
		bb = Rect(rect_in);
	}

	// convert to grey
	grey = Mat(frame.rows, frame.cols, CV_8UC1);
	cvtColor(frame, grey, CV_RGB2GRAY);
	if(hist_norm){
		equalizeHist(grey, tmp);
		swap(grey, tmp);
	}

	// set parameters
	tld_tracker->detectorCascade->imgWidth = grey.cols;
	tld_tracker->detectorCascade->imgHeight = grey.rows;
	tld_tracker->detectorCascade->imgWidthStep = grey.step;

	// starting frame and bounding box
	tld_tracker->selectObject(grey, &bb); 
}

void TrackerInterface::ConsumeFrame(Mat input){
	// resize if necessary
	if(use_small_frame){
		resize(input, frame, cv::Size(), resize_factor, resize_factor);
		cv::GaussianBlur(frame, tmp, cv::Size(0, 0), 15);
		swap(frame, tmp);
	} else
		frame = input;

	cvtColor(frame, grey, CV_RGB2GRAY);
	if(hist_norm) {
		equalizeHist(grey, tmp);
		swap(grey, tmp);
	}

	tld_tracker->processImage(grey);

	// emit signal goes here
}

void TrackerInterface::toggleAlternating(void){
	tld_tracker->alternating = !tld_tracker->alternating;
}

void TrackerInterface::toggleBackground(void){
	ForegroundDetector *fg = tld_tracker->detectorCascade->foregroundDetector;
	if(fg->bgImg.empty())
		fg->bgImg = grey.clone();
	else
		fg->bgImg.release();
}

void TrackerInterface::toggleLearning(void){
	tld_tracker->learningEnabled = !tld_tracker->learningEnabled;
}

void TrackerInterface::clearTracker(void){
	tld_tracker->release();
}


TrackerInterface::~TrackerInterface(void){
	delete tld_tracker;
}
