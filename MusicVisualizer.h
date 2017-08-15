#pragma once

#include <QWidget>

#include <time.h>

#include <FMOD\fmod.hpp>

class MusicVisualizer : public QWidget
{
	Q_OBJECT

public:
	MusicVisualizer(QWidget *parent = Q_NULLPTR);
	~MusicVisualizer();
protected:
	void paintEvent(QPaintEvent *event) override;

private:
	FMOD::DSP* dsp;
	FMOD::ChannelGroup* channel_group;
	FMOD::Sound *song;
	QList<QPair<int,float>> heights;
	clock_t lastTime;
};
