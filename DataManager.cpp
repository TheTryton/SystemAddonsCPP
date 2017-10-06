#include "DataManager.h"

#include <QColor>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileInfo>

DataManager* DataManager::instance = NULL;

bool DataManager::saveData(QString filename, bool save_as_binary)
{
	QFile save_file;

	save_file.setFileName(filename);
	if (!save_file.open(QIODevice::WriteOnly)) return false;

	QJsonObject root_data_object;
	//POPUP CONFIGURATION DATA
	{
		QJsonObject popup_configuration_data;
		//BACKGROUND COLOR
		{
			QJsonObject background_color_object;
			QColor background_color = this->getBackgroundColor();
			background_color_object["r"] = background_color.red();
			background_color_object["b"] = background_color.green();
			background_color_object["b"] = background_color.blue();

			popup_configuration_data["background_color"] = background_color_object;
		}
		//RESIZE BAR COLOR
		{
			QJsonObject resize_bar_color_object;
			QColor resize_bar_color = this->getResizeBarColor();
			resize_bar_color_object["r"] = resize_bar_color.red();
			resize_bar_color_object["b"] = resize_bar_color.green();
			resize_bar_color_object["b"] = resize_bar_color.blue();

			popup_configuration_data["resize_bar_color"] = resize_bar_color_object;
		}
		root_data_object["popup_configuration_data"] = popup_configuration_data;
	}
	//BOOKMARKS DATA
	{
		QJsonArray bookmarks_data;
		for (int i = 0; i < this->bookmark_items.size(); i++) {
			QJsonObject bookmark_object;
			//bookmark_object["internet_name"] = this->bookmark_items[i].getInternetName();
			//bookmark_object["synchronize_over_internet"] = this->bookmark_items[i].getSynchronizeOverInternet();

			bookmark_object["visible_name"] = this->bookmark_items[i].getVisibleName();
			bookmark_object["local_file_name"] = this->bookmark_items[i].getLocalFilename();
			bookmark_object["visible_image_file_name"] = this->bookmark_items[i].getVisibleImageFilename();
			bookmarks_data.push_back(bookmark_object);
		}
		root_data_object["bookmarks_data"] = bookmarks_data;
	}
	//PLAYLIST DATA
	{
		QJsonObject music_player_data;
		{
			QJsonArray playlist_data;
			for (int i = 0; i < this->playlist.size(); i++) {
				playlist_data.append(this->playlist[i]);
			}
			music_player_data["playlist_data"] = playlist_data;
			music_player_data["music_volume"] = popup_configuration_data["music_volume"].toDouble();
		}
		root_data_object["music_player_data"] = music_player_data;
	}
	QJsonDocument save_document(root_data_object);
	save_file.write(save_as_binary ? save_document.toBinaryData() : save_document.toJson());

	save_file.close();

	return true;
}

bool DataManager::loadData(QString filename, bool load_as_binary)
{
	QFile load_file;

	load_file.setFileName(filename);
	if (!load_file.open(QIODevice::ReadOnly)) return false;
	QByteArray load_data = load_file.readAll();

	QJsonDocument load_document(load_as_binary ? QJsonDocument::fromBinaryData(load_data) : QJsonDocument::fromJson(load_data));

	if (load_document.isObject()) {
		QJsonObject root_data_object = load_document.object();
		//POPUP CONFIGURATION DATA
		if(root_data_object.contains("popup_configuration_data")){
			if (root_data_object["popup_configuration_data"].isObject()) {
				QJsonObject popup_configuration_data = root_data_object["popup_configuration_data"].toObject();
				//BACKGROUND COLOR
				if (popup_configuration_data.contains("background_color")) {
					if (popup_configuration_data["background_color"].isObject()) {
						QJsonObject background_color_object = popup_configuration_data["background_color"].toObject();
						if (background_color_object.contains("r") && background_color_object.contains("g") && background_color_object.contains("b")) {
							if (background_color_object["r"].isDouble() && background_color_object["g"].isDouble() && background_color_object["b"].isDouble()) {
								QColor background_color;
								background_color.setRed(background_color_object["r"].toInt());
								background_color.setGreen(background_color_object["g"].toInt());
								background_color.setBlue(background_color_object["b"].toInt());
								this->setBackgroundColor(background_color);
							}
						}
					}
				}
				//RESIZE BAR COLOR
				if (popup_configuration_data.contains("resize_bar_color")) {
					if (popup_configuration_data["resize_bar_color"].isObject()) {
						QJsonObject resize_bar_color_object = popup_configuration_data["resize_bar_color"].toObject();
						if (resize_bar_color_object.contains("r") && resize_bar_color_object.contains("g") && resize_bar_color_object.contains("b")) {
							if (resize_bar_color_object["r"].isDouble() && resize_bar_color_object["g"].isDouble() && resize_bar_color_object["b"].isDouble()) {
								QColor resize_bar_color;
								resize_bar_color.setRed(resize_bar_color_object["r"].toInt());
								resize_bar_color.setGreen(resize_bar_color_object["g"].toInt());
								resize_bar_color.setBlue(resize_bar_color_object["b"].toInt());
								this->setResizeBarColor(resize_bar_color);
							}
						}
					}
				}
			}
		}
		//BOOKMARKS DATA
		if (root_data_object.contains("bookmarks_data")) {
			this->bookmark_items.clear();
			if (root_data_object["bookmarks_data"].isArray()) {
				QJsonArray bookmarks_data = root_data_object["bookmarks_data"].toArray();
				for (int i = 0; i < bookmarks_data.size(); i++) {
					if (bookmarks_data[i].isObject()) {
						QJsonObject bookmark_item = bookmarks_data[i].toObject();
						if (bookmark_item.contains("visible_name") && bookmark_item.contains("local_file_name") &&
							bookmark_item.contains("visible_image_file_name")) {
							if (bookmark_item["visible_name"].isString() && bookmark_item["local_file_name"].isString() &&
								bookmark_item["visible_image_file_name"].isString()) {
								QFileInfo bookmark_file_info;
								bookmark_file_info.setFile(bookmark_item["local_file_name"].toString());
								if (bookmark_file_info.exists()) {
									for (int i = 0; i < bookmark_items.size(); i++) if (bookmark_items[i].data["local_file_name"].toString() == filename) continue;
									BookmarkItem* item = new BookmarkItem;
									item->data["local_file_name"] = bookmark_item["local_file_name"].toString();
									//VISIBLE NAME
									if(bookmark_item["visible_name"].toString()!="") item->setVisibleName(bookmark_item["visible_name"].toString());
									else item->setVisibleName(item->getLocalFilename().mid(0, item->getLocalFilename().lastIndexOf('.')));

									//VISIBLE IMAGE FILENAME
									if (bookmark_item["visible_image_file_name"].toString() != "") {
										QFileInfo image_file_info;
										image_file_info.setFile(bookmark_item["visible_image_file_name"].toString());
										if (image_file_info.exists() &&
											(image_file_info.suffix() == "jpg" ||
												image_file_info.suffix() == "jpeg" ||
												image_file_info.suffix() == "png" ||
												image_file_info.suffix() == "ico" ||
												image_file_info.suffix() == "bmp")) {
											item->setVisibleImageFilename(bookmark_item["visible_image_file_name"].toString(), this->getPreferredBookmarkImageSize());
										}
										else item->setVisibleImageAsDefaultFileIcon(this->getPreferredBookmarkImageSize());
									}
									else item->setVisibleImageAsDefaultFileIcon(this->getPreferredBookmarkImageSize());
									/*//NETWORK
									if (bookmark_item["synchronize_over_internet"].toBool()) {
										if (bookmark_item["internet_name"].toString() != "") {
											if (this->registerInternetName(bookmark_item["internet_name"].toString())) {
												item->setInternetName(bookmark_item["internet_name"].toString());
												item->setSynchronizeOverInternet(true);
											}
											else {
												item->setInternetName("");
												item->setSynchronizeOverInternet(false);
											}
										}
										else {
											item->setInternetName("");
											item->setSynchronizeOverInternet(false);
										}
									}
									else {
										item->setInternetName("");
										item->setSynchronizeOverInternet(false);
									}*/
									
									this->bookmark_items.push_back(*item);
								}
								
							}
						}
					}
				}
				root_data_object["bookmarks_data"] = bookmarks_data;
			}
		}
		//PLAYLIST DATA
		if (root_data_object.contains("music_player_data")) {
			if (root_data_object["music_player_data"].isObject()) {
				QJsonObject music_player_data = root_data_object["music_player_data"].toObject();
				if (music_player_data.contains("playlist_data")) {
					if (music_player_data["playlist_data"].isArray()) {
						this->playlist.clear();
						QJsonArray playlist_data = music_player_data["playlist_data"].toArray();
						for (int i = 0; i < playlist_data.size(); i++) {
							if (playlist_data[i].isString()) {
								playlist.append(playlist_data[i].toString());
							}
						}
					}
				}
				if (music_player_data.contains("music_volume")) {
					if (music_player_data["music_volume"].isDouble()) {
						popup_configuration_data["music_volume"] = qMax(0.0, qMin(1.0, music_player_data["music_volume"].toDouble()));
					}
				}
			}
		}
	}

	load_file.close();

	return true;
}

QList<QString> DataManager::getPlaylist()
{
	return playlist;
}

void DataManager::setPlaylist(QList<QString> playlist)
{
	this->playlist = playlist;
}

double DataManager::getVolume()
{
	return popup_configuration_data["music_volume"].toDouble();
}

void DataManager::setVolume(double volume)
{
	volume = qMax(0.0, qMin(1.0, volume));
	popup_configuration_data["music_volume"] = volume;
}

QColor DataManager::getBackgroundColor()
{
	return popup_configuration_data["background_color"].value<QColor>();
}

QColor DataManager::getDefaultBackgroundColor()
{
	return popup_configuration_data["default_background_color"].value<QColor>();
}

void DataManager::setBackgroundColor(QColor color)
{
	popup_configuration_data["background_color"] = color;
}

DataManager* DataManager::getInstance() {
	if (DataManager::instance == NULL) DataManager::instance = new DataManager;
	return DataManager::instance;
}

QColor DataManager::getResizeBarColor()
{
	return popup_configuration_data["resize_bar_color"].value<QColor>();
}

QColor DataManager::getDefaultResizeBarColor()
{
	return popup_configuration_data["default_resize_bar_color"].value<QColor>();
}

void DataManager::setResizeBarColor(QColor color)
{
	popup_configuration_data["resize_bar_color"] = color;
}

QSize DataManager::getPreferredBookmarkSize()
{
	return popup_configuration_data["preferred_bookmark_size"].toSize();
}

void DataManager::setPreferredBookmarkSize(QSize size)
{
	popup_configuration_data["preferred_bookmark_size"] = size;
}

QSize DataManager::getPreferredBookmarkImageSize()
{
	QSize preferred_size = popup_configuration_data["preferred_bookmark_size"].toSize();
	preferred_size = QSize(preferred_size.width()*0.95, preferred_size.height() / 2.0 * 0.95);
	return preferred_size;
}

QSize DataManager::getSpacingBetweenBookmarks()
{
	return popup_configuration_data["bookmark_spacing"].toSize();
}

void DataManager::setSpacingBetweenBookmarks(QSize spacing)
{
	popup_configuration_data["bookmark_spacing"] = spacing;
}

QList<BookmarkItem>* DataManager::getBookmarkItems()
{
	return &bookmark_items;
}

void DataManager::removeBookmark(int index)
{
	if (index >= 0 && index < bookmark_items.size()) {
		//if (bookmark_items[index].getSynchronizeOverInternet())unregisterInternetName(bookmark_items[index].getInternetName());
		bookmark_items.erase(bookmark_items.begin() + index);
	}
}

const BookmarkItem * DataManager::addBookmark(QString filename)
{
	QFileInfo bookmark_file_info;
	bookmark_file_info.setFile(filename);
	if (bookmark_file_info.exists()) {
		//CHECK IF BOOKMARK DOESN'T EXIST
		for (int i = 0; i < bookmark_items.size(); i++) if (bookmark_items[i].data["local_file_name"].toString() == filename) return NULL;
		BookmarkItem* item = new BookmarkItem;
		item->data["local_file_name"] = filename;
		//VISIBLE NAME
		QFileInfo file_info(filename);
		item->setVisibleName(file_info.fileName().mid(0, file_info.fileName().lastIndexOf('.')));

		//VISIBLE IMAGE FILENAME
		item->setVisibleImageAsDefaultFileIcon(this->getPreferredBookmarkImageSize());

		//NETWORK
		//item->setInternetName("");
		//item->setSynchronizeOverInternet(false);

		this->bookmark_items.push_back(*item);
		return item;
	}
	return NULL;
}

/*
QList<InternetName>* DataManager::getInternetNames()
{
	return &internet_names;
}

bool DataManager::registerInternetName(QString name)
{
	if (name == "")return false;
	for (int i = 0; i < internet_names.size(); i++) {
		if (internet_names[i].internet_name == name) {
			for (int j = 0; j < internet_names[i].ip_addresses.size(); j++) {
				if (internet_names[i].ip_addresses[j] == local_host_address) return false;
			}
			internet_names[i].ip_addresses.push_back(local_host_address);
			return true;
		}
	}
	InternetName* internet_name = new InternetName;
	internet_name->internet_name = name;
	internet_name->ip_addresses.push_back(local_host_address);
	internet_names.push_back(*internet_name);
	return true;
}

void DataManager::unregisterInternetName(QString name)
{
	for (int i = 0; i < internet_names.size(); i++) {
		if (internet_names[i].internet_name == name) {
			for (int j = 0; j < internet_names[i].ip_addresses.size(); j++) {
				if (internet_names[i].ip_addresses[j] == local_host_address) {
					if (internet_names[i].ip_addresses.size() == 1) {
						internet_names.erase(internet_names.begin() + i);
					}
					else internet_names[i].ip_addresses.erase(internet_names[i].ip_addresses.begin() + j);
					return;
				}
			}
		}
	}
}

void DataManager::addDetectedInternetName(QString name, QHostAddress host_address)
{
	for (int i = 0; i < internet_names.size(); i++) {
		if (internet_names[i].internet_name == name) {
			for (int j = 0; j < internet_names[i].ip_addresses.size(); j++) {
				if (internet_names[i].ip_addresses[j] == host_address) return;
			}
			internet_names[i].ip_addresses.push_back(host_address);
			return;
		}
	}
	InternetName* internet_name = new InternetName;
	internet_name->internet_name = name;
	internet_name->ip_addresses.push_back(host_address);
	internet_names.push_back(*internet_name);
}

void DataManager::removeAllDetectedInternetNames()
{
	for (int i = 0; i < internet_names.size(); i++) {
		int local_address_index = -1;
		for (int j = 0; j < internet_names[i].ip_addresses.size(); j++) {
			if (internet_names[i].ip_addresses[j] == local_host_address) {
				local_address_index = j;
				break;
			}
		}
		if (local_address_index == -1) internet_names.erase(internet_names.begin() + i);
		else {
			if (local_address_index != 0)internet_names.erase(internet_names.begin(), internet_names.begin() + i);
			if (internet_names.size() != 1)internet_names.erase(internet_names.begin() + 1, internet_names.end());
		}
	}
}

void DataManager::unregisterAllRegisteredInternetNames()
{
	for (int i = 0; i < internet_names.size(); i++) {
		for (int j = 0; j < internet_names[i].ip_addresses.size(); j++) {
			if (internet_names[i].ip_addresses[j] == local_host_address) {
				internet_names[i].ip_addresses.erase(internet_names[i].ip_addresses.begin() + i);
				break;
			}
		}
	}
}

QHostAddress DataManager::getLocalhostAddress()
{
	return local_host_address;
}
*/

DataManager::DataManager(QObject *parent) : QObject(parent)
{
	popup_configuration_data["background_color"] = QColor(0, 120, 180, 180);
	popup_configuration_data["default_background_color"] = QColor(0, 120, 180, 180);
	popup_configuration_data["resize_bar_color"] = QColor(0, 80, 220, 200);
	popup_configuration_data["default_resize_bar_color"] = QColor(0, 80, 220, 200);
	popup_configuration_data["preferred_bookmark_size"] = QSize(90, 100);
	popup_configuration_data["bookmark_spacing"] = QSize(5, 5);

	/*foreach(const QHostAddress &address, QNetworkInterface::allAddresses()) {
		if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)) {
			local_host_address = address;
			break;
		}
	}*/
}

DataManager::~DataManager()
{
	if (instance != NULL)delete instance;
}
