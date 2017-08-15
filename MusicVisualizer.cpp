#include "MusicVisualizer.h"

#pragma comment(lib,"FMOD/fmod64_vc.lib")

#include <QtMultimedia>

#include <iostream>

using namespace std;

MusicVisualizer::MusicVisualizer(QWidget *parent)
	: QWidget(parent)
{
	FMOD::System     *system;
	FMOD::System_Create(&system);
	system->init(32, FMOD_INIT_NORMAL, NULL);

	
	system->createStream("D:/Music/The Hip Abduction - Before We Lose Our Mind.mp3", FMOD_DEFAULT, 0, &song);

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
}

void MusicVisualizer::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);


	float frq = 0;
	int val = 0;
	bool b = 0;

	FMOD_DSP_PARAMETER_FFT *fft;
	dsp->getParameterData(FMOD_DSP_FFT_SPECTRUMDATA, (void **)&fft, 0, 0, FMOD_DSP_FFT_WINDOW_RECT);

	QPainterPath path;
	path.moveTo(QPoint(0, painter.device()->height()));

	QPoint lastPoint = QPoint(0, painter.device()->height());

	FMOD::Channel* channel;

	channel_group->getChannel(0, &channel);
	float outputRate = 0;
	channel->getFrequency(&outputRate);

	int spectrum_size = fft->length;
	float spectrum_range = outputRate;
	float bin_size = spectrum_range / (float)spectrum_size;
	int spectrum_start = 20;
	int spectrum_end = 2000;

	int index = 0;

	if (heights.size() == 0) {
		for (int bin = 0; bin < spectrum_size; bin++)
		{
			float val = fft->spectrum[0][bin];

			if (bin_size*(bin + 1) > spectrum_start && bin_size*(bin + 1) < spectrum_end) {
				heights.append(QPair<int,float>(bin,val));
			}
		}
	}
	else {
		float deltaTime = (clock() - lastTime) / 1000.0;
		for (int i=0;i<heights.size();i++)
		{
			float val = fft->spectrum[0][heights[i].first];
			
			if (heights[i].second < val)heights[i].second = val;
			else if(heights[i].second>0){
				heights[i].second = max(heights[i].second - 0.1f * deltaTime,0.0f);
			}
		}
	}

	for (int i = 0; i < heights.size(); i++) {
		painter.fillRect(QRect(painter.device()->width() / (float)heights.size()*i, painter.device()->height(), painter.device()->width() / heights.size() / 2, -painter.device()->height()*heights[i].second),
			QColor(255 * (cos(heights[i].second) + 1) / 2, 255 * (sin(heights[i].second) + 1) / 2, 255 * (sin(heights[i].second) + 1) / 2));
	}

	lastTime = clock();
}
