#include "MusicVisualiser.h"

#include "MusicPlayer.h"
#include "MathHelper.h"

MusicVisualiser::MusicVisualiser(QWidget *parent)
	: QWidget(parent)
{
	parent_music_player = (MusicPlayer*)parent;
	parent_music_player->m_MusicSystem->createDSPByType(FMOD_DSP_TYPE::FMOD_DSP_TYPE_FFT, &m_DSP);
	parent_music_player->m_MainChannelGroup->addDSP(FMOD_CHANNELCONTROL_DSP_INDEX::FMOD_CHANNELCONTROL_DSP_FADER, m_DSP);

	void(MusicPlayer::*fun)(int) = &MusicPlayer::currentMusicChanged;
	QObject::connect(parent_music_player, fun, [&](int index) {
		m_VisualiserItems.clear();
	});

	QObject::connect(parent_music_player, &MusicPlayer::positionChanged, [&](uint position) {
		this->repaint();
	});
}

MusicVisualiser::~MusicVisualiser()
{
}

void MusicVisualiser::paintEvent(QPaintEvent * event)
{
	double deltaTime = (clock() - m_LastTime) / 1000.0;

	QPainter painter(this);

	float volume = 0;
	parent_music_player->m_MainChannelGroup->getVolume(&volume);

	if (parent_music_player->m_MainChannel) {
		FMOD_DSP_PARAMETER_FFT *FFT;
		m_DSP->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void **)&FFT, 0, 0, FMOD_DSP_FFT_WINDOW_RECT);

		float outputRate = 0;

		parent_music_player->m_MainChannel->getFrequency(&outputRate);

		int spectrum_size = FFT->length;
		float spectrum_range = outputRate;
		float bin_size = spectrum_range / (float)spectrum_size;
		int spectrum_start = 20;
		int spectrum_end = 1500;

		if (m_VisualiserItems.size() == 0) {
			for (int bin = 0; bin < spectrum_size; bin++)
			{

				float val = FFT->spectrum[0][bin];
				if (bin_size*(bin + 1) > spectrum_start && bin_size*(bin + 1) < spectrum_end) {
					MusicVisualizerItem item;
					item.m_MaxLength = MathHelper::random(0.1, 0.25);
					item.m_Position = QPointF(MathHelper::random(item.m_MaxLength, 1 - item.m_MaxLength), MathHelper::random(item.m_MaxLength, 1 - item.m_MaxLength));
					item.m_Rotation = MathHelper::random(0, 1);
					item.m_Type = MusicVisualizerItem::Type::Circle;
					item.m_LengthFalloff = 3;
					item.m_LengthGain = 4;
					item.m_Length = val;
					float r = MathHelper::random(0, 1);
					float g = MathHelper::random(0, 1);
					float b = MathHelper::random(0, 1);
					item.m_Color = QColor(r * 255, g * 255, b * 255);
					m_VisualiserItems.append(QPair<MusicVisualizerItem, int>(item, bin));
				}
			}
		}
		else {
			if (parent_music_player->state() != MusicPlayer::State::PausedState) {
				for (auto& visualiserItem : m_VisualiserItems)
				{
					visualiserItem.first.update(deltaTime, FFT->spectrum[0][visualiserItem.second], volume);
				}
			}
			for (auto& visualiserItem : m_VisualiserItems)
			{
				visualiserItem.first.draw(&painter);
			}

		}
	}
	else {
		if (parent_music_player->state() != MusicPlayer::State::PausedState) {
			for (auto& visualiserItem : m_VisualiserItems)
			{
				visualiserItem.first.update(deltaTime, 0, deltaTime);
			}
		}
		for (auto& visualiserItem : m_VisualiserItems)
		{
			visualiserItem.first.draw(&painter);
		}
	}

	m_LastTime = clock();
}

MusicVisualizerItem::MusicVisualizerItem()
{
}

MusicVisualizerItem::~MusicVisualizerItem()
{
}

void MusicVisualizerItem::draw(QPainter * painter)
{
	switch (m_Type) {
	case Type::Circle:
	{
		painter->setPen(Qt::PenStyle::NoPen);
		painter->setRenderHint(QPainter::RenderHint::Antialiasing);

		int width = painter->device()->width();
		int height = painter->device()->height();

		int circleDimensions = qMin(width, height);
		if (m_MaxLength*m_Length * 2 > 0.025) {
			double scale = m_MaxLength*m_Length;

			painter->setBrush(QBrush(m_Color));
			painter->drawEllipse(QRect
			(
				width*m_Position.x() - circleDimensions*scale,
				height*m_Position.y() - circleDimensions*scale,
				circleDimensions*scale * 2,
				circleDimensions*scale * 2
			));

			for (auto& object : bursted_objects) {
				painter->drawEllipse(QRect
				(
					width*object.first.x() - circleDimensions*0.005,
					height*object.first.y() - circleDimensions*0.005,
					circleDimensions*0.01,
					circleDimensions*0.01
				));
			}
		}
	}
	break;
	default:
		break;
	}
}

void MusicVisualizerItem::update(double deltaTime, double sampleValue, double volume)
{
	m_LengthTarget = qMin(volume / 3.5, sampleValue)*(3.5 / volume);

	if (m_LengthTarget > 0.80) {
		int reserved = qMin(360, bursted_objects.size() + 60) - bursted_objects.size();
		bursted_objects.reserve(qMin(360, bursted_objects.size() + 60));
		for (int i = 0; i < reserved; i++) {
			QPointF position = QPointF(
				MathHelper::random(m_MaxLength, 1 - m_MaxLength),
				MathHelper::random(m_MaxLength, 1 - m_MaxLength)
			);
			QPointF velocityVector = QPointF(position - QPointF(MathHelper::random(m_MaxLength, 1 - m_MaxLength), MathHelper::random(m_MaxLength, 1 - m_MaxLength)));
			velocityVector = velocityVector / qSqrt(velocityVector.x()*velocityVector.x() + velocityVector.y()*velocityVector.y()) / 4 * MathHelper::random(2, 8);
			bursted_objects.append(QPair<QPointF, QPointF>(position, velocityVector));
		}
	}

	for (int i = 0; i < bursted_objects.size(); i++) {
		bursted_objects[i].first.setY(bursted_objects[i].first.y() + bursted_objects[i].second.y()*deltaTime + 0.981*deltaTime*deltaTime / 2);
		bursted_objects[i].first.setX(bursted_objects[i].first.x() + bursted_objects[i].second.x()*deltaTime);
		bursted_objects[i].second.setY(bursted_objects[i].second.y() + 0.981*deltaTime);

		if (bursted_objects[i].first.x() < 0 || bursted_objects[i].first.x() > 1 ||
			bursted_objects[i].first.y() > 1) {
			bursted_objects.erase(bursted_objects.begin() + i);
		}
	}

	if (m_LengthTarget > m_Length)
		m_Length = qMin(m_LengthTarget, m_Length + MathHelper::interpolateCubic(1.0, 0.1, m_Length)*m_LengthGain*deltaTime);
	else if (m_LengthTarget < m_Length)
		m_Length = qMax(0.0, m_Length - MathHelper::interpolateCubic(0.1, 1.0, m_Length)*m_LengthFalloff*deltaTime);

	m_Color.setAlpha(MathHelper::inverseInterpolateCubic(0.4, 1.0, m_Length) * 255);
}