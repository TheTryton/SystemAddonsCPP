#pragma once

#include <QComboBox>
#include <QEvent>
#include <QKeyEvent>

class MusicComboBox : public QComboBox
{
	Q_OBJECT
public:
	MusicComboBox(QWidget *parent = Q_NULLPTR);
protected:
	bool eventFilter(QObject *obj, QEvent *event) override;
signals:
	void pressed();
	void released();
};
