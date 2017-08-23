#include "MusicPlayer.h"
#include "MathHelper.h"
#include "SystemAddonsPopup.h"
#pragma comment(lib,"FMOD/fmod64_vc.lib")

#include <QtMultimedia>

#include <iostream>

using namespace std;

MusicPlayer* MusicPlayer::instance = NULL;

MusicPlayer::MusicPlayer(QWidget *parent)
	: QWidget(parent)
{
	//SOUND SYSTEM INITIALIZATION
	{
		init();
	}
	//DATA MANAGER
	{
		data_manager = DataManager::getInstance();
	}
	//CREATING WINDOW LAYOUT
	{
		root_layout = new QVBoxLayout;
		{
			playlist_visualiser_layout = new QHBoxLayout;
			{
				music_visualiser = new MusicVisualiser(this);
				music_visualiser->setVisible(false);

				playlist_music_selector = new QListWidget;
			}
			bottom_layout = new QVBoxLayout;
			{
				position_slider = new MusicSlider;
				buttons_layout = new QHBoxLayout;
				{
					random_button = new QPushButton;
					repeat_button = new QPushButton;

					separator_mode_frame = new QFrame;

					previous_button = new QPushButton;
					backward_button = new QPushButton;
					play_pause_button = new QPushButton;
					forward_button = new QPushButton;
					next_button = new QPushButton;

					separator_volume_frame = new QFrame;

					volume_mute_button = new QPushButton;
					volume_slider = new MusicSlider;

					separator_playlist_buttons_frame = new QFrame;

					playlist_remove_button = new QPushButton;
					playlist_clear_button = new QPushButton;
					playlist_show_hide_button = new QPushButton;
				}
			}

		}

		root_layout->setMargin(0);
		root_layout->setSpacing(2);
		root_layout->addLayout(playlist_visualiser_layout, 9);
		{
			playlist_visualiser_layout->setMargin(0);
			playlist_visualiser_layout->setSpacing(0);

			playlist_visualiser_layout->addWidget(music_visualiser, 7);

			playlist_visualiser_layout->addWidget(playlist_music_selector, 3);
			playlist_music_selector->setMinimumWidth(200);
			playlist_music_selector->setMaximumWidth(300);
			playlist_music_selector->setStyleSheet(
				"QListWidget {"
				"	background:	qradialgradient(cx:0.5, cy:0.5, radius: 1,"
				"				fx:0.5, fy : 0.5, stop : 0 white, stop : 1 green)"
				"}"
				"QListWidget::item:selected{"
				"	background: 1px solid rgb(255,0,0);"
				"}"/*

				"QListWidget::item : selected : !active{"
				"	background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,"
				"								stop : 0 #ABAFE5, stop: 1 #8588B2);"
				"}"

				"QListWidget::item : selected : active{"
				"	background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,"
				"								stop : 0 #6a6ea9, stop: 1 #888dd9);"
				"}"

				"QListWidget::item : hover{"
				"	background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1,"
				"	stop : 0 #FAFBFE, stop: 1 #DCDEF1);"
				"}"*/);
			void(QListWidget::*fun1)(int) = &QListWidget::currentRowChanged;
			QObject::connect(playlist_music_selector, fun1, this, [&](int index) {
				if (index != -1) {
					if (this->currentMusicIndex() != index) {
						this->play(index);
					}
				}
				else {
					playlist_music_selector->setCurrentRow(this->currentMusicIndex());
				}
			});
			void(MusicPlayer::*fun2)(int) = &MusicPlayer::currentMusicChanged;
			QObject::connect(this, fun2, [&](int index) {
				playlist_music_selector->setCurrentRow(index);
			});
		}
		root_layout->addLayout(bottom_layout, 1);
		{
			bottom_layout->addWidget(position_slider);
			position_slider->setOrientation(Qt::Orientation::Horizontal);
			position_slider->setMinimum(0);
			position_slider->setMaximum(0);
			position_slider->setStyleSheet(
				"QSlider::right-arrow:horizontal, QSlider::left-arrow:horizontal {"
				"	border: none;"
				"	background: none;"
				"	color: none;"
				"}"
			);
			QObject::connect(position_slider, &QSlider::valueChanged, [&](int value) {
				if (qAbs(position() - value) > 100)this->setPosition(value);
			});

			QObject::connect(this, &MusicPlayer::durationChanged, [&](uint duration) {
				position_slider->setMaximum(duration);
			});
			QObject::connect(this, &MusicPlayer::positionChanged, [&](uint position) {
				position_slider->setValue(position);
			});

			bottom_layout->setMargin(1);
			bottom_layout->setSpacing(1);
			bottom_layout->setAlignment(Qt::AlignmentFlag::AlignBottom);
			bottom_layout->addLayout(buttons_layout);
			{
				buttons_layout->setMargin(1);
				buttons_layout->setSpacing(5);
				buttons_layout->setAlignment(Qt::AlignmentFlag::AlignBottom | Qt::AlignmentFlag::AlignHCenter);

				QString buttons_stylesheet = ""
					"QPushButton{"
					"	border-width: 2px;"
					"	border-style: solid;"
					"	border-color: #8e008e;"
					"	border-radius: 12px;"
					"	border-style: outset;"
					"	background-color: #ffffff"
					"}"
					"QPushButton:hover{"
					"	border-width: 2px;"
					"	border-style: solid;"
					"	border-color: #8e008e;"
					"	border-radius: 12px;"
					"	border-style: outset;"
					"	background-color: #dddddd"
					"}"
					"QPushButton:pressed{"
					"	border-width: 2px;"
					"	border-style: solid;"
					"	border-color: #8e008e;"
					"	border-radius: 12px;"
					"	border-style: inset;"
					"	background-color: #cccccc"
					"}";

				//RANDOM & REPEAT BUTTON
				{
					buttons_layout->addWidget(random_button);
					random_button->setFlat(true);
					random_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/shuffle_inactive.png"));
					random_button->setProperty("active", 0);
					random_button->setFixedSize(48, 48);
					random_button->setIconSize(QSize(36, 36));
					random_button->setStyleSheet(buttons_stylesheet);
					QObject::connect(random_button, &QPushButton::released, [=]() {
						if (random_button->property("active").toInt()) {
							random_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/shuffle_inactive.png"));
							random_button->setProperty("active", 0);
							switch (repeat_button->property("active").toInt()) {
							case 0:
							default:
								this->m_MusicPlaylist->setPlaybackMode(MusicPlaylist::PlaybackMode::Sequential);
								break;
							case 1:
								this->m_MusicPlaylist->setPlaybackMode(MusicPlaylist::PlaybackMode::Loop);
								break;
							case 2:
								this->m_MusicPlaylist->setPlaybackMode(MusicPlaylist::PlaybackMode::CurrentItemInLoop);
								break;
							}
						}
						else {
							random_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/shuffle_active.png"));
							random_button->setProperty("active", 1);
							this->m_MusicPlaylist->setPlaybackMode(MusicPlaylist::PlaybackMode::Random);
						}
					});

					buttons_layout->addWidget(repeat_button);
					repeat_button->setFlat(true);
					repeat_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/repeat_inactive.png"));
					repeat_button->setProperty("active", 0);
					repeat_button->setFixedSize(48, 48);
					repeat_button->setIconSize(QSize(36, 36));
					repeat_button->setStyleSheet(buttons_stylesheet);
					QObject::connect(repeat_button, &QPushButton::released, [=]() {
						switch (repeat_button->property("active").toInt()) {
						case 0:
						default:
							if (!random_button->property("active").toInt()) {
								this->m_MusicPlaylist->setPlaybackMode(MusicPlaylist::PlaybackMode::Loop);
							}
							repeat_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/repeat_active.png"));
							repeat_button->setProperty("active", 1);
							break;
						case 1:
							if (!random_button->property("active").toInt()) {
								this->m_MusicPlaylist->setPlaybackMode(MusicPlaylist::PlaybackMode::CurrentItemInLoop);
							}
							repeat_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/repeat_active_one.png"));
							repeat_button->setProperty("active", 2);
							break;
						case 2:
							if (!random_button->property("active").toInt()) {
								this->m_MusicPlaylist->setPlaybackMode(MusicPlaylist::PlaybackMode::Sequential);
							}
							repeat_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/repeat_inactive.png"));
							repeat_button->setProperty("active", 0);
							break;
						}


					});
				}

				buttons_layout->addSpacing(3);
				buttons_layout->addWidget(separator_mode_frame);
				separator_mode_frame->setFrameShape(QFrame::Shape::VLine);
				separator_mode_frame->setStyleSheet(""
					"QFrame{"
					"	background-color: #aaaaaa"
					"}"
				);
				buttons_layout->addSpacing(3);

				//PREVIOUS & BACKWARD & PLAY/PAUSE & FORWARD & NEXT
				{
					buttons_layout->addWidget(previous_button);
					previous_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/previous.png"));
					previous_button->setFixedSize(64, 48);
					previous_button->setIconSize(QSize(52, 36));
					previous_button->setFlat(true);
					previous_button->setStyleSheet(buttons_stylesheet);
					QObject::connect(previous_button, &QPushButton::released, [&]() {
						if (m_MusicPlaylist) {
							if ((float)position() / duration() > 0.05) {
								setPosition(0);
							}
							else {
								m_MusicPlaylist->previous();
								play();
							}
						}
					});

					buttons_layout->addWidget(backward_button);
					backward_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/backward.png"));
					backward_button->setFixedSize(64, 48);
					backward_button->setIconSize(QSize(52, 36));
					backward_button->setFlat(true);
					backward_button->setStyleSheet(buttons_stylesheet);
					QObject::connect(backward_button, &QPushButton::released, [&]() {
						if (m_MusicPlaylist) {
							setPosition(qMax(0, (int)position() - 2000));
						}
					});

					buttons_layout->addWidget(play_pause_button);
					play_pause_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/pause.png"));
					play_pause_button->setProperty("active", 1);
					play_pause_button->setFixedSize(64, 64);
					play_pause_button->setIconSize(QSize(52, 52));
					play_pause_button->setFlat(true);
					play_pause_button->setStyleSheet(buttons_stylesheet);
					QObject::connect(play_pause_button, &QPushButton::released, [&]() {
						if (play_pause_button->property("active").toInt()) {
							play_pause_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/play.png"));
							pause(true);
							play_pause_button->setProperty("active", 0);
						}
						else {
							play_pause_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/pause.png"));
							pause(false);
							play_pause_button->setProperty("active", 1);
						}

					});

					buttons_layout->addWidget(forward_button);
					forward_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/forward.png"));
					forward_button->setFixedSize(64, 48);
					forward_button->setIconSize(QSize(52, 36));
					forward_button->setFlat(true);
					forward_button->setStyleSheet(buttons_stylesheet);
					QObject::connect(forward_button, &QPushButton::released, [&]() {
						if (m_MusicPlaylist) {
							setPosition(position() + 2000);
						}
					});

					buttons_layout->addWidget(next_button);
					next_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/next.png"));
					next_button->setFixedSize(64, 48);
					next_button->setIconSize(QSize(52, 36));
					next_button->setFlat(true);
					next_button->setStyleSheet(buttons_stylesheet);
					QObject::connect(next_button, &QPushButton::released, [&]() {
						if (m_MusicPlaylist) {
							m_MusicPlaylist->next();
							play();
						}
					});
				}

				buttons_layout->addSpacing(3);
				buttons_layout->addWidget(separator_volume_frame);
				separator_volume_frame->setFrameShape(QFrame::Shape::VLine);
				separator_volume_frame->setStyleSheet(""
					"QFrame{"
					"	background-color: #aaaaaa"
					"}"
				);
				buttons_layout->addSpacing(3);

				//VOLUME SLIDER & MUTE VOLUME
				{
					buttons_layout->addWidget(volume_mute_button);
					volume_mute_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/audio_muted.png"));
					volume_mute_button->setFixedSize(64, 48);
					volume_mute_button->setIconSize(QSize(52, 36));
					volume_mute_button->setFlat(true);
					volume_mute_button->setStyleSheet(buttons_stylesheet);
					volume_mute_button->setProperty("active", false);
					QObject::connect(volume_mute_button, &QPushButton::released, [&]() {
						if (m_MusicPlaylist) {
							if (volume_mute_button->property("active").toBool()) {
								volume_slider->setMaximum(1000);
								volume_slider->setValue(m_SaveVolume*1000);
								setMuted(false);
								volume_mute_button->setProperty("active", false);
							}
							else {
								volume_mute_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/audio_muted.png"));
								m_SaveVolume = volume();
								volume_slider->setMaximum(0);
								volume_slider->setValue(0);
								setMuted(true);
								volume_mute_button->setProperty("active", true);
							}
							
						}
					});

					buttons_layout->addWidget(volume_slider);
					volume_slider->setOrientation(Qt::Orientation::Horizontal);
					QObject::connect(volume_slider, &MusicSlider::valueChanged, [=](int value) {
						setVolume(value / 1000.0);
						if (value > 750) {
							volume_mute_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/audio_100.png"));
						}
						else if (value > 500) {
							volume_mute_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/audio_75.png"));
						}
						else if (value > 250) {
							volume_mute_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/audio_50.png"));
						}
						else if (value > 0) {
							volume_mute_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/audio_25.png"));
						}
						else {
							volume_mute_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/audio_muted.png"));
						}
					});
					volume_slider->setMinimum(0);
					volume_slider->setMaximum(1000);
					volume_slider->setMaximumWidth(100);
					volume_slider->setValue(volume()*volume_slider->maximum());
					volume_slider->setStyleSheet(
						"QSlider::right-arrow:horizontal, QSlider::left-arrow:horizontal {"
						"	border: none;"
						"	background: none;"
						"	color: none;"
						"}"
					);
				}

				buttons_layout->addSpacing(3);
				buttons_layout->addWidget(separator_playlist_buttons_frame);
				separator_playlist_buttons_frame->setFrameShape(QFrame::Shape::VLine);
				separator_playlist_buttons_frame->setStyleSheet(""
					"QFrame{"
					"	background-color: #aaaaaa"
					"}"
				);
				buttons_layout->addSpacing(3);

				//PLAYLIST CONTROL
				{
					buttons_layout->addWidget(playlist_show_hide_button);
					playlist_show_hide_button->setIcon(QIcon(u8":/SystemAddonsPopup/icons/music_control/audio_muted.png"));
					playlist_show_hide_button->setFixedSize(64, 48);
					playlist_show_hide_button->setIconSize(QSize(52, 36));
					playlist_show_hide_button->setFlat(true);
					playlist_show_hide_button->setStyleSheet(buttons_stylesheet);
					playlist_show_hide_button->setProperty("active", false);
					QObject::connect(playlist_show_hide_button, &QPushButton::released, [&]() {
							if (playlist_show_hide_button->property("active").toBool()) {
								emit hidePlaylist();
								playlist_show_hide_button->setProperty("active", false);
							}
							else {
								emit showPlaylist();
								playlist_show_hide_button->setProperty("active", true);
							}
					});
				}
			}
		}

		this->setLayout(root_layout);
	}
	//WIDGET INITIALIZATION
	{
		this->setAcceptDrops(true);
	}
	//PLAYLIST STATE MACHINE
	{
		playlist_state_machine = new QStateMachine(this);

		QState *hide_state = new QState(playlist_state_machine);
		hide_state->assignProperty(this, "playlistShowPercent", QSize(0,0));
		playlist_state_machine->setInitialState(hide_state);

		QState *show_state = new QState(playlist_state_machine);
		show_state->assignProperty(this, "playlistShowPercent", QSize(200, 800));

		QPropertyAnimation* prop_anim = new QPropertyAnimation(this, "playlistShowPercent");
		prop_anim->setEasingCurve(QEasingCurve::OutSine);
		prop_anim->setDuration(500);

		QSignalTransition *hide_to_show_transition = hide_state->addTransition(this, &MusicPlayer::showPlaylist, show_state);
		hide_to_show_transition->addAnimation(prop_anim);

		QSignalTransition *show_to_hide_transition = show_state->addTransition(this, &MusicPlayer::hidePlaylist, hide_state);
		show_to_hide_transition->addAnimation(prop_anim);

		playlist_state_machine->start();
	}
	//CREATE PLAYLIST
	{
		m_MusicPlaylist = new MusicPlaylist();
		m_MusicPlaylist->addMusic(data_manager->getPlaylist());
		m_MusicPlaylist->setPlaybackMode(MusicPlaylist::PlaybackMode::Sequential);

		playlist_music_selector->clear();
		QList<QString> names = m_MusicPlaylist->musicNames();
		for (QString& name : names) {
			name = QFileInfo(name).fileName();
			playlist_music_selector->addItem(name.mid(0, name.lastIndexOf('.')));
		}

		QObject::connect(this, &MusicPlayer::musicAdded, [=]() {
			data_manager->setPlaylist(m_MusicPlaylist->musicNames());
			data_manager->saveData();

			playlist_music_selector->clear();
			QList<QString> names = m_MusicPlaylist->musicNames();
			for (QString& name : names) {
				name = QFileInfo(name).fileName();
				playlist_music_selector->addItem(name.mid(0, name.lastIndexOf('.')));
			}
		});
		QObject::connect(this, &MusicPlayer::musicRemoved, [=]() {
			data_manager->setPlaylist(m_MusicPlaylist->musicNames());
			data_manager->saveData();

			playlist_music_selector->clear();
			QList<QString> names = m_MusicPlaylist->musicNames();
			for (QString& name : names) {
				name = QFileInfo(name).fileName();
				playlist_music_selector->addItem(name.mid(0, name.lastIndexOf('.')));
			}
		});
	}
}

MusicPlayer::~MusicPlayer()
{
	delete m_MainChannel;
	delete m_MainChannelGroup;
	delete m_MusicSystem;
}

void MusicPlayer::init()
{
	//MUSIC SYSTEM INITIALIZATION
	{
		FMOD::System_Create(&m_MusicSystem);
		m_MusicSystem->init(32, FMOD_INIT_NORMAL, NULL);
	}
	//GETTING MASTER CHANNEL GROUP
	{
		m_MusicSystem->getMasterChannelGroup(&m_MainChannelGroup);
	}
	//REFRESHER TIMER
	{
		refresh_callback_timer = new QTimer();
		QObject::connect(refresh_callback_timer, &QTimer::timeout, [&]() {
			emit positionChanged(position());
			if (this->isVisible()) {
				if (position() >= duration()) {
					if (m_MusicPlaylist) {
						switch (m_MusicPlaylist->playbackMode()) {
						case MusicPlaylist::PlaybackMode::CurrentItemOnce:
							stop();
							break;
						case MusicPlaylist::PlaybackMode::CurrentItemInLoop:
							play();
							break;
						case MusicPlaylist::PlaybackMode::Loop:
						default:
							m_MusicPlaylist->next();
							play();
							break;
						case MusicPlaylist::PlaybackMode::Sequential:
							if (m_MusicPlaylist->currentIndex() != m_MusicPlaylist->musicCount() - 1) {
								m_MusicPlaylist->next();
								play();
							}
							else {
								stop();
							}
							break;
						case MusicPlaylist::PlaybackMode::Random:
							m_MusicPlaylist->next();
							play();
							break;
						}
						emit currentMusicChanged(m_MusicPlaylist->currentMusicName());
						emit currentMusicChanged(m_MusicPlaylist->currentIndex());
					}
				}
			}
		});
		refresh_callback_timer->start(20);
	}
}

QSize MusicPlayer::playlistShowPercent()
{
	return expectedSize;
}

void MusicPlayer::setPlaylistShowPercent(const QSize & size)
{
	expectedSize = size;
	playlist_music_selector->setMaximumSize(size);
}

void MusicPlayer::attachVisualiser()
{
	music_visualiser->setVisible(true);
}

void MusicPlayer::detachVisualiser()
{
	music_visualiser->setVisible(false);
}

MusicVisualiser * MusicPlayer::visualiser()
{
	return music_visualiser;
}

MusicPlaylist * MusicPlayer::playlist()
{
	return m_MusicPlaylist;
}

bool MusicPlayer::addMusic(const QString & music)
{
	if (m_MusicPlaylist) {
		if (m_MusicPlaylist->addMusic(music)) {
			emit musicAdded();
			return true;
		}
		return false;
	}
	return false;
}

bool MusicPlayer::addMusic(const QList<QString>& music)
{
	if (m_MusicPlaylist) {
		if (m_MusicPlaylist->addMusic(music)) {
			emit musicAdded();
			return true;
		}
		return false;
	}
	return false;
}

bool MusicPlayer::insertMusic(int pos, const QString & music)
{
	if (m_MusicPlaylist) {
		if (m_MusicPlaylist->insertMusic(pos, music)) {
			emit musicAdded();
			return true;
		}
		return false;
	}
	return false;
}

bool MusicPlayer::insertMusic(int pos, const QList<QString>& music)
{
	if (m_MusicPlaylist) {
		if (m_MusicPlaylist->insertMusic(pos, music)) {
			emit musicAdded();
			return true;
		}
		return false;
	}
	return false;
}

void MusicPlayer::removeMusic(int pos)
{
	if (m_MusicPlaylist) {
		m_MusicPlaylist->removeMusic(pos);
		emit musicRemoved();
	}
}

void MusicPlayer::removeMusic(int from, int to)
{
	if (m_MusicPlaylist) {
		m_MusicPlaylist->removeMusic(from, to);
		emit musicRemoved();
	}
}

QString MusicPlayer::currentMusic()
{
	if (m_MusicPlaylist) {
		return m_MusicPlaylist->currentMusicName();
	}
	return QString();
}

int MusicPlayer::currentMusicIndex()
{
	if (m_MusicPlaylist) {
		return m_MusicPlaylist->currentIndex();
	}
	return -1;
}

uint MusicPlayer::duration()
{
	uint length = 0;

	if (m_MusicPlaylist) {
		if (m_MusicPlaylist->currentMusic()) {
			FMOD::Sound* music = m_MusicPlaylist->currentMusic();

			music->getLength(&length, FMOD_TIMEUNIT_MS);
		}
	}

	return length;
}

bool MusicPlayer::isMuted()
{
	bool muted = false;
	m_MainChannelGroup->getMute(&muted);
	return muted;
}

uint MusicPlayer::position()
{
	uint position = 0;
	if (m_MainChannel) {
		m_MainChannel->getPosition(&position, FMOD_TIMEUNIT_MS);
	}
	return position;
}

float MusicPlayer::volume()
{
	float volume = 0;
	m_MainChannelGroup->getVolume(&volume);
	return volume;
}

MusicPlayer::MusicState MusicPlayer::state()
{
	bool is_paused = false;
	m_MainChannelGroup->getPaused(&is_paused);
	if (is_paused) {
		return MusicPlayer::MusicState::PausedState;
	}
	else {
		bool is_playing = false;
		m_MainChannelGroup->isPlaying(&is_playing);
		return is_playing ? MusicPlayer::MusicState::PlayingState : MusicPlayer::MusicState::StoppedState;
	}

	return MusicPlayer::MusicState::StoppedState;
}

MusicPlayer * MusicPlayer::getInstance()
{
	if (MusicPlayer::instance == NULL) {
		MusicPlayer::instance = new MusicPlayer();
	}
	return MusicPlayer::instance;
}

void MusicPlayer::dragEnterEvent(QDragEnterEvent * event)
{
	if (event->mimeData()->hasUrls())event->acceptProposedAction();
}

void MusicPlayer::dropEvent(QDropEvent * event)
{
	if (m_MusicPlaylist) {
		for (int k = 0; k < event->mimeData()->urls().size(); k++) {
			if (m_MusicPlaylist->addMusic(event->mimeData()->urls()[k].toLocalFile())) {
				emit musicAdded();
			}
		}
	}
}

void MusicPlayer::closeEvent(QCloseEvent * event)
{
	event->setAccepted(false);
	this->stop();
	emit hiding();
	this->hide();
}

void MusicPlayer::pause(bool pause)
{
	m_MainChannelGroup->setPaused(pause);
	emit stateChanged(state());
}

void MusicPlayer::play()
{
	if (m_MainChannel) {
		m_MainChannel->stop();
		emit stateChanged(state());
		m_MainChannel = NULL;
	}

	if (m_MusicPlaylist) {
		if (m_MusicPlaylist->currentMusic()) {
			m_MusicSystem->playSound(m_MusicPlaylist->currentMusic(), m_MainChannelGroup, false, &m_MainChannel);
			emit stateChanged(state());
			emit currentMusicChanged(m_MusicPlaylist->currentMusicName());
			emit currentMusicChanged(m_MusicPlaylist->currentIndex());
			emit durationChanged(duration());
		}
		else {
			if (m_MusicPlaylist->m_MusicData.size() > 0) {
				if (m_MusicPlaylist->currentIndex() == -1) {
					m_MusicPlaylist->setCurrentIndex(qrand() % m_MusicPlaylist->m_MusicData.size());
				}

				if (!m_MusicPlaylist->currentMusic()) {
					m_MusicSystem->createStream(m_MusicPlaylist->m_MusicData[m_MusicPlaylist->currentIndex()].first.toUtf8(), FMOD_DEFAULT, 0, &m_MusicPlaylist->m_MusicData[m_MusicPlaylist->currentIndex()].second);
					if (!m_MusicPlaylist->m_MusicData[m_MusicPlaylist->currentIndex()].second) {
						emit loadingFailed(m_MusicPlaylist->m_MusicData[m_MusicPlaylist->currentIndex()].first);
					}
					else {
						m_MusicSystem->playSound(m_MusicPlaylist->m_MusicData[m_MusicPlaylist->currentIndex()].second, m_MainChannelGroup, false, &m_MainChannel);
						emit stateChanged(state());
						emit currentMusicChanged(m_MusicPlaylist->currentMusicName());
						emit currentMusicChanged(m_MusicPlaylist->currentIndex());
						emit durationChanged(duration());
					}
				}

			}
		}
	}
}

void MusicPlayer::play(int index)
{
	if (m_MusicPlaylist) {
		m_MusicPlaylist->setCurrentIndex(index);
		play();
	}
}

void MusicPlayer::play(const QString & music)
{
	int index = m_MusicPlaylist->contains(music);
	if (index == -1) {
		m_MusicPlaylist->addMusic(music);
		index = m_MusicPlaylist->contains(music);
	}

	if (index != -1)play(index);
}

void MusicPlayer::setMuted(bool muted)
{
	m_MainChannelGroup->setMute(muted);
	emit mutedChanged(muted);
}

void MusicPlayer::setPosition(uint position)
{
	if (m_MainChannel) {
		m_MainChannel->setPosition(position, FMOD_TIMEUNIT_MS);
		emit positionChanged(position);
	}
}

void MusicPlayer::setVolume(float volume)
{
	m_MainChannelGroup->setVolume(volume);

	emit volumeChanged(volume);
}

void MusicPlayer::stop()
{
	m_MainChannelGroup->stop();

	emit stateChanged(state());
}
