#include "RFInterface.h"

RFInterface::RFInterface(QObject *parent): QObject(parent)	
{
	port = new QSerialPort(this);
	isReporting = false;
}

RFInterface::~RFInterface(void){
	disconnectPort();
}

void RFInterface::connectPort(QString name){
	if(!port->isOpen()){
		// connect signals to slots
		connect(port, SIGNAL(readyRead()), SLOT(handleReadyRead()));
		connect(port, SIGNAL(error(QSerialPort::SerialPortError)), 
			SLOT(handleError(QSerialPort::SerialPortError)));

		// set port properties
		port->setPortName(name);
		port->open(QIODevice::ReadWrite);
		port->setBaudRate(QSerialPort::Baud19200);
		port->setDataBits(QSerialPort::Data8);
		port->setParity(QSerialPort::NoParity);
		port->setStopBits(QSerialPort::OneStop);
		port->setFlowControl(QSerialPort::NoFlowControl);

		// set averaged mode to report in meters
		port->write("M\r"); 
	}
}

void RFInterface::disconnectPort(void){
	if(port->isOpen())
		stopReporting();
	port->close();
}

bool RFInterface::isConnected(void){
	return port->isOpen();
}

void RFInterface::handleReadyRead(void){
	QString response(port->readLine());
	if(response.startsWith("DIST:")){
		// "DIST:XXXX.YYU"
		double d = response.midRef(5, 7).toDouble();
		if(this->distance != d){
			this->distance = d;
			emit distanceChanged(this->distance);
		}
	} else if(response.startsWith("COUNTS:")){
		// "COUNTS:XXXX"
		double d = response.midRef(7, 4).toDouble();
		if(this->distance != d){
			this->distance = d;
			emit distanceChanged(this->distance);
		}
	} else {
		// probably a status message
		response += port->readAll();
		emit statusMessage(response);
	}
}

void RFInterface::handleError(QSerialPort::SerialPortError error){
	QString s;
	switch(error){
	case QSerialPort::ReadError:
		s = "Serial Read Error";
		break;
	case QSerialPort::WriteError:
		s = "Serial Write Error";
		break;
	case QSerialPort::DeviceNotFoundError:
		s = "Device not found";
		break;
	default:
		s = "Unexpected error";
	}
	emit rangefinderError(tr("%1 on %2, %3").arg(s, port->portName(), port->errorString()));
}

void RFInterface::startReporting(void){
	if(port->isOpen()){
		//port->write("R\r"); // start continuous Average ranged mode, 10 Hz
		port->write("H\r"); // start continuous counts mode, 200 Hz
		isReporting = true;
	}
}

void RFInterface::stopReporting(void){
	if(port->isOpen()){
		port->write("O\r"); // stop continuous reporting
		isReporting = false;
	}
}

void RFInterface::checkStatus(void){
	if(port->isOpen())
		port->write("B\r"); // get status message
}

void RFInterface::toggleReporting(void){
	if(isReporting)
		stopReporting();
	else
		startReporting();
}