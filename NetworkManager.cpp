/*
#include "NetworkManager.h"

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include <iostream>
using namespace std;

NetworkManager* NetworkManager::instance = NULL;

NetworkManager::NetworkManager(QObject *parent)
	: QObject(parent)
{
	//DETECTION INITIALZIATION
	{
		udp_transmitter = new QUdpSocket();
		udp_receiver = new QUdpSocket();

		refresh_timer = new QTimer();
		resend_timer = new QTimer();
	}
	//DATA MANAGER INITIALIZATION
	{
		data_manager = DataManager::getInstance();
	}
}

NetworkManager::~NetworkManager()
{
	if (instance != NULL)delete instance;
	delete udp_receiver;
	delete udp_transmitter;
	delete refresh_timer;
	delete resend_timer;
}

void NetworkManager::startScanning()
{
	udp_receiver->bind(56712, QUdpSocket::ShareAddress);

	QObject::connect(udp_receiver, &QUdpSocket::readyRead, [=]() {
		QByteArray datagram;
		datagram.resize(udp_receiver->pendingDatagramSize());
		
		QHostAddress recv_address;
		udp_receiver->readDatagram(datagram.data(), datagram.size(), &recv_address);

		QJsonDocument recv_document(QJsonDocument::fromBinaryData(datagram));

		if (recv_address.toIPv4Address() != data_manager->getLocalhostAddress().toIPv4Address()) {
			if (recv_document.isArray()) {
				QJsonArray internet_names = recv_document.array();
				for (int i = 0; i < internet_names.size(); i++) {
					if (internet_names[i].isString()) {
						data_manager->addDetectedInternetName(internet_names[i].toString(), recv_address);
					}
				}
			}
		}
	});

	QObject::connect(resend_timer, &QTimer::timeout, [=]() {
		QJsonArray internet_names_array;
		QList<BookmarkItem>* bookmark_items = data_manager->getBookmarkItems();
		for (int i = 0; i < bookmark_items->size(); i++) {
			if ((*bookmark_items)[i].getInternetName() != "") {
				internet_names_array.push_back((*bookmark_items)[i].getInternetName());
				break;
			}
		}
		QJsonDocument send_document(internet_names_array);

		QByteArray data = send_document.toBinaryData();
		udp_transmitter->writeDatagram(data, data.size(), QHostAddress::Broadcast, 56712);
	});
	resend_timer->start(500);

	QObject::connect(refresh_timer, &QTimer::timeout, [=]() {
		data_manager->removeAllDetectedInternetNames();
	});
	refresh_timer->start(10000);
}

NetworkManager* NetworkManager::getInstance() {
	if (NetworkManager::instance == NULL)NetworkManager::instance = new NetworkManager();
	return instance;
}

*/