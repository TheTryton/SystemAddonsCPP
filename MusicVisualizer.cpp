#include "MusicVisualizer.h"
#include "MathHelper.h"

#pragma comment(lib,"FMOD/fmod64_vc.lib")

#include <QtMultimedia>

#include <iostream>

using namespace std;

MusicVisualizer::MusicVisualizer(QWidget *parent)
	: QWidget(parent)
{
	
	FMOD::System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, NULL);
	
	system->createStream("D:/Music/Ivan Gough & Feenixpawl ft. Georgi Kay - In My Mind (Axwell Mix) [OFFICIAL VIDEO].mp3", FMOD_DEFAULT, 0, &song);

	system->createDSPByType(FMOD_DSP_TYPE::FMOD_DSP_TYPE_FFT, &dsp);

	system->getMasterChannelGroup(&channel_group);
	channel_group->setVolume(1);


	channel_group->addDSP(FMOD_CHANNELCONTROL_DSP_INDEX::FMOD_CHANNELCONTROL_DSP_FADER, dsp);

	system->playSound(song, channel_group, false, NULL);

	int num_parameters = 0;

	dsp->getNumParameters(&num_parameters);

	QTimer* timer = new QTimer;

	QObject::connect(timer, &QTimer::timeout, this, [&]() {
		this->repaint();
	});

	timer->start(32);
	lastTime = clock();
}

MusicVisualizer::~MusicVisualizer()
{
	system->release();
	delete system;
}

void MusicVisualizer::paintEvent(QPaintEvent * event)
{
	double deltaTime = (clock() - lastTime) / 1000.0;

	QPainter painter(this);

	FMOD_DSP_PARAMETER_FFT *fft;

	dsp->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void **)&fft, 0, 0, FMOD_DSP_FFT_WINDOW_RECT);
	FMOD::Channel* channel;
	channel_group->getChannel(0, &channel);

	float outputRate = 0;
	float volume = 0;
	channel->getFrequency(&outputRate);
	channel->getVolume(&volume);

	int spectrum_size = fft->length;
	float spectrum_range = outputRate;
	float bin_size = spectrum_range / (float)spectrum_size;
	int spectrum_start = 20;
	int spectrum_end = 1500;

	if (m_Spheres.size() == 0) {
		for (int bin = 0; bin < spectrum_size; bin++)
		{
			float val = fft->spectrum[0][bin];
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
				m_Spheres.append(QPair<MusicVisualizerItem,int>(item,bin));
			}
		}
	}
	else {
		float deltaTime = (clock() - lastTime) / 1000.0;
		for (auto& sphere:m_Spheres)
		{
			sphere.first.update(deltaTime ,fft->spectrum[0][sphere.second],volume);
			sphere.first.draw(&painter);
		}
	}

	lastTime = clock();
}

MusicVisualizerItem::MusicVisualizerItem()
{
}

MusicVisualizerItem::~MusicVisualizerItem()
{
}

void MusicVisualizerItem::draw(QPainter * painter)
{
	painter->beginNativePainting();

	switch (m_Type) {
	case Type::Circle:
	{
		painter->setPen(Qt::PenStyle::NoPen);
		painter->setRenderHint(QPainter::RenderHint::Antialiasing);

		int width = painter->device()->width();
		int height = painter->device()->height();

		int circleDimensions = qMin(width,height);
		if (circleDimensions*m_MaxLength*m_Length * 2 > 6) {
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
					width*object.first.x() - circleDimensions*0.0025,
					height*object.first.y() - circleDimensions*0.0025,
					circleDimensions*0.005,
					circleDimensions*0.005
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
	
	m_LengthTarget = qMin(volume/3,sampleValue)*(3 /volume);

	if (m_LengthTarget > 0.80) {
		int reserved = qMin(360, bursted_objects.size() + 60) - bursted_objects.size();
		bursted_objects.reserve(qMin(360, bursted_objects.size() + 60));
		for (int i = 0; i < reserved;i++) {
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
		m_Length = qMax(0.0, m_Length - MathHelper::interpolateCubic(0.1,1.0, m_Length)*m_LengthFalloff*deltaTime);

	m_Color.setAlpha(MathHelper::inverseInterpolateCubic(0.4, 1.0, m_Length) * 255);
}
