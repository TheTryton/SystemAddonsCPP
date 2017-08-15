#include "documentsmanageritem.h"

DocumentsManagerItem::DocumentsManagerItem(QObject * parent) : QObject(parent) {
}

DocumentsManagerItem::DocumentsManagerItem(const DocumentsManagerItem & dmi)
{
	this->visible_name = dmi.visible_name;
	this->file_name = dmi.file_name;
	this->img_file_name = dmi.img_file_name;
	this->img = dmi.img;
	this->item_display_position = dmi.item_display_position;
	this->total_size = dmi.total_size;
	this->internet_name = dmi.internet_name;
	this->sync_over_internet = dmi.sync_over_internet;
}

DocumentsManagerItem::~DocumentsManagerItem() {
	
}

void DocumentsManagerItem::setVisibleName(QString visible_name)
{
	this->visible_name = visible_name;
}

QString DocumentsManagerItem::getVisibleName()
{
	return visible_name;
}

QString DocumentsManagerItem::getFileName()
{
	return file_name;
}

void DocumentsManagerItem::setSyncOverInternet(bool sync)
{
	sync_over_internet = sync;
}

bool DocumentsManagerItem::getSyncOverInternet()
{
	return sync_over_internet;
}

void DocumentsManagerItem::setInternetName(QString name)
{
	internet_name = name;
}

QString DocumentsManagerItem::getInternetName()
{
	return internet_name;
}

QString DocumentsManagerItem::getImgFileName()
{
	return img_file_name;
}

void DocumentsManagerItem::setImage(QImage& image)
{
	this->img = image;
}

QImage& DocumentsManagerItem::getImage()
{
	return img;
}

void DocumentsManagerItem::setPos(QPoint pos)
{
	this->item_display_position = pos;
}

QPoint DocumentsManagerItem::getPos()
{
	return item_display_position;
}

void DocumentsManagerItem::setSize(QSize size)
{
	this->total_size = size;
}

QSize DocumentsManagerItem::getSize()
{
	return total_size;
}
