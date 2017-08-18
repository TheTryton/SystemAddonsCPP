#pragma once

#include <QtWidgets>
#include <time.h>
#include <FMOD\fmod.hpp>

#include "MusicPlaylist.h"
#include "MusicVisualiser.h"
#include "MusicSlider.h"

#include "DataManager.h"

class MusicVisualizerItem;

class MusicPlayer : public QWidget
{
	Q_OBJECT
	friend class SystemAddonsPopup;
	friend class MusicVisualiser;
public:
	static MusicPlayer* getInstance();
private:
	static MusicPlayer* instance;
private:
	MusicPlayer(QWidget * parent = Q_NULLPTR);
	~MusicPlayer();
private:
	void init();
public:
	enum class State {
		StoppedState,
		PlayingState,
		PausedState
	};
public:
	void attachVisualiser();
	void detachVisualiser();
	MusicVisualiser* visualiser();

	MusicPlaylist* playlist();
	void setPlaylist(MusicPlaylist* playlist);

	bool addMusic(const QString& music);
	bool addMusic(const QList<QString>& music);
	bool insertMusic(int pos, const QString& music);
	bool insertMusic(int pos, const QList<QString>& music);
	void removeMusic(int pos);
	void removeMusic(int from, int to);
	QString currentMusic();
	int currentMusicIndex();
	uint duration();
	bool isMuted();
	uint position();
	float volume();
	State state();
public slots:
	void pause(bool pause);
	void play();
	void play(int index);
	void play(const QString& music);
	void setMuted(bool muted);
	void setPosition(uint position);
	void setVolume(float volume);
	void stop();
signals:
	void positionChanged(uint position);
	void mutedChanged(bool muted);
	void volumeChanged(int volume);
	void stateChanged(State state);
	void durationChanged(uint duration);
	void currentMusicChanged(const QString& currentMusic);
	void currentMusicChanged(int index);
	void loadingFailed(const QString&  music);
	void musicAdded();
	void musicRemoved();
protected:
	void resizeEvent(QResizeEvent *event) override;
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;
private:
	FMOD::System* m_MusicSystem = NULL;
	FMOD::ChannelGroup* m_MainChannelGroup = NULL;
	FMOD::Channel* m_MainChannel = NULL;

	MusicPlaylist* m_MusicPlaylist = NULL;
private:
	QVBoxLayout* root_layout = NULL;

	QHBoxLayout* playlist_visualiser_layout = NULL;

	QListWidget* playlist_music_selector = NULL;
	
	MusicVisualiser* music_visualiser = NULL;

	QVBoxLayout* bottom_layout = NULL;

	MusicSlider* position_slider = NULL;

	QHBoxLayout* buttons_layout = NULL;

	QPushButton* random_button = NULL;
	QPushButton* repeat_button = NULL;

	QFrame* separator_mode_frame = NULL;

	QPushButton* previous_button = NULL;
	QPushButton* pause_button = NULL;
	QPushButton* next_button = NULL;

	QFrame* separator_volume_frame = NULL;

	QPushButton* volume_mute_button = NULL;
	float m_SaveVolume = 0;
	MusicSlider* volume_slider = NULL;

	QFrame* separator_layout_buttons_frame = NULL;

	QPushButton* playlist_remove_button = NULL;
	QPushButton* playlist_clear_button = NULL;
	QPushButton* playlist_show_hide_button = NULL;

	QTimer* refresh_callback_timer = NULL;
	//DATA MANAGER POINTER
	DataManager* data_manager = NULL;
};