#include "MusicComboBox.h"



MusicComboBox::MusicComboBox(QWidget *parent)
	: QComboBox(parent)
{
	this->installEventFilter(this);
}

bool MusicComboBox::eventFilter(QObject * obj, QEvent * event)
{
	if (event->type() == QEvent::MouseButtonPress) {
		emit pressed();
	}
	if (event->type() == QEvent::MouseButtonRelease) {
		emit released();
	}
	return QComboBox::eventFilter(obj, event);
}
