#pragma once

#include <QObject>
#include <QString>
#include <FMOD\fmod.hpp>

class MusicPlaylist : public QObject
{
	Q_OBJECT
public:
	friend class MusicPlayer;
private:
	MusicPlaylist(QObject *parent = Q_NULLPTR);
	~MusicPlaylist();
public:
	enum class PlaybackMode {
		CurrentItemOnce,
		CurrentItemInLoop,
		Sequential,
		Loop,
		Random
	};
public:
	bool addMusic(const QString& music);
	bool addMusic(const QList<QString>& music_list);
	void clear();
	int currentIndex() const;
	QString currentMusicName() const;
	FMOD::Sound* currentMusic() const;
	bool insertMusic(int pos, const QString& music);
	bool insertMusic(int pos, const QList<QString>& music_list);
	bool isEmpty() const;
	QString musicName(int index) const;
	QList<QString> musicNames() const;
	FMOD::Sound* music(int index) const;
	QList<FMOD::Sound*> musicList() const;
	int musicCount() const;
	bool moveMusic(int from, int to);
	int nextIndex(int steps = 1);
	PlaybackMode playbackMode() const;
	int previousIndex(int steps = 1);
	bool removeMusic(int pos);
	bool removeMusic(int start, int end);
	void setPlaybackMode(PlaybackMode mode);

	int contains(const QString& music);
private:
	QList<QPair<QString, FMOD::Sound*>> m_MusicData;
	int m_CurrentIndex = -1;
	PlaybackMode m_PlaybackMode = PlaybackMode::Sequential;
public slots:
	void next();
	void previous();
	void setCurrentIndex(int pos);
	void shuffle();
signals:
	void currentIndexChanged(int position);
	void currentMusicNameChanged(const QString &musicName);
	void currentMusicChanged(FMOD::Sound* music);
	void playlistChanged();
};
