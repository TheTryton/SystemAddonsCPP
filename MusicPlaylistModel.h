#pragma once


#include <QAbstractItemModel>
#include <FMOD\fmod.hpp>
#include <QString>
#include <QTimer>
#include <memory>

class MusicPlaylistModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	MusicPlaylistModel(QAbstractItemModel *parent = Q_NULLPTR);
	~MusicPlaylistModel();
public:
	enum class PlaybackMode {
		CurrentItemOnce,
		CurrentItemInLoop,
		Sequential,
		Loop,
		Random
	};

	enum class MusicState {
		StoppedState,
		PlayingState,
		PausedState
	};
public:
	//QAbstractItemModel
	virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;
	virtual Qt::ItemFlags flags(const QModelIndex & index) const override;

	virtual QModelIndex parent(const QModelIndex &index) const override;
	virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
public:
	//MusicPlaylistModel

	//ADDING AND REMOVING
	bool addMusic(const QString& music);
	bool addMusic(const QList<QString>& music_list);

	bool insertMusic(int pos, const QString& music);
	bool insertMusic(int pos, const QList<QString>& music_list);

	bool removeMusic(int pos);
	bool removeMusic(int start, int end);

	void clear();

	//CURRENTLY PLAYED MUSIC
	QModelIndex currentIndex() const;
	QString currentMusicName() const;
	const FMOD::Sound* currentMusic() const;
	
	//MUSIC DATA INFO
	bool isEmpty() const;
	int contains(const QString& music);

	int musicCount() const;

	QString musicName(int index) const;
	QList<QString> musicNames() const;
	FMOD::Sound* music(int index) const;
	QList<FMOD::Sound*> musicList() const;
	
	//DATA MANIPULATION
	bool moveMusic(int from, int to);
	
	//PLAYBACK MODE MANIPULATION
	void setPlaybackMode(PlaybackMode mode);
	PlaybackMode playbackMode() const;

	//CURRENTLY PLAYED MUSIC MANIPULATION
	int previousIndex(int steps = 1);
	int nextIndex(int steps = 1);
	
	//CURRENTLY PLAYED MUSIC INFO
	uint currentMusicTimePosition();
	void setCurrentMusicTimePosition();
	uint currentMusicDuration();

	bool isMuted();
	float volume();
	MusicState state();
public slots:
	//MUSIC PLAYBACK CONTROL
	void pause(bool pause);
	void play();
	void play(int index);
	void play(const QString& music);
	void setMuted(bool muted);
	void setCurrentMusicTimePosition(uint position);
	void setVolume(float volume);
	void stop();

	//CURRENTLY PLAYED MUSIC MANIPULATION
	void next();
	void previous();
	void setCurrentIndex(int pos);

	//DATA MANIPULATION
	void shuffle();
private:
	//MUSIC SYSTEM
	static std::shared_ptr<FMOD::System> sm_MusicSystem;
	std::shared_ptr<FMOD::System> m_MusicSystem = NULL;

	FMOD::ChannelGroup* m_MainChannelGroup = NULL;
	FMOD::Channel* m_MainChannel = NULL;

	//CURRENT MUSIC INFO
	QTimer* m_ChannelInfoRefresher = NULL;

	//PLAYBACK
	PlaybackMode m_PlaybackMode = PlaybackMode::Sequential;
	int m_CurrentIndex = -1;

	//DATA
	QVector<QPair<QString, FMOD::Sound*>> m_MusicData;
signals:
	void currentIndexChanged(int position);
	void currentMusicNameChanged(const QString &musicName);
	void currentMusicChanged(const FMOD::Sound* music);
	void currentMusicTimePositionChanged(uint position);
	
	void failedToLoadMusic(int row);

	void mutedChanged(bool muted);
	void volumeChanged(int volume);
	void stateChanged(MusicState state);
	void durationChanged(uint duration);

	void musicAdded(int row);
	void musicRemoved(const QString &musicName);
	void musicDataChanged();
};
