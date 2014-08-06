#include "main_window.h"

main_window::main_window(QWidget *parent): QMainWindow(parent){
	ui.setupUi(this);
	
	// camera view
	camThread = new CameraThread();
	camScene = new QGraphicsScene();
	pmiCam = camScene->addPixmap(pmCam);
	connect(ui.playPushButton, SIGNAL(clicked()), this, SLOT(playVideo()));

	// tracker
	tracking = false;
	tracker = new TrackerInterface();
	connect(ui.trackPushButton, SIGNAL(clicked()), this, SLOT(trackButtonClicked()));
	trackScene = new QGraphicsScene();
	pmiTrack = trackScene->addPixmap(pmTrack);
	

	// for selecting bb with mouse. click & drag rectangle
	selector = new SelectorOverlay(ui.centralWidget);
	connect(selector, SIGNAL(selectionReady(QRect)), this, SLOT(handleSelection(QRect)));
	selector->setGeometry(ui.cameraView->geometry());
	selector->setScene(camScene);
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

void main_window::updateViewers(void){
	/*if(img.isNull())
		return;

	QPixmap pix = QPixmap::fromImage(img);		
	pnt = new QPainter(&pix);
	if(tracking){
		displayRect = tracker->consumeFrame(mat);
		if(tracker->confident())
			pnt->setPen(Qt::blue);
		else
			pnt->setPen(Qt::yellow);
	} else 
		pnt->setPen(Qt::green);

	pnt->drawRect(displayRect);
	pmi->setPixmap(pix);*/

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

void main_window::handleSelection(QRect rect){
	// do something?
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