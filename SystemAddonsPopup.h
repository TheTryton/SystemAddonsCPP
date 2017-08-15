#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QStateMachine>
#include <QSystemTrayIcon>

#include "BookmarksManager.h"

class SystemAddonsPopup : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(float showPercent READ showPercent WRITE setShowPercent)
public:
	static SystemAddonsPopup* getInstance();

	~SystemAddonsPopup();
private:
	SystemAddonsPopup(SystemAddonsPopup const&) = delete;
	void operator=(SystemAddonsPopup const&) = delete;

	static SystemAddonsPopup* instance;
private:
	SystemAddonsPopup(QWidget *parent = Q_NULLPTR);
protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override; 
	void mouseReleaseEvent(QMouseEvent* event) override; 
public:
	const float& showPercent();
	void setShowPercent(const float& val);
private:
	//POPUP CONTROL VARIABLES
	bool is_resized = false;
	bool is_locked = false;
	float percent_shown = 1.0;
	//DISPLAY
	QLabel* resize_bar_widget = NULL;
	BookmarksManager* management_container_widget = NULL;
	QVBoxLayout* root_layout = NULL;

	QTimer* mouse_pos_check_timer = NULL;

	QStateMachine* window_state_machine = NULL;

	QSystemTrayIcon* system_tray_icon = NULL;
	QMenu* system_tray_icon_context_menu = NULL;
	QAction* is_locked_context_menu_action = NULL;
	//DATA MANAGER POINTER
	DataManager* data_manager;
signals:
	void showSignal();
	void hideSignal();
};
