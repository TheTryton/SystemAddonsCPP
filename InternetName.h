#pragma once

#include <QHostAddress>

class InternetName
{
	friend class DataManager;
private:
	void operator=(InternetName const&) = delete;
public:
	//NETWORKING
	QString getInternetName();
	QList<QHostAddress>* getIPAddressesList();
private:
	QList<QHostAddress> ip_addresses;
	QString internet_name;
private:
	InternetName();
public:
	~InternetName();
};

