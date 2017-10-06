#include "BookmarkItem.h"

#include <QFileInfo>
#include <QFileIconProvider>

BookmarkItem::BookmarkItem()
{
	data["internet_name"] = "";
	data["synchronize_over_internet"] = false;

	data["visible_name"] = "";
	data["local_file_name"] = "";
	data["visible_image_file_name"] = "";
}

BookmarkItem::~BookmarkItem()
{
}

/*
QString BookmarkItem::getInternetName()
{
	return data["internet_name"].toString();
}

void BookmarkItem::setInternetName(QString name)
{
	data["internet_name"] = name;
}

bool BookmarkItem::getSynchronizeOverInternet()
{
	return data["synchronize_over_internet"].toBool();
}

void BookmarkItem::setSynchronizeOverInternet(bool synchronize)
{
	data["synchronize_over_internet"] = synchronize;
}*/

QString BookmarkItem::getVisibleName()
{
	return data["visible_name"].toString();
}

void BookmarkItem::setVisibleName(QString name)
{
	data["visible_name"] = name;
}

QString BookmarkItem::getVisibleImageFilename()
{
	return data["visible_image_file_name"].toString();
}

void BookmarkItem::setVisibleImageFilename(QString filename, QSize preferred_size)
{
	QFileInfo image_file;
	image_file.setFile(filename);
	if (image_file.exists()) {
		this->visible_image = QImage(filename);
		if (preferred_size.width() > 0 && preferred_size.height() > 0) {
			this->visible_image = this->visible_image.scaledToHeight(preferred_size.height(), Qt::TransformationMode::SmoothTransformation);
			if (this->visible_image.width() > preferred_size.width())this->visible_image = this->visible_image.scaledToWidth(preferred_size.width(), Qt::TransformationMode::SmoothTransformation);
		}
		data["visible_image_file_name"] = filename;
	}
}

void BookmarkItem::setVisibleImageAsDefaultFileIcon(QSize preferred_size)
{
	QFileIconProvider file_icon;
	QIcon ico = file_icon.icon(QFileInfo(data["local_file_name"].toString()));
	this->visible_image = ico.pixmap(128, 128).toImage();
	if (preferred_size.width() > 0 && preferred_size.height() > 0) {
		this->visible_image = this->visible_image.scaledToHeight(preferred_size.height(), Qt::TransformationMode::SmoothTransformation);
		if (this->visible_image.width() > preferred_size.width())this->visible_image = this->visible_image.scaledToWidth(preferred_size.width(), Qt::TransformationMode::SmoothTransformation);
	}
	data["visible_image_file_name"] = "";
}

const QImage* BookmarkItem::getVisibleImage()
{
	return &visible_image;
}

QString BookmarkItem::getLocalFilename()
{
	return data["local_file_name"].toString();
}
