#pragma once

#include <QObject>
#include <QList>
#include <QMediaPlaylist>

#include "BookmarkItem.h"
#include "InternetName.h"

//SINGLETON DATAMANAGER
class DataManager : public QObject
{
	Q_OBJECT

public:
	static DataManager* getInstance();
private:
	static DataManager* instance;

	DataManager(DataManager const&) = delete;
	void operator=(DataManager const&) = delete;
private:
	//BOOKMARKS
	QList<BookmarkItem> bookmark_items;
	//NETWORKING
	//QList<InternetName> internet_names;
	//LOCAL HOST IP
	//QHostAddress local_host_address;
	//POPUP CONFIGURATION
	QMap<QString, QVariant> popup_configuration_data;
	//MEDIA PLAYLIST
	QList<QString> playlist;
public:
	bool saveData(QString filename = "config.json", bool save_as_binary = true);
	bool loadData(QString filename = "config.json", bool load_as_binary = true);

	QList<QString> getPlaylist();
	void setPlaylist(QList<QString> playlist);

	double getVolume();
	void setVolume(double volume);

	QColor getBackgroundColor();
	QColor getDefaultBackgroundColor();
	void setBackgroundColor(QColor color);

	QColor getResizeBarColor();
	QColor getDefaultResizeBarColor();
	void setResizeBarColor(QColor color);

	QSize getPreferredBookmarkSize();
	void setPreferredBookmarkSize(QSize spacing);

	QSize getPreferredBookmarkImageSize();

	QSize getSpacingBetweenBookmarks();
	void setSpacingBetweenBookmarks(QSize size);

	QList<BookmarkItem>* getBookmarkItems();
	void removeBookmark(int index);
	const BookmarkItem* addBookmark(QString filename);
	//QList<InternetName>* getInternetNames();

	//bool registerInternetName(QString name);
	//void unregisterInternetName(QString name);
	//void addDetectedInternetName(QString name, QHostAddress host_address);
	//void removeAllDetectedInternetNames();
	//void unregisterAllRegisteredInternetNames();

	//QHostAddress getLocalhostAddress();
private:
	DataManager(QObject *parent = Q_NULLPTR);
	~DataManager();
};
