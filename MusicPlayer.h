#pragma once

#include <QtWidgets>
#include <time.h>
#include <FMOD\fmod.hpp>

#include "MusicPlaylist.h"
#include "MusicVisualiser.h"
#include "MusicSlider.h"
#include "MusicPlaylistWidget.h"

#include "DataManager.h"

class MusicVisualizerItem;

class MusicPlayer : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QSize playlistShowPercent READ playlistShowPercent WRITE setPlaylistShowPercent)
	friend class SystemAddonsPopup;
	friend class MusicVisualiser;
public:
	static MusicPlayer* getInstance();
private:
	static MusicPlayer* instance;
private:
	MusicPlayer(QWidget * parent = Q_NULLPTR);
	~MusicPlayer();
public:
	enum class MusicState {
		StoppedState,
		PlayingState,
		PausedState
	};
public:
	void attachVisualiser();
	void detachVisualiser();
	MusicVisualiser* visualiser();

	MusicPlaylist* playlist();

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
	MusicState state();
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
	void stateChanged(MusicState	 state);
	void durationChanged(uint duration);
	void currentMusicChanged(const QString& currentMusic);
	void currentMusicChanged(int index);
	void loadingFailed(const QString&  music);
	void musicAdded();
	void musicRemoved();

	void hiding();

	void hidePlaylist();
	void showPlaylist();
protected:
	virtual void dragEnterEvent(QDragEnterEvent* event) override;
	virtual void dropEvent(QDropEvent* event) override;

	virtual void closeEvent(QCloseEvent* event) override;
private:
	void init();
	QSize playlistShowPercent();
	void setPlaylistShowPercent(const QSize& size);
private:
	FMOD::System* m_MusicSystem = NULL;
	FMOD::ChannelGroup* m_MainChannelGroup = NULL;
	FMOD::Channel* m_MainChannel = NULL;

	bool m_ShouldStop = false;

	MusicPlaylist* m_MusicPlaylist = NULL;
private:
	QVBoxLayout* root_layout = NULL;

	QHBoxLayout* playlist_visualiser_layout = NULL;

	QSize m_PlaylistShowPercent = QSize(0, 0);
	QListWidget* playlist_music_selector = NULL;
	
	MusicVisualiser* music_visualiser = NULL;

	QVBoxLayout* bottom_layout = NULL;

	MusicSlider* position_slider = NULL;

	QHBoxLayout* buttons_layout = NULL;

	QPushButton* random_button = NULL;
	QPushButton* repeat_button = NULL;

	QFrame* separator_mode_frame = NULL;

	QPushButton* previous_button = NULL;
	QPushButton* backward_button = NULL;
	QPushButton* play_pause_button = NULL;
	QPushButton* forward_button = NULL;
	QPushButton* next_button = NULL;

	QFrame* separator_volume_frame = NULL;

	QPushButton* volume_mute_button = NULL;
	float m_SaveVolume = 0;
	MusicSlider* volume_slider = NULL;

	QFrame* separator_playlist_buttons_frame = NULL;

	QPushButton* playlist_remove_button = NULL;
	QPushButton* playlist_clear_button = NULL;
	QPushButton* playlist_show_hide_button = NULL;
	QSize expectedSize = QSize(0, 0);
	QStateMachine* playlist_state_machine = NULL;

	QTimer* refresh_callback_timer = NULL;
	//DATA MANAGER POINTER
	DataManager* data_manager = NULL;
};