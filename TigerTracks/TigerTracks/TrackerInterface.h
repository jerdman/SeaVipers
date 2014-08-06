#pragma once

#include <opencv2\opencv.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <libopentld\tld\TLD.h>
#include <QImage>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>

using namespace tld;
using namespace cv;

class TrackerInterface : public QObject{
	Q_OBJECT

private:
	bool stopTrack;

	QMutex mutex;
	QWaitCondition condition;

	TLD *tld_tracker;
	Mat frame, grey, tmp;
	Rect bb;

	bool initialized;
	double threshold;
	bool use_small_frame;
	double resize_factor;
	bool hist_norm;
	bool print_result;

	double currConf;

signals:
	void ready(QRect rect);

public:
	TrackerInterface(void);
	~TrackerInterface(void);

	void Initialize(Mat frame_in, Rect rect_in);
	
	void startTracking(void);
	void stopTracking(void);

	void toggleBackground(void);
	void toggleLearning(void);
	void toggleAlternating(void);
	void clearTracker(void);
	bool confident(void);

	void consumeFrame(Mat input);

};

