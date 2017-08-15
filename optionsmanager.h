#pragma once
#include <QObject>
#include "documentsmanageritem.h"

class OptionsManager : public QObject {
	Q_OBJECT

private:
	friend class BookmarksManager;
	friend class NetworkManager;
	friend class SystemAddonsPopup;
	OptionsManager(QObject * parent = Q_NULLPTR);
private:
	static void loadOptions();
	static void saveOptions();

	static int getSelectedScreenIndex();
	static void setSelectedScreenIndex(int selected_screen_index);

	static QColor getBackgroundColor();
	static void setBackgroundColor(QColor color);

	static QColor getResizeBarColor();
	static void setResizeBarColor(QColor color);

	static void setDocumentItemsList(const QList<DocumentsManagerItem>& item_list);
	static const QList<DocumentsManagerItem>& getDocumentItemsList();
private:
	static QColor background_color;
	static QColor resize_bar_color;
	static QList<DocumentsManagerItem> items;
	static int selected_screen_index;
};
