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
					pause_button = new QPushButton;
					next_button = new QPushButton;

					separator_volume_frame = new QFrame;

					volume_mute_button = new QPushButton;
					volume_slider = new MusicSlider;

					separator_layout_buttons_frame = new QFrame;

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
			playlist_music_selector->setSelectionMode(QAbstractItemView::SingleSelection);
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
				""
				""
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
				buttons_layout->setSpacing(1);
				buttons_layout->setAlignment(Qt::AlignmentFlag::AlignBottom | Qt::AlignmentFlag::AlignHCenter);

				buttons_layout->addWidget(random_button);
				random_button->setText("RNG");
				random_button->setFixedSize(20, 20);
				buttons_layout->addWidget(repeat_button);
				repeat_button->setText("REP");
				repeat_button->setFixedSize(20, 20);

				buttons_layout->addSpacing(3);
				buttons_layout->addWidget(separator_mode_frame);
				separator_mode_frame->setFrameShape(QFrame::Shape::VLine);
				buttons_layout->addSpacing(3);

				buttons_layout->addWidget(previous_button);
				previous_button->setText("<");
				previous_button->setFixedSize(20, 20);
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
				buttons_layout->addWidget(pause_button);
				pause_button->setText("P");
				pause_button->setFixedSize(20, 20);
				QObject::connect(pause_button, &QPushButton::released, [&]() {
					pause((state() == State::PausedState) ? false : true);
				});
				buttons_layout->addWidget(next_button);
				next_button->setText(">");
				next_button->setFixedSize(20, 20);
				QObject::connect(next_button, &QPushButton::released, [&]() {
					if (m_MusicPlaylist) {
						m_MusicPlaylist->next();
						play();
					}
				});
			}
		}

		this->setLayout(root_layout);
	}
	//WIDGET INITIALIZATION
	{
		this->setAcceptDrops(true);
		this->setMaximumWidth((double)QApplication::screens()[QApplication::desktop()->primaryScreen()]->availableSize().width() / 2);
	}
	//DATA MANAGER
	{
		data_manager = DataManager::getInstance();
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

			if (position() >= duration()) {
				if (m_MusicPlaylist) {
					m_MusicPlaylist->next();
					play();
					emit currentMusicChanged(m_MusicPlaylist->currentMusicName());
					emit currentMusicChanged(m_MusicPlaylist->currentIndex());
				}
			}
		});
		refresh_callback_timer->start(20);
	}
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

MusicPlayer::State MusicPlayer::state()
{
	bool is_paused = false;
	m_MainChannelGroup->getPaused(&is_paused);
	if (is_paused) {
		return MusicPlayer::State::PausedState;
	}
	else {
		bool is_playing = false;
		m_MainChannelGroup->isPlaying(&is_playing);
		return is_playing ? MusicPlayer::State::PlayingState : MusicPlayer::State::StoppedState;
	}

	return MusicPlayer::State::StoppedState;
}

MusicPlayer * MusicPlayer::getInstance()
{
	if (MusicPlayer::instance == NULL) {
		MusicPlayer::instance = new MusicPlayer();
	}
	return MusicPlayer::instance;
}

void MusicPlayer::resizeEvent(QResizeEvent * event)
{
	this->setMinimumWidth(qMin(event->size().height() / 9.0*32.0, (double)QApplication::screens()[QApplication::desktop()->primaryScreen()]->availableSize().width() / 2));
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
	m_MainChannel->stop();

	emit stateChanged(state());
}
