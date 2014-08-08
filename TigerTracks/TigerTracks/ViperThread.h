#pragma once
#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <QImage>
#include <highgui\highgui.hpp>
#include <imgproc\imgproc.hpp>
#include <libopentld\tld\TLD.h>

class ViperThread : public QThread {
	Q_OBJECT

private:
	bool stop;
	QMutex mutex;
	QWaitCondition wcondition;

	cv::VideoCapture vidcap;
	int frame;
	cv::Mat input, grey, tmp;
	cv::Rect bb;

	bool tracking;
	tld::TLD tracker;
	bool initialized;
	double threshold;
	//bool use_small_frame;
	//double resize_factor;
	//bool hist_norm;
	//bool print_result;

	QImage img;
	QRect rect;

signals:
	void ready(QImage img, QRect rect);

public:
	ViperThread(QObject *parent = 0);
	~ViperThread(void);

	void initializeTracker();
	void toggleTracker(void);
	void processImage(void);
	void setBB(const QRect &bb);

	void connectCamera(int cam);
	void disconnectCamera(void);
	void captureImage(void);
	void startCamera(void);
	void stopCamera(void);
	void convertOutput(void);

protected:
	void run(void);
};

