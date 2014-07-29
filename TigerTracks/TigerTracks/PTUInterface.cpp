#include "PTUInterface.h"

PTUInterface::PTUInterface(QObject *parent): QObject(parent)
{
	port = new QSerialPort(this);
	this->setPan(0);
	this->setTilt(0);
}

PTUInterface::~PTUInterface(void)
{
	disconnectPort();
}

void PTUInterface::connectPort(QString name){
	if(!port->isOpen()){
		// connect signals to slots
		connect(port, SIGNAL(readyRead()), SLOT(handleReadyRead()));
		connect(port, SIGNAL(error(QSerialPort::SerialPortError)), SLOT(handleError(QSerialPort::SerialPortError)));

		// set properties
		port->setPortName(name);
		port->open(QIODevice::ReadWrite);
		port->setBaudRate(QSerialPort::Baud9600);
		port->setDataBits(QSerialPort::Data8);
		port->setParity(QSerialPort::NoParity);
		port->setStopBits(QSerialPort::OneStop);
		port->setFlowControl(QSerialPort::NoFlowControl);
	}
}

void PTUInterface::disconnectPort(void){
	port->close();
}

bool PTUInterface::isConnected(void){
	return port->isOpen();
}

void PTUInterface::handleReadyRead(void){
	QList<QByteArray> list = port->readAll().split('&');
	for(int i = 0; i < list.size(); i++){
		parseResponse(list.at(i));
	}
}

void PTUInterface::handleError(QSerialPort::SerialPortError error){
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
	emit ptuError(tr("%1 on %2, %3").arg(s, port->portName(), port->errorString()));

}

void PTUInterface::panCommandAbsolute(int pan){
	int n = (pan - 1.0) * 65535.0 / 358.0; // remap from [1, 359] to [0, 65535]
	sendCommand(tr("G1L%1").arg(QString(n)));
}

void PTUInterface::tiltCommandAbsolute(int tilt){
	int n = (tilt - 90.0) * 65535.0 / 180.0; // remap to [90, 270] from [0, 65535]
	sendCommand(tr("G2L%1").arg(QString(n)));
}

void PTUInterface::panCommandRelative(int pan){
	this->panCommandAbsolute(pan + this->pan);
}

void PTUInterface::tiltCommandRelative(int tilt){
	this->tiltCommandAbsolute(tilt + this->tilt);
}

void PTUInterface::homeCommand(void){
	sendCommand("HOME");
}

void PTUInterface::sendCommand(QString str){
	char buff[32];
	int i, j, l, sum;
	buff[0] = '*';
	buff[1] = 5;
	buff[2] = 0;
	buff[3] = l = str.length();
	sum = buff[0] + buff[1] + buff[3];
	i = 0;
	j = 4;
	while(i < l && j < 31){
		buff[j] = str.at(i).toLatin1();
		sum += buff[j];
		i++;
		j++;
	}
	buff[j] = sum % 256; // checksum
	port->write(buff, j + 1);
}


void PTUInterface::parseResponse(QByteArray barr){
	if(barr.size() < 1)
		return;

	int n;
	double m;
	switch(barr[0]){
	case 8: // change level word
		if(barr.size() < 6)
			break;
		n = barr.at(3) * 256 + barr.at(4);
		if(barr.at(2) == 5){ // pan
			m = 1.0 + n * 358.0 / 65535.0; // remap to [1, 359] from [0, 65535]
			setPan(m);
		} else if(barr.at(2) == 6){ // tilt
			m = 90.0 + n * 180.0 / 65535.0; // remap to [90, 270] from [0, 65535]
			setTilt(m);
		}
		break;
	case 2: // change level byte
		if(barr.size() < 5)
			break;
		n = barr.at(3);
		if(barr.at(2) == 0){ // pan
			m = 1.0 + n * 358.0 / 256.0; // remap to [1, 359] from [0, 256]
			setPan(m);
		} else if(barr.at(2) == 1){ // tilt
			m = 90.0 + n * 180.0 / 256.0; // remap to [90, 270] from [0, 256]
			setTilt(m);
		}
		break;
	default:
		// do nothing, for now
		break;
	}
}

void PTUInterface::setPan(double pan){
	if(this->pan != pan){
		this->pan = pan;
		emit panChanged(pan);
	}
}

void PTUInterface::setTilt(double tilt){
	if(this->tilt != tilt){
		this->tilt = tilt;
		emit tiltChanged(tilt);
	}
}