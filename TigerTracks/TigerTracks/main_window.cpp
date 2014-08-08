#include "main_window.h"

main_window::main_window(QWidget *parent): QMainWindow(parent){
	ui.setupUi(this);
	
	// camera view
	camThread = new CameraThread();
	displayScene = new QGraphicsScene();
	connect(ui.playPushButton, SIGNAL(clicked()), this, SLOT(playVideo()));

	// tracker
	tracking = false;
	tracker = new TrackerInterface();
	connect(ui.trackPushButton, SIGNAL(clicked()), this, SLOT(trackButtonClicked()));
	
	qRegisterMetaType<cv::Mat>("cv::Mat");
	// connect camera output to tracker input
	connect(camThread, SIGNAL(readyMat(cv::Mat)), tracker, SLOT(consumeFrame(cv::Mat)));
	
	qRegisterMetaType<cv::Rect>("cv::Rect");
	// connect tracker output to UI input
	connect(tracker, SIGNAL(ready(cv::Mat, cv::Rect*)), this, SLOT(updateViewers(cv::Mat, cv::Rect*)));

	// for selecting bb with mouse. click & drag rectangle
	selector = new SelectorOverlay(ui.centralWidget);
	//connect(selector, SIGNAL(selectionReady(QRect)), this, SLOT(handleSelection(QRect)));
	selector->setGeometry(ui.cameraView->geometry());
	selector->setScene(displayScene);
	selector->show();
	
	// rangefinder
	rf = new RFInterface(this);
	connect(rf, SIGNAL(rangefinderError(QString)), this, SLOT(displayError(QString)));
	connect(rf, SIGNAL(distanceChanged(double)), ui.lcdRange, SLOT(display(double)));
	connect(ui.connectRFButton, SIGNAL(clicked()), this, SLOT(connectRangefinder()));
	connect(ui.rangePushButton, SIGNAL(clicked()), this, SLOT(toggleRangefinder()));

	// pan/tilt unit
	ptu = new PTUInterface(this);
	connect(ui.connectPTUButton, SIGNAL(clicked()), this, SLOT(connectPTU()));
	connect(ui.homePushButton, SIGNAL(clicked()), this, SLOT(ptuHome()));
	connect(ptu, SIGNAL(panChanged(double)), ui.lcdPan, SLOT(display(double)));
	connect(ptu, SIGNAL(tiltChanged(double)), ui.lcdTilt, SLOT(display(double)));
	this->stepSize = 1;

}

main_window::~main_window()
{
	delete camThread;
}

void main_window::keyPressEvent(QKeyEvent *k){
	if(k->key() == Qt::Key_W)
		stepUp();
	else if(k->key() == Qt::Key_S)
		stepDown();
	else if(k->key() == Qt::Key_A)
		stepLeft();
	else if(k->key() == Qt::Key_D)
		stepRight();
	else
		k->ignore(); // propogates event up to parent widget
}

void main_window::stepUp(void){
	ptu->tiltCommandRelative(stepSize);
}

void main_window::stepDown(void){
	ptu->tiltCommandRelative(-stepSize);
}

void main_window::stepLeft(void){
	ptu->panCommandRelative(stepSize);
}

void main_window::stepRight(void){
	ptu->panCommandRelative(-stepSize);
}

void main_window::updateViewers(cv::Mat m, cv::Rect* r){
	if(m.empty())
		return;
	
	QPainter* displayPainter;
	QImage displayImage;
	QPixmap displayPixmap;
	displayPixmapItem = displayScene->addPixmap(displayPixmap);

	if(m.channels() == 3){
		cv::cvtColor(m, m, cv::COLOR_BGR2RGB);
		displayImage = QImage((const unsigned char*)m.data, m.cols, m.rows, QImage::Format_RGB888);
	} else 
		displayImage = QImage((const unsigned char*)m.data, m.cols, m.rows, QImage::Format_Indexed8);
	displayPixmap = QPixmap::fromImage(displayImage);
	displayPainter = new QPainter(&displayPixmap);

	if(tracking){
		if(tracker->confident())
			displayPainter->setPen(Qt::blue);
		else
			displayPainter->setPen(Qt::yellow);
		displayPainter->drawRect(QRect(r->x, r->y, r->width, r->height));
	} else {
		displayPainter->setPen(Qt::green);
		displayPainter->drawRect(selector->getSelection());
	}
}

void main_window::playVideo(void){
	if(camThread->isStopped()){
		camThread->openCamera();
		camThread->playVideo();
		ui.playPushButton->setText("Pause");
	} else {
		camThread->stopVideo();
		ui.playPushButton->setText("Resume");
	}
}

void main_window::displayError(QString message){
	QMessageBox b(QMessageBox::Critical, "Error", message, QMessageBox::Close, this);
	b.show();
}

void main_window::connectRangefinder(void){
	rf->connectPort("COM7");
}

void main_window::toggleRangefinder(void){
	rf->toggleReporting();
}

void main_window::connectPTU(void){
	ptu->connectPort("COM6");
}

void main_window::ptuHome(void){
	ptu->homeCommand();
}

void main_window::toggleTracking(void){
	tracking = !tracking;
	if(tracking){
		cv::Rect r = cv::Rect(selector->getSelection().x(), selector->getSelection().y(), selector->getSelection().width(), selector->getSelection().height());
		tracker->Initialize(camThread->getCurrentMat(), r);
	} else
		tracker->clearTracker();
}

void main_window::trackButtonClicked(void){
	toggleTracking();
}