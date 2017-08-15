#include "InternetName.h"



InternetName::InternetName()
{
}


InternetName::~InternetName()
{
}

QString InternetName::getInternetName()
{
	return internet_name;
}

QList<QHostAddress>* InternetName::getIPAddressesList()
{
	return &ip_addresses;
}
