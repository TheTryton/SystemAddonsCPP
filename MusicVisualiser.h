#pragma once

#include <QtWidgets>
#include <FMOD\fmod.hpp>
#include <time.h>

class MusicVisualizerItem;

class MusicVisualiser : public QWidget
{
	Q_OBJECT
	friend class MusicPlayer;
private:
	MusicVisualiser(QWidget *parent);
	~MusicVisualiser();
protected:
	void paintEvent(QPaintEvent *event) override;
private:
	FMOD::DSP* m_DSP = NULL;

	QList<QPair<MusicVisualizerItem, int>> m_VisualiserItems;

	MusicPlayer* parent_music_player = NULL;

	clock_t m_LastTime = 0;
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
	QPointF m_Position = QPointF(0, 0);
	double m_Rotation = 0;

	double m_Length = 0;

	double m_LengthGain = 0.01;
	double m_LengthFalloff = 0.001;

	QColor m_Color = QColor(255, 255, 255);

	QList<QPair<QPointF, QPointF>> bursted_objects;

	void draw(QPainter* painter);
	void update(double deltaTime, double sampleValue, double volume);
private:
    void drawSubsphere(QPainter* painter, QPoint p, float radius);
	double m_LengthTarget = 0;
};
