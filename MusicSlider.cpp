#include "MusicSlider.h"

class MusicSliderStyle : public QProxyStyle
{
public:
	using QProxyStyle::QProxyStyle;

	int styleHint(QStyle::StyleHint hint, const QStyleOption* option = 0, const QWidget* widget = 0, QStyleHintReturn* returnData = 0) const
	{
		if (hint == QStyle::SH_Slider_AbsoluteSetButtons)
			return (Qt::LeftButton | Qt::MidButton | Qt::RightButton);
		return QProxyStyle::styleHint(hint, option, widget, returnData);
	}
};

MusicSlider::MusicSlider(QWidget *parent)
	: QSlider(parent)
{
	setStyle(new MusicSliderStyle(this->style()));
}

void MusicSlider::mousePressEvent(QMouseEvent * event)
{
	QStyleOptionSlider opt;
	initStyleOption(&opt);
	QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);

	if (event->button() == Qt::LeftButton &&
		sr.contains(event->pos()) == false)
	{
		this->setValue(((float)event->pos().x() / this->width())*(this->maximum() - this->minimum()) + this->minimum());
		this->setSliderDown(true);
	}
	QSlider::mousePressEvent(event);
}
