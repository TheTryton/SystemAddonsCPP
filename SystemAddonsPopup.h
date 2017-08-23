#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QStateMachine>
#include <QSystemTrayIcon>

#include "BookmarksManager.h"
#include "MusicPlayer.h"

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
	void closeEvent(QCloseEvent* event) override;
public:
	const float& showPercent();
	void setShowPercent(const float& val);
	void freezePopup(bool freeze = false);
	bool isPopupFrozen();
private:
	//POPUP CONTROL VARIABLES
	bool is_resized = false;
	bool is_locked = false;
	float percent_shown = 1.0;
	//DISPLAY
	QLabel* resize_bar_widget = NULL;
	BookmarksManager* management_container_widget = NULL;
	QVBoxLayout* root_layout = NULL;
	QHBoxLayout* bookmarks_music_layout = NULL;

	QTimer* mouse_pos_check_timer = NULL;

	QStateMachine* window_state_machine = NULL;
	bool m_FreezeStateMachine = false;

	QSystemTrayIcon* system_tray_icon = NULL;
	QMenu* system_tray_icon_context_menu = NULL;
	QAction* is_locked_context_menu_action = NULL;
	//DATA MANAGER POINTER
	DataManager* data_manager = NULL;
	//MUSIC PLAYER
	MusicPlayer* music_player = NULL;
	MusicPlaylist* music_player_playlist = NULL;
	QFrame* music_player_separator = NULL;
	QWidget* music_player_color_filler = NULL;
	QVBoxLayout* music_player_show_button_layout = NULL;
	QPushButton* music_player_show_button = NULL;
signals:
	void showSignal();
	void hideSignal();
};
