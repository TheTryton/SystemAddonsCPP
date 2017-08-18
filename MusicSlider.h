#pragma once

#include <QSlider>
#include <QMouseEvent>

class MusicSlider : public QSlider
{
	Q_OBJECT

public:
	MusicSlider(QWidget *parent = Q_NULLPTR);
protected:
	void mousePressEvent(QMouseEvent* event) override;
};
