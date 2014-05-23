#pragma once

#include <QtSerialPort/QSerialPort>


class RFInterface : public QObject{
	
	Q_OBJECT

private:
	double distance;
	QSerialPort *port;
	bool isReporting;

signals:
	void distanceChanged(double distance);
	void rangefinderError(QString summary);
	void statusMessage(QString message);

public slots:
	void handleReadyRead(void);
	void handleError(QSerialPort::SerialPortError error);

public:
	RFInterface(QObject *parent = 0);
	~RFInterface(void);

	void connectPort(QString name);
	void disconnectPort(void);
	bool isConnected(void);

	void startReporting(void);
	void stopReporting(void);
	void checkStatus(void);
	void toggleReporting(void);
};

