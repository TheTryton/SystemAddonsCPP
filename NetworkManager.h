#pragma once

/*
#include <QUdpSocket>
#include <QTimer>
#include <QHostAddress>

#include "DataManager.h"

class NetworkManager : public QObject
{
	Q_OBJECT

public:
	static NetworkManager* getInstance();
private:
	static NetworkManager* instance;

	NetworkManager(NetworkManager const&) = delete;
	void operator=(NetworkManager const&) = delete;
private:
	//DETECTION
	QUdpSocket* udp_transmitter;
	QUdpSocket* udp_receiver;
	QTimer* refresh_timer;
	QTimer* resend_timer;
	//DATA MANAGER POINTER
	DataManager* data_manager;
public:
	void startScanning();
private:
	NetworkManager(QObject *parent = Q_NULLPTR);
	~NetworkManager();
};

*/