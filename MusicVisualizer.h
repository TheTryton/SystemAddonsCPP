#pragma once

#include <QWidget>

#include <time.h>

#include <FMOD\fmod.hpp>

class MusicVisualizerItem;

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
	FMOD::System *system;
	QList<QPair<MusicVisualizerItem,int>> m_Spheres;
	clock_t lastTime;
};

class MusicVisualizerItem {
public:
	MusicVisualizerItem();
	~MusicVisualizerItem();
public:
	enum class Type {
		Circle,
		Bars,
		Line,
		CircularLine
	};

	Type m_Type = Type::Circle;

	double m_MaxLength = 0.01;
	QPointF m_Position = QPointF(0,0);
	double m_Rotation = 0;

	double m_Length = 0;

	double m_LengthGain = 0.01;
	double m_LengthFalloff = 0.001;

	QColor m_Color = QColor(255, 255, 255);

	QList<QPair<QPointF,QPointF>> bursted_objects;

	void draw(QPainter* painter);
	void update(double deltaTime, double sampleValue,double volume);
private:
	double m_LengthTarget = 0;
};
