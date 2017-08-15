#pragma once

#include <QMap>
#include <QVariant>
#include <QSize>
#include <QImage>

class BookmarkItem
{
	friend class DataManager;
private:
	void operator=(BookmarkItem const&) = delete;
public:
	//NETWORKING
	QString getInternetName();
	void setInternetName(QString name);

	bool getSynchronizeOverInternet();
	void setSynchronizeOverInternet(bool synchronize);

	//DISPLAY
	QString getVisibleName();
	void setVisibleName(QString name);

	QString getVisibleImageFilename();
	void setVisibleImageFilename(QString filename, QSize preferred_size = QSize(0,0));

	void setVisibleImageAsDefaultFileIcon(QSize preferred_size = QSize(0, 0));

	const QImage* getVisibleImage();

	//LINKING
	QString getLocalFilename();
private:
	QImage visible_image;
	QMap<QString,QVariant> data;
private:
	BookmarkItem();
public:
	~BookmarkItem();
};

