// Justin Erdman 2013
// adapted from:
// http://codingexodus.blogspot.com/2012/12/working-with-video-using-opencv-and-qt.html

#pragma once

#include <QtCore/QMutex>
#include <QtCore/QThread>
#include <QtCore/QWaitCondition>
#include <QtGui/QImage>

#include "OpenCVCam.h"

class CameraThread : public QThread
{
	Q_OBJECT

private:
	bool stop;
	int frameRate;

	QMutex mutex;
	QWaitCondition condition;

	OpenCVCam camera;

signals:
	void imageReady(const QImage &image);
	void matReady(cv::Mat mat);

protected:
	void run(void);

public:
	CameraThread(QObject *parent = 0);
	~CameraThread(void);

	bool openCamera(void);
	void playVideo(void);
	void stopVideo(void);
	bool isStopped(void) const;
};

