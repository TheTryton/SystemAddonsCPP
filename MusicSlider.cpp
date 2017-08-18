#include "MusicSlider.h"

MusicSlider::MusicSlider(QWidget *parent)
	: QSlider(parent)
{
}

void MusicSlider::mousePressEvent(QMouseEvent * event)
{
	this->setValue(((float)event->pos().x() / this->width())*(this->maximum() - this->minimum()) + this->minimum());
	this->setSliderDown(true);
	QSlider::mousePressEvent(event);
}
