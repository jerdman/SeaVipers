#pragma once

#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <libopentld\tld\TLD.h>
#include <QTimer>

using namespace tld;
using namespace cv;

class TrackerInterface : public QObject{
	Q_OBJECT

	TLD *tld_tracker;
	Mat frame, grey, tmp;
	Rect bb;

	double threshold;
	bool use_small_frame;
	double resize_factor;
	bool hist_norm;
	bool print_result;

public:
	TrackerInterface(void);
	~TrackerInterface(void);
	void Initialize(Mat frame_in, Rect rect_in);
	void ConsumeFrame(Mat input);
	void toggleBackground(void);
	void toggleLearning(void);
	void toggleAlternating(void);
	void clearTracker(void);


};

