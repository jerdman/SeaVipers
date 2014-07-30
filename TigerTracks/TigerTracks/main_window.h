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
#include <iostream>

class main_window : public QMainWindow
{
	Q_OBJECT

private:
	Ui::main_windowClass ui;
	CameraThread* camThread;
	QPoint origin;
	QGraphicsScene* scene;
	SelectorOverlay* selector;
	QRect displayRect;
	RFInterface* rf;
	PTUInterface* ptu;
	QGraphicsPixmapItem* pmi;
	QPixmap pm;
	QPainter* pnt;
	int stepSize;


public:
	main_window(QWidget *parent = 0);
	~main_window();
	void keyPressEvent(QKeyEvent *k);
	void stepUp(void);
	void stepDown(void);
	void stepLeft(void);
	void stepRight(void);

private slots:
	void updatecamThreadUI(QImage img);
	void playVideo(void);
	void handleSelection(QRect rect);
	void displayError(QString message);
	void connectRangefinder(void);
	void toggleRangefinder(void);
	void connectPTU(void);
	void ptuHome(void);
	void toggleTracking(void);
};

#endif // MAIN_WINDOW_H
