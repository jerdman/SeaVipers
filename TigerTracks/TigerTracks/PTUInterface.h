#pragma once

#include <QtSerialPort/QSerialPort>

class PTUInterface : public QObject{

		Q_OBJECT
private:
	double pan, tilt;
	QSerialPort *port;

signals:
	void panChanged(double p);
	void tiltChanged(double t);
	void ptuError(QString summary);
	void ptuMessage(QString message);

public slots:
	void handleReadyRead(void);
	void handleError(QSerialPort::SerialPortError error);

public:
	PTUInterface(QObject *parent = 0);
	~PTUInterface(void);

	void connectPort(QString name);
	void disconnectPort(void);
	bool isConnected(void);

	void panCommandAbsolute(int pan);
	void tiltCommandAbsolute(int tilt);
	void panCommandRelative(int pan);
	void tiltCommandRelative(int tilt);

	void homeCommand(void);


private:
	void sendCommand(QString command);
	void parseResponse(QByteArray barr);
	void setPan(double pan);
	void setTilt(double tilt);
};

