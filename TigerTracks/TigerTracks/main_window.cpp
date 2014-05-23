#include "main_window.h"

main_window::main_window(QWidget *parent)
	: QMainWindow(parent)
{
	camThread = new CameraThread();
	scene = new QGraphicsScene();
	connect(camThread, SIGNAL(imageReady(QImage)), this, SLOT(updatecamThreadUI(QImage)));
	
	ui.setupUi(this);
	connect(ui.playPushButton, SIGNAL(clicked()), this, SLOT(playVideo()));

	selector = new SelectorOverlay(ui.centralWidget);
	connect(selector, SIGNAL(selectionReady(QRect)), this, SLOT(handleSelection(QRect)));
	selector->setGeometry(10, 10, 640, 480);
	selector->setScene(scene);
	selector->show();

	displayRect = QRect(0, 0, 0, 0);
	
	rf = new RFInterface(this);
	connect(rf, SIGNAL(rangefinderError(QString)), this, SLOT(displayMessage(QString)));
	connect(rf, SIGNAL(distanceChanged(double)), ui.lcdRange, SLOT(display(double)));
	connect(ui.connectRFButton, SIGNAL(clicked()), this, SLOT(connectRangefinder()));
	connect(ui.rangePushButton, SIGNAL(clicked()), this, SLOT(toggleRangefinder()));

	ptu = new PTUInterface(this);
	connect(ui.connectPTUButton, SIGNAL(clicked()), this, SLOT(connectPTU()));
	connect(ui.demoPushButton, SIGNAL(clicked()), this, SLOT(ptuDemo()));
	connect(ui.homePushButton, SIGNAL(clicked()), this, SLOT(ptuHome()));
	connect(ptu, SIGNAL(panChanged(double)), ui.lcdPan, SLOT(display(double)));
	connect(ptu, SIGNAL(tiltChanged(double)), ui.lcdTilt, SLOT(display(double)));
	

}

main_window::~main_window()
{
	delete camThread;
}

void main_window::updatecamThreadUI(QImage img){
	if(!img.isNull()){
		pm = QPixmap::fromImage(img);
		// if selection area is greater than 100 px, draw it
		if((displayRect.width() * displayRect.height()) >= 100){
			//QPainter pnt(&pm);
			pnt = new QPainter(&pm);
			pnt->setPen(Qt::blue);
			pnt->drawRect(displayRect);
		}
		scene->addPixmap(pm);
	}
}

void main_window::playVideo(void){
	if(camThread->isStopped()){
		camThread->openCamera();
		camThread->playVideo();
		ui.playPushButton->setText("Stop");
	} else {
		camThread->stopVideo();
		ui.playPushButton->setText("Play");
	}
}

void main_window::handleSelection(QRect rect){
	displayRect = rect;
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

void main_window::ptuDemo(void){
	ptu->panCommandAbsolute(0);
	ptu->tiltCommandAbsolute(0);
}

void main_window::ptuHome(void){
	ptu->homeCommand();
}

