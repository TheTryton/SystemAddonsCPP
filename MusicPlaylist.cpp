#include "MusicPlaylist.h"

#include <QFileInfo>
#include <QTime>

MusicPlaylist::MusicPlaylist(QObject *parent)
	: QObject(parent)
{
	qsrand(QTime::currentTime().elapsed());
}

MusicPlaylist::~MusicPlaylist()
{
	for (auto& data : m_MusicData) {
		delete data.second;
	}
}

bool MusicPlaylist::addMusic(const QString & music)
{
	if (contains(music)!=-1)return false;

	if (QFileInfo(music).exists()) {
		m_MusicData.append(QPair<QString,FMOD::Sound*>(music,nullptr));
		emit playlistChanged();
		return true;
	}
	return false;
}

bool MusicPlaylist::addMusic(const QList<QString>& allMusic)
{
	bool all_music_loaded = true;

	for (const QString& music : allMusic) {
		if (QFileInfo(music).exists() && (contains(music)==-1)) {
			m_MusicData.append(QPair<QString, FMOD::Sound*>(music, nullptr));
		}
		else {
			all_music_loaded = false;
		}
	}
	
	if (all_music_loaded) {
		emit playlistChanged();
	}

	return all_music_loaded;
}

void MusicPlaylist::clear()
{
	for (auto& music_stream : m_MusicData) {
		if (music_stream.second != NULL) {
			music_stream.second->release();
		}
	}
	m_MusicData.clear();
}

int MusicPlaylist::currentIndex() const
{
	return m_CurrentIndex;
}

QString MusicPlaylist::currentMusicName() const
{
	if (m_CurrentIndex >= 0 && m_CurrentIndex < m_MusicData.size()) {
		return m_MusicData[m_CurrentIndex].first;
	}
	else {
		return QString();
	}
}

FMOD::Sound * MusicPlaylist::currentMusic() const
{
	if (m_CurrentIndex >= 0 && m_CurrentIndex < m_MusicData.size()) {
		return m_MusicData[m_CurrentIndex].second;
	}
	else {
		return nullptr;
	}
}

bool MusicPlaylist::insertMusic(int pos, const QString & music)
{
	if (contains(music)!=-1)return false;

	if (QFileInfo(music).exists()) {
		m_MusicData.insert(pos, QPair<QString, FMOD::Sound*>(music, nullptr));
		emit playlistChanged();
		return true;
	}

	if (m_CurrentIndex > pos) {
		m_CurrentIndex++;

		emit currentIndexChanged(m_CurrentIndex);
		if (m_CurrentIndex != -1) {
			emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
			emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
		}
	}

	return false;
}

bool MusicPlaylist::insertMusic(int pos, const QList<QString>& music_list)
{
	bool all_music_loaded = true;
	int index = 0;

	for (const QString& music : music_list) {
		if (QFileInfo(music).exists() && (contains(music) == -1)) {
			m_MusicData.insert(pos+index, QPair<QString, FMOD::Sound*>(music, nullptr));
			index++;
		}
		else {
			all_music_loaded = false;
		}
	}

	if (m_CurrentIndex > pos) {

		m_CurrentIndex += index + 1;

		emit currentIndexChanged(m_CurrentIndex);
		if (m_CurrentIndex != -1) {
			emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
			emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
		}
	}

	if(all_music_loaded)emit playlistChanged();

	return all_music_loaded;
}

bool MusicPlaylist::isEmpty() const
{
	return m_MusicData.size();
}

QString MusicPlaylist::musicName(int index) const
{
	if (index >= 0 && index < m_MusicData.size()) {
		return m_MusicData[index].first;
	}
	else {
		return QString();
	}
}

QList<QString> MusicPlaylist::musicNames() const
{
	QList<QString> names;
	names.reserve(m_MusicData.size());
	for (auto& music : m_MusicData) {
		names.append(music.first);
	}
	return names;
}

FMOD::Sound* MusicPlaylist::music(int index) const
{
	if (index >= 0 && index < m_MusicData.size()) {
		return m_MusicData[index].second;
	}
	else {
		return nullptr;
	}
}

QList<FMOD::Sound*> MusicPlaylist::musicList() const
{
	QList<FMOD::Sound*> music_pointers;
	music_pointers.reserve(m_MusicData.size());
	for (auto& music : m_MusicData) {
		music_pointers.append(music.second);
	}
	return music_pointers;
}

int MusicPlaylist::musicCount() const
{
	return m_MusicData.size();
}

bool MusicPlaylist::moveMusic(int from, int to)
{
	if (from >= 0 && from < m_MusicData.size() &&
		to >= 0 && to < m_MusicData.size()) {
		m_MusicData.swap(from, to);

		if (m_CurrentIndex == from) {
			m_CurrentIndex = to;

			emit currentIndexChanged(m_CurrentIndex);
			if (m_CurrentIndex != -1) {
				emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
				emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
			}
		}
		return true;
	}
	else {
		return false;
	}
}

int MusicPlaylist::nextIndex(int steps)
{
	if (m_MusicData.size() != 0) {
		for (int i = 0; i < steps; i++) {
			switch (m_PlaybackMode) {
			case PlaybackMode::CurrentItemOnce:
				m_CurrentIndex = -1;
				break;
			case PlaybackMode::CurrentItemInLoop:
				m_CurrentIndex = (m_CurrentIndex + 1) % m_MusicData.size();
				break;
			case PlaybackMode::Sequential:
			default:
				if (m_CurrentIndex + 1 >= m_MusicData.size()) {
					m_CurrentIndex = -1;
				}
				else {
					m_CurrentIndex++;
				}
				break;
			case PlaybackMode::Loop:
				m_CurrentIndex = (m_CurrentIndex + 1) % m_MusicData.size();
				break;
			case PlaybackMode::Random:
				m_CurrentIndex = (m_CurrentIndex + qrand()) % m_MusicData.size();
				break;
			}
		}

		emit currentIndexChanged(m_CurrentIndex);
		if (m_CurrentIndex != -1) {
			emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
			emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
		}
	}

	return m_CurrentIndex;
}

MusicPlaylist::PlaybackMode MusicPlaylist::playbackMode() const
{
	return m_PlaybackMode;
}

int MusicPlaylist::previousIndex(int steps)
{
	if (m_MusicData.size() != 0) {
		for (int i = 0; i < steps; i++) {
			switch (m_PlaybackMode) {
			case PlaybackMode::CurrentItemOnce:
				break;
			case PlaybackMode::CurrentItemInLoop:
				m_CurrentIndex = (m_CurrentIndex - 1) % m_MusicData.size();
				if (m_CurrentIndex < 0)m_CurrentIndex += m_MusicData.size();
				break;
			case PlaybackMode::Sequential:
			default:
				if (m_CurrentIndex - 1 < 0) {
					m_CurrentIndex = 0;
				}
				else {
					m_CurrentIndex--;
				}
				break;
			case PlaybackMode::Loop:
				m_CurrentIndex = (m_CurrentIndex - 1) % m_MusicData.size();
				if (m_CurrentIndex < 0)m_CurrentIndex += m_MusicData.size();
				break;
			case PlaybackMode::Random:
				m_CurrentIndex = (m_CurrentIndex - qrand()) % m_MusicData.size();
				if (m_CurrentIndex < 0)m_CurrentIndex += m_MusicData.size();
				break;
			}
		}

		emit currentIndexChanged(m_CurrentIndex);
		if (m_CurrentIndex != -1) {
			emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
			emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
		}
	}

	return m_CurrentIndex;
}

bool MusicPlaylist::removeMusic(int pos)
{
	if (pos >= 0 && pos < m_MusicData.size()) {
		m_MusicData.removeAt(pos);
		if (m_CurrentIndex == pos) {
			if (m_MusicData.size()>0)m_CurrentIndex = 0;
			else m_CurrentIndex = -1;

			emit currentIndexChanged(m_CurrentIndex);
			if (m_CurrentIndex != -1) {
				emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
				emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
			}
		}
		emit playlistChanged();
		return true;
	}
	else {
		return false;
	}
}

bool MusicPlaylist::removeMusic(int start, int end)
{
	if (start >= 0 && start < m_MusicData.size()) {
		for (int i = start; i <= end; i++) {
			if (m_MusicData[i].second) {
				delete m_MusicData[i].second;
			}
		}
		m_MusicData.erase(m_MusicData.begin() + start, m_MusicData.begin() + end);
		if (m_CurrentIndex > start && m_CurrentIndex < end) {
			if (m_MusicData.size()>0)m_CurrentIndex = 0;
			else m_CurrentIndex = -1;

			emit currentIndexChanged(m_CurrentIndex);
			if (m_CurrentIndex != -1) {
				emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
				emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
			}
		}
		emit playlistChanged();
		return true;
	}
	else {
		return false;
	}
}

void MusicPlaylist::setPlaybackMode(PlaybackMode mode)
{
	m_PlaybackMode = mode;
}

int MusicPlaylist::contains(const QString & music)
{
	for (int i = 0; i < m_MusicData.size();i++) {
		if (m_MusicData[i].first == music) {
			return i;
		}
	}
	return -1;
}

void MusicPlaylist::next()
{
	if (m_MusicData.size() != 0) {
		switch (m_PlaybackMode) {
		case PlaybackMode::CurrentItemOnce:
			m_CurrentIndex = -1;
			break;
		case PlaybackMode::CurrentItemInLoop:
			m_CurrentIndex = (m_CurrentIndex + 1) % m_MusicData.size();
			break;
		case PlaybackMode::Sequential:
		default:
			if (m_CurrentIndex + 1 >= m_MusicData.size()) {
				m_CurrentIndex = -1;
			}
			else {
				m_CurrentIndex++;
			}
			break;
		case PlaybackMode::Loop:
			m_CurrentIndex = (m_CurrentIndex + 1) % m_MusicData.size();
			break;
		case PlaybackMode::Random:
			m_CurrentIndex = (m_CurrentIndex + qrand()) % m_MusicData.size();
			break;
		}

		emit currentIndexChanged(m_CurrentIndex);
		if (m_CurrentIndex != -1) {
			emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
			emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
		}
	}
}

void MusicPlaylist::previous()
{
	if (m_MusicData.size() != 0) {
		switch (m_PlaybackMode) {
		case PlaybackMode::CurrentItemOnce:
			break;
		case PlaybackMode::CurrentItemInLoop:
			m_CurrentIndex = (m_CurrentIndex - 1) % m_MusicData.size();
			if (m_CurrentIndex < 0)m_CurrentIndex += m_MusicData.size();
			break;
		case PlaybackMode::Sequential:
		default:
			if (m_CurrentIndex - 1 < 0) {
				m_CurrentIndex = 0;
			}
			else {
				m_CurrentIndex--;
			}
			break;
		case PlaybackMode::Loop:
			m_CurrentIndex = (m_CurrentIndex - 1) % m_MusicData.size();
			if (m_CurrentIndex < 0)m_CurrentIndex += m_MusicData.size();
			break;
		case PlaybackMode::Random:
			m_CurrentIndex = (m_CurrentIndex - qrand()) % m_MusicData.size();
			if (m_CurrentIndex < 0)m_CurrentIndex += m_MusicData.size();
			break;
		}

		emit currentIndexChanged(m_CurrentIndex);
		if (m_CurrentIndex != -1) {
			emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
			emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
		}
	}
}

void MusicPlaylist::setCurrentIndex(int pos)
{
	if (pos >= 0 && pos < m_MusicData.size()) {
		m_CurrentIndex = pos;
		emit currentIndexChanged(m_CurrentIndex);
		if (m_CurrentIndex != -1) {
			emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
			emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
		}
	}
}

void MusicPlaylist::shuffle()
{
	std::random_shuffle(m_MusicData.begin(), m_MusicData.end());
}
