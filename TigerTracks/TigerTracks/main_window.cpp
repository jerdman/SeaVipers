#include "main_window.h"

main_window::main_window(QWidget *parent): QMainWindow(parent){
	ui.setupUi(this);
	
	// camera view
	camThread = new CameraThread();
	scene = new QGraphicsScene();
	pmi = scene->addPixmap(pm);
	connect(camThread, SIGNAL(imageReady(QImage)), this, SLOT(updatecamThreadUI(QImage)));
	connect(ui.playPushButton, SIGNAL(clicked()), this, SLOT(playVideo()));
	

	// for selecting bb with mouse. click & drag rectangle
	displayRect = QRect(0, 0, 0, 0);
	selector = new SelectorOverlay(ui.centralWidget);
	connect(selector, SIGNAL(selectionReady(QRect)), this, SLOT(handleSelection(QRect)));
	selector->setGeometry(10, 10, 640, 480);
	selector->setScene(scene);
	selector->show();
	
	// rangefinder
	rf = new RFInterface(this);
	connect(rf, SIGNAL(rangefinderError(QString)), this, SLOT(displayMessage(QString)));
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

void main_window::updatecamThreadUI(QImage img){
	if(!img.isNull()){
		QPixmap pix = QPixmap::fromImage(img);		
		if(displayRect.width() > 0 && displayRect.height() > 0){
			pnt = new QPainter(&pix);
			pnt->setPen(Qt::blue);
			pnt->drawRect(displayRect);
		}
		pmi->setPixmap(pix);
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

void main_window::handleSelection(QRect rect){
	displayRect = QRect(rect);
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

