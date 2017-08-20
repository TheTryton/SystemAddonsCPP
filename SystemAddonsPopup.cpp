#include "SystemAddonsPopup.h"

#include "DataManager.h"
#include "NetworkManager.h"

#include <QSharedMemory>
#include <QApplication>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QScreen>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QTimer>
#include <QMessageBox>
#include <QtMultimedia>

#include <iostream>

using namespace std;


SystemAddonsPopup* SystemAddonsPopup::instance = NULL;

SystemAddonsPopup::SystemAddonsPopup(QWidget *parent)
	: QWidget(parent)
{
	QSize selected_screen_size;

	NetworkManager::getInstance()->startScanning();
	
	//DATA MANAGER INITIALIZATION
	{
		data_manager = DataManager::getInstance();
		data_manager->loadData();
	}
	//MAIN POPUP WINDOW INITIALIZATION
	{
		this->setMouseTracking(true);

		this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
		this->setAttribute(Qt::WA_TranslucentBackground);
		QPalette pal = this->palette();
		pal.setColor(QPalette::Window, QColor(255,255,255,0));
		this->setAutoFillBackground(true);
		this->setPalette(pal);

		selected_screen_size = QApplication::screens()[QApplication::desktop()->primaryScreen()]->availableSize();

		this->setMinimumWidth(selected_screen_size.width());
		this->setMaximumWidth(selected_screen_size.width());
		this->setMinimumHeight(selected_screen_size.height() / 9);
		this->setMaximumHeight(selected_screen_size.height() / 2);

		this->setGeometry(QRect(QPoint(0, 0), QSize(selected_screen_size.width(), selected_screen_size.height() / 9)));
		this->setWindowIcon(QIcon(u8":/SystemAddonsPopup/icons/System Addons.ico"));
	}
	//DOCUMENT MANAGER INITIALIZATION
	{
		management_container_widget = new BookmarksManager(this);
		management_container_widget->setMouseTracking(true);
		QPalette palette = management_container_widget->palette();
		palette.setBrush(QPalette::Window, QBrush(data_manager->getBackgroundColor()));
		management_container_widget->setAutoFillBackground(true);
		management_container_widget->setPalette(palette);
		management_container_widget->setFixedWidth(width() - 80);
		QObject::connect(management_container_widget, &BookmarksManager::shouldLock, [&]() {
			is_locked = true;
			is_locked_context_menu_action->setChecked(is_locked);
			emit hideSignal();
		});
		QObject::connect(management_container_widget, &BookmarksManager::shouldClose, [&]() {
			this->close();
		});
		QObject::connect(management_container_widget, &BookmarksManager::changedColor, [&]() {
			QPalette palette = management_container_widget->palette();
			palette.setBrush(QPalette::Window, QBrush(data_manager->getBackgroundColor()));
			management_container_widget->setPalette(palette);

			palette = resize_bar_widget->palette();
			QLinearGradient grad = QLinearGradient(0, 0, 0, 8);
			grad.setColorAt(0.0, data_manager->getBackgroundColor());
			grad.setColorAt(0.6, data_manager->getResizeBarColor());
			grad.setColorAt(1.0, data_manager->getResizeBarColor());
			palette.setBrush(QPalette::Window, grad);
			resize_bar_widget->setPalette(palette);

			palette = music_player_color_filler->palette();
			palette.setBrush(QPalette::Window, QBrush(data_manager->getBackgroundColor()));
			music_player_color_filler->setAutoFillBackground(true);
		});
	}
	//MUSIC PLAYER INITIALIZATION
	{
		music_player_color_filler = new QWidget;
		QPalette palette = music_player_color_filler->palette();
		palette.setBrush(QPalette::Window, QBrush(data_manager->getBackgroundColor()));
		music_player_color_filler->setAutoFillBackground(true);
		music_player_color_filler->setPalette(palette);
		music_player_color_filler->setFixedWidth(76);

		music_player_separator = new QFrame;
		music_player_separator->setFrameShape(QFrame::Shape::VLine);
		music_player_separator->setStyleSheet(""
			"QFrame{"
			"	border: 2px solid white"
			"}");
		music_player_separator->setFixedWidth(4);

		music_player_show_button = new QPushButton;
		music_player_show_button->setFixedSize(60, 60);
		music_player_show_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_inactive.png"));
		music_player_show_button->setIconSize(QSize(56, 56));
		music_player_show_button->setFlat(true);
		QObject::connect(music_player_show_button, &QPushButton::released, [&]() {
			if (music_player->isVisible()) 
			{
				music_player_show_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_inactive.png"));
				music_player->stop();
				music_player->hide();
			}
			else
			{
				music_player_show_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_active.png"));
				music_player->play();
				music_player->show();
				music_player->repaint();
			}
		});

		music_player = MusicPlayer::getInstance();
		music_player->attachVisualiser();
		music_player->playlist()->setPlaybackMode(MusicPlaylist::PlaybackMode::Random);
		music_player->setWindowIcon(QIcon(u8":/SystemAddonsPopup/icons/System Addons.ico"));
		QObject::connect(music_player, &MusicPlayer::hiding, [&]() {
			music_player_show_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_inactive.png"));
			music_player_show_button->repaint();
		});

	}
	//RESIZE BAR INITIALIZATION
	{
		resize_bar_widget = new QLabel(this);
		resize_bar_widget->setMouseTracking(true);
		resize_bar_widget->setFixedSize(QSize(this->minimumWidth(), 8));

		QPalette pal = resize_bar_widget->palette();
		QLinearGradient grad = QLinearGradient(0, 0, 0, 8);
		grad.setColorAt(0.0, data_manager->getBackgroundColor());
		grad.setColorAt(0.6, data_manager->getResizeBarColor());
		grad.setColorAt(1.0, data_manager->getResizeBarColor());
		pal.setBrush(QPalette::Window, grad);
		resize_bar_widget->setAutoFillBackground(true);
		resize_bar_widget->setPalette(pal);
	}
	//LAYOUT INITIALIZATION
	{
		bookmarks_music_layout = new QHBoxLayout();

		bookmarks_music_layout->setMargin(0);
		bookmarks_music_layout->setSpacing(0);
		bookmarks_music_layout->setAlignment(Qt::AlignmentFlag::AlignLeft);

		bookmarks_music_layout->addWidget(management_container_widget);

		music_player_show_button_layout = new QVBoxLayout;
		music_player_show_button_layout->setMargin(5);
		music_player_show_button_layout->setAlignment(Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignTop);
		music_player_show_button_layout->addWidget(music_player_show_button);
		music_player_color_filler->setLayout(music_player_show_button_layout);

		bookmarks_music_layout->addWidget(music_player_separator);
		bookmarks_music_layout->addWidget(music_player_color_filler);

		root_layout = new QVBoxLayout();

		root_layout->setMargin(0);
		root_layout->setSpacing(0);

		root_layout->addLayout(bookmarks_music_layout);
		root_layout->addWidget(resize_bar_widget);

		this->setLayout(root_layout);
	}
	//WINDOW STATE MACHINE INITIALIZATION
	{
		window_state_machine = new QStateMachine(this);

		QState *hide_state = new QState(window_state_machine);
		hide_state->assignProperty(this, "showPercent", 0);
		window_state_machine->setInitialState(hide_state);

		QState *show_state = new QState(window_state_machine);
		show_state->assignProperty(this, "showPercent", 1);

		QPropertyAnimation* prop_anim = new QPropertyAnimation(this, "showPercent");
		prop_anim->setEasingCurve(QEasingCurve::OutSine);
		prop_anim->setDuration(250);

		QSignalTransition *hide_to_show_transition = hide_state->addTransition(this, &SystemAddonsPopup::showSignal, show_state);
		hide_to_show_transition->addAnimation(prop_anim);

		QSignalTransition *show_to_hide_transition = show_state->addTransition(this, &SystemAddonsPopup::hideSignal, hide_state);
		show_to_hide_transition->addAnimation(prop_anim);

		window_state_machine->start();
	}
	//MOUSE POS CHECKER INITIALIZATION
	{
		mouse_pos_check_timer = new QTimer(this);

		QObject::connect(mouse_pos_check_timer, &QTimer::timeout, [&]() {
			if (QRect(0, 0, this->size().width(), 5).contains(QCursor::pos()) || this->geometry().contains(QCursor::pos())) {
				if (!is_locked) {
					emit showSignal();
					if(!this->geometry().adjusted(0, this->geometry().height()-8,0,0).contains(QCursor::pos()))QApplication::setOverrideCursor(Qt::ArrowCursor);
				}
			}
			else {
				if (!is_locked) {
					if (!is_resized) {
						emit hideSignal();
					}
				}
			}
			if (music_player->isVisible()) {
				if (music_player->geometry().contains(QCursor::pos())) {
					QApplication::setOverrideCursor(Qt::ArrowCursor);
				}
			}
		});

		mouse_pos_check_timer->start(100);
	}
	//SYSTEM TRAY ICON AND CONTEXT MENU INITIALIZATION
	{
		system_tray_icon = new QSystemTrayIcon(this);
		system_tray_icon->setIcon(QIcon(u8":/SystemAddonsPopup/icons/System Addons.ico"));
		QObject::connect(system_tray_icon, &QSystemTrayIcon::activated, [&](QSystemTrayIcon::ActivationReason reason) {
			QApplication::setOverrideCursor(Qt::ArrowCursor);
			if (reason == QSystemTrayIcon::ActivationReason::DoubleClick) {
				is_locked = false;
				is_locked_context_menu_action->setChecked(is_locked);
			}
		});

		//SYSTEM TRAY CONTEXT MENU
		{
			system_tray_icon_context_menu = new QMenu(this);

			is_locked_context_menu_action = new QAction(u8"Lock", this);
			is_locked_context_menu_action->setCheckable(true);
			QObject::connect(is_locked_context_menu_action, &QAction::triggered, [&](bool checked) {
				is_locked = !is_locked;
				is_locked_context_menu_action->setChecked(is_locked);
			});
			system_tray_icon_context_menu->addAction(is_locked_context_menu_action);

			system_tray_icon_context_menu->addSeparator();

			QAction* exit = new QAction(u8"Exit", this);
			QObject::connect(exit, &QAction::triggered, [&](bool checked) {
				QApplication::exit();
			});
			system_tray_icon_context_menu->addAction(exit);
		}

		system_tray_icon->setContextMenu(system_tray_icon_context_menu);

		system_tray_icon->setToolTip(u8"System Addons");

		system_tray_icon->show();
	}
}

void SystemAddonsPopup::mousePressEvent(QMouseEvent * event)
{
	if (resize_bar_widget->geometry().adjusted(0, 2, 0, 0).contains(event->pos())) {
		is_resized = true;
		QApplication::setOverrideCursor(Qt::CursorShape::SizeVerCursor);
	}
}

void SystemAddonsPopup::mouseMoveEvent(QMouseEvent * event)
{
	if (!is_resized) {
		if (resize_bar_widget->geometry().adjusted(0, 2 + this->size().height() - this->size().height()*percent_shown,0,0).contains(event->pos())) {
			QApplication::setOverrideCursor(Qt::CursorShape::SizeVerCursor);
		}
		else {
			QApplication::setOverrideCursor(Qt::CursorShape::ArrowCursor);
		}
	}
	else {
		this->resize(QSize(this->size().width(), event->pos().y()));
	}
}

void SystemAddonsPopup::mouseReleaseEvent(QMouseEvent * event)
{
	if (is_resized) {
		QApplication::setOverrideCursor(Qt::CursorShape::ArrowCursor);
		is_resized = false;
	}
}

SystemAddonsPopup* SystemAddonsPopup::getInstance() {
	if (SystemAddonsPopup::instance == NULL) {
		QSharedMemory *single_app = new QSharedMemory("SharedMemoryForSystemAddons", NULL);
		if (single_app->attach(QSharedMemory::ReadOnly)) {
			single_app->detach();
			QMessageBox::warning(NULL, "", "Another instance of System Addons is already running");
			return NULL;
		}
		else {
			if (single_app->create(1)) {
				SystemAddonsPopup::instance = new SystemAddonsPopup();
				return SystemAddonsPopup::instance;
			}
			else {
				QMessageBox::warning(NULL, "", "Another instance of System Addons is already running");
				return NULL;
			}
		}
	}
	return SystemAddonsPopup::instance;
}

const float& SystemAddonsPopup::showPercent()
{
	return percent_shown;
}

void SystemAddonsPopup::setShowPercent(const float& val)
{
	percent_shown = val;
	this->move(QPoint(0,-this->size().height() + this->size().height()*percent_shown));
}

void SystemAddonsPopup::freezePopup(bool freeze)
{
	is_locked = freeze;
}

bool SystemAddonsPopup::isPopupFrozen()
{
	return is_locked;
}

SystemAddonsPopup::~SystemAddonsPopup()
{
	if (instance != NULL)delete instance;
	system_tray_icon->hide();
}
