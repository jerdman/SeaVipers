#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QTimer>
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
	QPixmap pm;
	QPainter* pnt;

public:
	main_window(QWidget *parent = 0);
	~main_window();

private slots:
	void updatecamThreadUI(QImage img);
	void playVideo(void);
	void handleSelection(QRect rect);
	void displayError(QString message);
	void connectRangefinder(void);
	void toggleRangefinder(void);
	void connectPTU(void);
	void ptuDemo(void);
	void ptuHome(void);
};

#endif // MAIN_WINDOW_H
