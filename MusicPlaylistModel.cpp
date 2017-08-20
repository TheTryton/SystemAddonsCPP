#include "MusicPlaylistModel.h"

std::shared_ptr<FMOD::System> MusicPlaylistModel::sm_MusicSystem = NULL;

MusicPlaylistModel::MusicPlaylistModel(QAbstractItemModel *parent)
	: QAbstractItemModel(parent)
{
	if (sm_MusicSystem.get() == NULL) {
		FMOD::System* system;
		FMOD::System_Create(&system);
		system->init(32, FMOD_INIT_NORMAL, NULL);

		sm_MusicSystem = std::shared_ptr<FMOD::System>(system, [](FMOD::System* system) {
			system->release();
		});
	}

	m_MusicSystem = sm_MusicSystem;
	m_MusicSystem->getMasterChannelGroup(&m_MainChannelGroup);

	m_ChannelInfoRefresher = new QTimer();
	QObject::connect(m_ChannelInfoRefresher, &QTimer::timeout, [&]() {
		emit this->currentMusicTimePositionChanged(currentMusicTimePosition());

		if (currentMusicTimePosition() >= currentMusicDuration()) {
			this->next();
			emit currentMusicNameChanged(currentMusicName());
			emit currentMusicChanged(currentMusic());
			emit currentIndexChanged(m_CurrentIndex);
		}
	});
	m_ChannelInfoRefresher->start(20);
}

MusicPlaylistModel::~MusicPlaylistModel()
{
	for (auto& data : m_MusicData) {
		if (data.second) {
			data.second->release();
			delete data.second;
		}
	}
}

int MusicPlaylistModel::rowCount(const QModelIndex & parent) const
{
	return m_MusicData.size();
}

int MusicPlaylistModel::columnCount(const QModelIndex & parent) const
{
	return 1;
}

QVariant MusicPlaylistModel::data(const QModelIndex & index, int role) const
{
	int row = index.row();
	int col = index.column();

	if (role == Qt::DisplayRole)
	{
		if (col == 0)
		{
			if (row >= 0 && row < m_MusicData.size()) 
			{
				return m_MusicData[row].first;
			}
		}
	}
	return QVariant();
}

bool MusicPlaylistModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	if (role == Qt::ItemDataRole::EditRole)
	{
		int row = index.row();
		int col = index.column();
		if (col == 0) {
			if (row >= 0 && row < m_MusicData.size())
			{
				if (value.toString() != m_MusicData[row].first) {
					if (m_MusicData[row].second)
					{
						m_MusicData[row].second->release();
						delete m_MusicData[row].second;
					}
					m_MusicData[row] = QPair<QString, FMOD::Sound*>(value.toString(), NULL);
					emit dataChanged(this->index(row, col), this->index(row, col), QVector<int>() = { role });
				}
				return true;
			}
		}
	}
	return false;
}

Qt::ItemFlags MusicPlaylistModel::flags(const QModelIndex & index) const
{
	return Qt::ItemFlag::ItemIsEnabled;
}

QModelIndex MusicPlaylistModel::parent(const QModelIndex & index) const
{
	return QModelIndex();
}

QModelIndex MusicPlaylistModel::index(int row, int column, const QModelIndex & parent) const
{
	if (!parent.isValid())
	{
		if (column == 0) 
		{
			if (row >= 0 && row < m_MusicData.size())
			{
				return createIndex(row, column,(void*)&m_MusicData[row]);
			}
		}
	}

	return QModelIndex();
}

bool MusicPlaylistModel::addMusic(const QString & music)
{
	if (contains(music) != -1)
	{
		return false;
	}
	m_MusicData.append(QPair<QString, FMOD::Sound*>(music, nullptr));
	emit musicAdded(m_MusicData.size() - 1);
	return true;
}

bool MusicPlaylistModel::addMusic(const QList<QString>& allMusic)
{
	for (const QString& music : allMusic)
	{
		this->addMusic(music);
	}

	return true;
}

void MusicPlaylistModel::clear()
{
	for (auto& music_stream : m_MusicData) 
	{
		if (music_stream.second) 
		{
			music_stream.second->release();
			delete music_stream.second;
			emit musicRemoved(music_stream.first);
		}
	}
	m_MusicData.clear();
}

QModelIndex MusicPlaylistModel::currentIndex() const
{
	return index(m_CurrentIndex,0);
}

QString MusicPlaylistModel::currentMusicName() const

{
	if (m_CurrentIndex >= 0 && m_CurrentIndex < m_MusicData.size()) 
	{
		return ((QPair<QString, FMOD::Sound*>*)index(m_CurrentIndex, 0).data().data())->first;
	}
	else
	{
		return QString();
	}
}

const FMOD::Sound * MusicPlaylistModel::currentMusic() const
{
	if (m_CurrentIndex >= 0 && m_CurrentIndex < m_MusicData.size()) 
	{
		return ((QPair<QString, FMOD::Sound*>*)index(m_CurrentIndex,0).data().data())->second;
	}
	else 
	{
		return nullptr;
	}
}

bool MusicPlaylistModel::insertMusic(int pos, const QString & music)
{
	if (contains(music) != -1)
	{
		return false;
	}
	m_MusicData.insert(pos, QPair<QString, FMOD::Sound*>(music, nullptr));
	emit musicAdded(pos);

	if (m_CurrentIndex > pos) 
	{
		m_CurrentIndex++;

		emit currentIndexChanged(m_CurrentIndex);
		if (m_CurrentIndex != -1) {
			emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
			emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
		}
	}

	return false;
}

bool MusicPlaylistModel::insertMusic(int pos, const QList<QString>& music_list)
{
	int helper_index = 0;

	for (const QString& music : music_list) 
	{
		if (contains(music) == -1) 
		{
			m_MusicData.insert(pos + helper_index, QPair<QString, FMOD::Sound*>(music, nullptr));
			helper_index++;
		}
	}

	if (m_CurrentIndex > pos) 
	{
		m_CurrentIndex += helper_index + 1;

		emit currentIndexChanged(m_CurrentIndex);
		if (m_CurrentIndex != -1) {
			emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
			emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
		}
	}

	return true;
}

bool MusicPlaylistModel::isEmpty() const
{
	return !m_MusicData.size();
}

QString MusicPlaylistModel::musicName(int index) const
{
	if (index >= 0 && index < m_MusicData.size()) 
	{
		return m_MusicData[index].first;
	}
	else 
	{
		return QString();
	}
}

QList<QString> MusicPlaylistModel::musicNames() const
{
	QList<QString> names;
	names.reserve(m_MusicData.size());
	for (auto& music : m_MusicData) 
	{
		names.append(music.first);
	}
	return names;
}

FMOD::Sound* MusicPlaylistModel::music(int index) const
{
	if (index >= 0 && index < m_MusicData.size()) 
	{
		return m_MusicData[index].second;
	}
	else 
	{
		return nullptr;
	}
}

QList<FMOD::Sound*> MusicPlaylistModel::musicList() const
{
	QList<FMOD::Sound*> music_pointers;
	music_pointers.reserve(m_MusicData.size());
	for (auto& music : m_MusicData) 
	{
		music_pointers.append(music.second);
	}
	return music_pointers;
}

int MusicPlaylistModel::musicCount() const
{
	return m_MusicData.size();
}

bool MusicPlaylistModel::moveMusic(int from, int to)
{
	if (from >= 0 && from < m_MusicData.size() && to >= 0 && to < m_MusicData.size()) 
	{
		std::swap(m_MusicData[from], m_MusicData[to]);

		emit musicDataChanged();

		if (m_CurrentIndex == from) 
		{
			m_CurrentIndex = to;

			emit currentIndexChanged(m_CurrentIndex);
			if (m_CurrentIndex != -1) 
			{
				emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
				emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
			}
		}

		return true;
	}
	else 
	{
		return false;
	}
}

int MusicPlaylistModel::nextIndex(int steps)
{
	if (m_MusicData.size() != 0) 
	{
		for (int i = 0; i < steps; i++) 
		{
			switch (m_PlaybackMode) 
			{
			case PlaybackMode::CurrentItemOnce:
				m_CurrentIndex = -1;
				break;
			case PlaybackMode::CurrentItemInLoop:
				break;
			case PlaybackMode::Sequential:
			default:
				if (m_CurrentIndex + 1 >= m_MusicData.size()) 
				{
					m_CurrentIndex = -1;
				}
				else 
				{
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
		if (m_CurrentIndex != -1)
		{
			emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
			emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
		}
	}

	return m_CurrentIndex;
}

uint MusicPlaylistModel::currentMusicTimePosition()
{
	uint position = 0;
	if (m_MainChannel) 
	{
		m_MainChannel->getPosition(&position, FMOD_TIMEUNIT_MS);
	}
	return position;
}

void MusicPlaylistModel::setCurrentMusicTimePosition()
{
}

uint MusicPlaylistModel::currentMusicDuration()
{
	uint duration = 0;
	if (m_CurrentIndex >= 0 && m_CurrentIndex < m_MusicData.size())
	{
		FMOD::Sound* music = ((QPair<QString, FMOD::Sound*>*)index(m_CurrentIndex, 0).data().data())->second;
		if (music)
		{
			music->getLength(&duration, FMOD_TIMEUNIT_MS);
		}
	}
	return duration;;
}

bool MusicPlaylistModel::isMuted()
{
	bool muted = false;
	m_MainChannelGroup->getMute(&muted);
	return muted;
}

float MusicPlaylistModel::volume()
{
	float volume = 0;
	m_MainChannelGroup->getVolume(&volume);
	return volume;
}

MusicPlaylistModel::MusicState MusicPlaylistModel::state()
{
	bool is_paused = false;
	m_MainChannelGroup->getPaused(&is_paused);
	if (is_paused) 
	{
		return MusicPlaylistModel::MusicState::PausedState;
	}
	else 
	{
		bool is_playing = false;
		m_MainChannelGroup->isPlaying(&is_playing);
		return is_playing ? MusicPlaylistModel::MusicState::PlayingState : MusicPlaylistModel::MusicState::StoppedState;
	}

	return MusicPlaylistModel::MusicState::StoppedState;
}

void MusicPlaylistModel::play()
{
	if (m_MainChannel) 
	{
		m_MainChannel->stop();
		emit stateChanged(state());
		m_MainChannel = NULL;
	}

	FMOD::Sound* current_music = ((QPair<QString, FMOD::Sound*>*)index(m_CurrentIndex, 0).data().data())->second;

	if (current_music) 
	{
		m_MusicSystem->playSound(current_music, m_MainChannelGroup, false, &m_MainChannel);
		emit stateChanged(state());
		emit currentMusicNameChanged(currentMusicName());
		emit currentMusicChanged(currentMusic());
		emit durationChanged(currentMusicDuration());
	}
	else {
		if (m_MusicData.size() > 0) 
		{
			if (m_CurrentIndex == -1)
			{
				setCurrentIndex(qrand() % m_MusicData.size());
			}

			if (!current_music)
			{
				m_MusicSystem->createStream(m_MusicData[m_CurrentIndex].first.toUtf8(), FMOD_DEFAULT, 0, &m_MusicData[m_CurrentIndex].second);
				if (!m_MusicData[m_CurrentIndex].second)
				{
					emit failedToLoadMusic(m_CurrentIndex);
				}
				else
				{
					m_MusicSystem->playSound(m_MusicData[m_CurrentIndex].second, m_MainChannelGroup, false, &m_MainChannel);
					emit stateChanged(state());
					emit currentMusicNameChanged(currentMusicName());
					emit currentMusicChanged(currentMusic());
					emit durationChanged(currentMusicDuration());
				}
			}
		}
	}
}

void MusicPlaylistModel::play(int index)
{
	setCurrentIndex(index);
	play();
}

void MusicPlaylistModel::play(const QString & music)
{
	int index = contains(music);
	if (index == -1) 
	{
		addMusic(music);
		index = contains(music);
	}

	if (index != -1)play(index);
}

void MusicPlaylistModel::setMuted(bool muted)
{
	m_MainChannelGroup->setMute(muted);
	emit mutedChanged(muted);
}

void MusicPlaylistModel::pause(bool pause)
{
	m_MainChannelGroup->setPaused(pause);
	emit stateChanged(state());
}

MusicPlaylistModel::PlaybackMode MusicPlaylistModel::playbackMode() const
{
	return m_PlaybackMode;
}

int MusicPlaylistModel::previousIndex(int steps)
{
	if (m_MusicData.size() != 0) 
	{
		for (int i = 0; i < steps; i++) 
		{
			switch (m_PlaybackMode) 
			{
			case PlaybackMode::CurrentItemOnce:
				break;
			case PlaybackMode::CurrentItemInLoop:
				break;
			case PlaybackMode::Sequential:
			default:
				if (m_CurrentIndex - 1 < 0) 
				{
					m_CurrentIndex = 0;
				}
				else
				{
					m_CurrentIndex--;
				}
				break;
			case PlaybackMode::Loop:
				m_CurrentIndex = (m_CurrentIndex - 1) % m_MusicData.size();
				if (m_CurrentIndex < 0)
					m_CurrentIndex += m_MusicData.size();
				break;
			case PlaybackMode::Random:
				m_CurrentIndex = (m_CurrentIndex - qrand()) % m_MusicData.size();
				if (m_CurrentIndex < 0)
					m_CurrentIndex += m_MusicData.size();
				break;
			}
		}

		emit currentIndexChanged(m_CurrentIndex);
		if (m_CurrentIndex != -1) 
		{
			emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
			emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
		}
	}

	return m_CurrentIndex;
}

bool MusicPlaylistModel::removeMusic(int pos)
{
	if (pos >= 0 && pos < m_MusicData.size()) 
	{
		QString music_name = m_MusicData[pos].first;
		if (m_MusicData[pos].second)
		{
			m_MusicData[pos].second->release();
			delete m_MusicData[pos].second;
		}
		m_MusicData.removeAt(pos);
		emit musicRemoved(music_name);

		if (m_CurrentIndex == pos)
		{
			if (m_MusicData.size()>0)m_CurrentIndex = 0;
			else m_CurrentIndex = -1;

			emit currentIndexChanged(m_CurrentIndex);
			if (m_CurrentIndex != -1) 
			{
				emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
				emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
			}
		}
		return true;
	}
	else 
	{
		return false;
	}
}

bool MusicPlaylistModel::removeMusic(int start, int end)
{
	if (start >= 0 && start < m_MusicData.size()) 
	{
		for (int i = start; i <= end; i++) {
			if (m_MusicData[i].second)
			{
				QString music_name = m_MusicData[i].first;
				m_MusicData[i].second->release();
				delete m_MusicData[i].second;
				emit musicRemoved(music_name);
			}
		}
		m_MusicData.erase(m_MusicData.begin() + start, m_MusicData.begin() + end);

		if (m_CurrentIndex > start && m_CurrentIndex < end) 
		{
			if (m_MusicData.size()>0)m_CurrentIndex = 0;
			else m_CurrentIndex = -1;

			emit currentIndexChanged(m_CurrentIndex);
			if (m_CurrentIndex != -1) 
			{
				emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
				emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
			}
		}
		return true;
	}
	else 
	{
		return false;
	}
}

void MusicPlaylistModel::setPlaybackMode(PlaybackMode mode)
{
	m_PlaybackMode = mode;
}

int MusicPlaylistModel::contains(const QString & music)
{
	for (int i = 0; i < m_MusicData.size(); i++) 
	{
		if (m_MusicData[i].first == music) 
		{
			return i;
		}
	}
	return -1;
}

void MusicPlaylistModel::setCurrentMusicTimePosition(uint position)
{
	if (m_MainChannel)
	{
		m_MainChannel->setPosition(position, FMOD_TIMEUNIT_MS);
		emit currentMusicTimePositionChanged(position);
	}
}

void MusicPlaylistModel::setVolume(float volume)
{
	m_MainChannelGroup->setVolume(volume);

	emit volumeChanged(volume);
}

void MusicPlaylistModel::stop()
{
	m_MainChannel->stop();

	emit stateChanged(state());
}

void MusicPlaylistModel::next()
{
	if (m_MusicData.size() != 0) 
	{
		switch (m_PlaybackMode) 
		{
		case PlaybackMode::CurrentItemOnce:
			m_CurrentIndex = -1;
			break;
		case PlaybackMode::CurrentItemInLoop:
			break;
		case PlaybackMode::Sequential:
		default:
			if (m_CurrentIndex + 1 >= m_MusicData.size()) 
			{
				m_CurrentIndex = -1;
			}
			else 
			{
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
		if (m_CurrentIndex != -1)
		{
			emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
			emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
		}
	}
}

void MusicPlaylistModel::previous()
{
	if (m_MusicData.size() != 0) 
	{
		switch (m_PlaybackMode) 
		{
		case PlaybackMode::CurrentItemOnce:
			break;
		case PlaybackMode::CurrentItemInLoop:
			break;
		case PlaybackMode::Sequential:
		default:
			if (m_CurrentIndex - 1 < 0) 
			{
				m_CurrentIndex = 0;
			}
			else 
			{
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
		if (m_CurrentIndex != -1)
		{
			emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
			emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
		}
	}
}

void MusicPlaylistModel::setCurrentIndex(int pos)
{
	if (pos >= 0 && pos < m_MusicData.size()) 
	{
		m_CurrentIndex = pos;
		emit currentIndexChanged(m_CurrentIndex);
		if (m_CurrentIndex != -1) 
		{
			emit currentMusicNameChanged(m_MusicData[m_CurrentIndex].first);
			emit currentMusicChanged(m_MusicData[m_CurrentIndex].second);
		}
	}
}

void MusicPlaylistModel::shuffle()
{
	std::random_shuffle(m_MusicData.begin(), m_MusicData.end());
	emit musicDataChanged();
}
