#include "optionsmanager.h"

#include <QColor>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

int OptionsManager::selected_screen_index = -1;
QColor OptionsManager::background_color = QColor(0, 120, 180, 180);
QColor OptionsManager::resize_bar_color = QColor(0, 80, 220, 200);
QList<DocumentsManagerItem> OptionsManager::items;

void OptionsManager::loadOptions()
{
	QFile load_file("save.json");

	if (!load_file.open(QIODevice::ReadOnly)) {
		saveOptions();
		return;
	}

	QByteArray load_data = load_file.readAll();

	QJsonDocument load_document(QJsonDocument::fromJson(load_data));

	QJsonObject data_object = load_document.object();

	if (data_object.contains("background_color")) {
		background_color.setRed(((QJsonObject)data_object["background_color"].toObject())["r"].toInt());
		background_color.setGreen(((QJsonObject)data_object["background_color"].toObject())["g"].toInt());
		background_color.setBlue(((QJsonObject)data_object["background_color"].toObject())["b"].toInt());
	}
	if (data_object.contains("resize_bar_color")) {
		resize_bar_color.setRed(((QJsonObject)data_object["resize_bar_color"].toObject())["r"].toInt());
		resize_bar_color.setGreen(((QJsonObject)data_object["resize_bar_color"].toObject())["g"].toInt());
		resize_bar_color.setBlue(((QJsonObject)data_object["resize_bar_color"].toObject())["b"].toInt());
	}
	if (data_object.contains("documents")) {
		QJsonArray documents_array = data_object["documents"].toArray();
		items.clear();
		for (int i = 0; i < documents_array.size(); i++) {
			QJsonObject item = documents_array[i].toObject();
			DocumentsManagerItem* it = new DocumentsManagerItem();
			if (item.contains("file_name")) it->file_name = item["file_name"].toString();
			if (item.contains("visible_name")) it->visible_name = item["visible_name"].toString();
			if (item.contains("img_file_name")) it->img_file_name = item["img_file_name"].toString();
			if (item.contains("sync_over_internet")) it->sync_over_internet = item["sync_over_internet"].toBool();
			if (item.contains("internet_name")) it->internet_name = item["internet_name"].toString();

			items.push_back(*it);
		}
	}
	if (data_object.contains("selected_screen_index")) {
		selected_screen_index = data_object["selected_screen_index"].toInt();
	}

	load_file.close();
}

void OptionsManager::saveOptions()
{
	QFile save_file("save.json");
	if (!save_file.open(QIODevice::WriteOnly)) return;
	QJsonObject data_object;
	//BACKGROUND COLOR
	{
		QJsonObject background_color_object;
		background_color_object["r"] = background_color.red();
		background_color_object["g"] = background_color.green();
		background_color_object["b"] = background_color.blue();
		data_object["background_color"] = background_color_object;
	}
	//RESIZE BAR COLOR
	{
		QJsonObject resize_bar_color_object;
		resize_bar_color_object["r"] = resize_bar_color.red();
		resize_bar_color_object["g"] = resize_bar_color.green();
		resize_bar_color_object["b"] = resize_bar_color.blue();
		data_object["resize_bar_color"] = resize_bar_color_object;
	}
	//DOCUMENT LIST
	{
		QJsonArray documents_array;
		for (int i = 0; i < items.size(); i++) {
			QJsonObject item;
			item["file_name"] = items[i].getFileName();
			item["visible_name"] = items[i].getVisibleName();
			item["img_file_name"] = items[i].getImgFileName();
			item["sync_over_internet"] = items[i].getSyncOverInternet();
			item["internet_name"] = items[i].getInternetName();
			documents_array.append(item);
		}
		data_object["documents"] = documents_array;
	}
	//SELECTED SCREEN INDEX
	{
		data_object["selected_screen_index"] = selected_screen_index;
	}

	QJsonDocument save_document(data_object);
	save_file.write(save_document.toJson());

	save_file.close();
}

int OptionsManager::getSelectedScreenIndex()
{
	return selected_screen_index;
}

void OptionsManager::setSelectedScreenIndex(int selected_screen_index)
{
	OptionsManager::selected_screen_index = selected_screen_index;
	saveOptions();
}

QColor OptionsManager::getBackgroundColor()
{
	return background_color;
}

void OptionsManager::setBackgroundColor(QColor color)
{
	background_color = color;
	saveOptions();
}

QColor OptionsManager::getResizeBarColor()
{
	return resize_bar_color;
}

void OptionsManager::setResizeBarColor(QColor color)
{
	resize_bar_color = color;
	saveOptions();
}

void OptionsManager::setDocumentItemsList(const QList<DocumentsManagerItem>& item_list)
{
	items = item_list;
	saveOptions();
}

const QList<DocumentsManagerItem>& OptionsManager::getDocumentItemsList()
{
	return items;
}

OptionsManager::OptionsManager(QObject * parent) : QObject(parent) {
	
}

