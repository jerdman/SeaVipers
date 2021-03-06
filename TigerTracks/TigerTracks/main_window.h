#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include "ui_main_window.h"

#include "CameraThread.h"
#include "SelectorOverlay.h"
#include "RFInterface.h"
#include "PTUInterface.h"
#include "TrackerInterface.h"
#include <iostream>

class main_window : public QMainWindow
{
	Q_OBJECT

private:
	Ui::main_windowClass ui;
	CameraThread* camThread;
	SelectorOverlay* selector;
	RFInterface* rf;
	PTUInterface* ptu;

	int stepSize;
	bool tracking;
	TrackerInterface* tracker;

	QGraphicsPixmapItem* displayPixmapItem;
	QGraphicsScene* displayScene;





public:
	main_window(QWidget *parent = 0);
	~main_window();
	void keyPressEvent(QKeyEvent *k);
	void stepUp(void);
	void stepDown(void);
	void stepLeft(void);
	void stepRight(void);
	void toggleTracking(void);

private slots:
	void updateViewers(cv::Mat m, cv::Rect* r);
	void playVideo(void);
	void displayError(QString message);
	void connectRangefinder(void);
	void toggleRangefinder(void);
	void connectPTU(void);
	void ptuHome(void);
	void trackButtonClicked(void);
};

#endif // MAIN_WINDOW_H
