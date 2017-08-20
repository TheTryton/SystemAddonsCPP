#pragma once

#include <QWidget>
#include <QMenu>

#include "DataManager.h"

class BookmarksManager : public QWidget {
	Q_OBJECT

	friend class SystemAddonsPopup;
	friend class MusicPlayer;
public:
	static BookmarksManager* getInstance();
private:
	BookmarksManager(BookmarksManager const&) = delete;
	void operator=(BookmarksManager const&) = delete;

	static BookmarksManager* instance;
protected:
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;

	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;

	void paintEvent(QPaintEvent* event) override;
private:
	//SELECTION
	QPoint selected_item = QPoint(-1, -1);
	QPoint drag_start_position = QPoint(0, 0);
	//MENU
	QMenu* right_button_context_menu;
	//SYNC IMG
	QImage sync_img;
	//DATA MANAGER POINTER
	DataManager* data_manager;
signals:
	void shouldLock();
	void shouldClose();
	void changedColor();
private:
	BookmarksManager(QWidget * parent = Q_NULLPTR);
public:
	~BookmarksManager();
};
