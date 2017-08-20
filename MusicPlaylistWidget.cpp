#include "MusicPlaylistWidget.h"
#include <QScrollBar>
#include <QStringListModel>
#include <QPainter>
#include <QWheelEvent>
#include <QDebug>

MusicPlaylistWidget::MusicPlaylistWidget(QWidget *parent)
	: QWidget(parent)
{
	//MODEL
	{
		model = new MusicPlaylistModel;
		for (int i = 0; i < 100; i++)
			model->addMusic(QString::number(i));

		selection_model = new QItemSelectionModel;
		selection_model->setModel(model);
	}
	//LAYOUT
	{
		root_layout = new QHBoxLayout;
		{
			vertical_scrollbar = new QScrollBar;
		}

		root_layout->addWidget(vertical_scrollbar);
		vertical_scrollbar->setOrientation(Qt::Orientation::Vertical);
	}	
}

void MusicPlaylistWidget::setSmoothScrolling(bool smooth)
{
	m_ScrollSmoothly = smooth;
}

bool MusicPlaylistWidget::smoothScrolling() const
{
	return m_ScrollSmoothly;
}


QModelIndex MusicPlaylistWidget::indexAt(const QPoint & point) const
{
	return QModelIndex();
}

void MusicPlaylistWidget::scrollTo(const QModelIndex & index)
{
}

QRect MusicPlaylistWidget::visualRect(const QModelIndex & index) const
{
	return QRect();
}

bool MusicPlaylistWidget::isIndexHidden(const QModelIndex & index) const
{
	return false;
}

int MusicPlaylistWidget::horizontalOffset() const
{
	return 0;
}

int MusicPlaylistWidget::verticalOffset() const
{
	return 0;
}

void MusicPlaylistWidget::setSelection(const QRect & rect, QItemSelectionModel::SelectionFlags flags)
{
}

QRegion MusicPlaylistWidget::visualRegionForSelection(const QItemSelection & selection) const
{
	return QRegion();
}

void MusicPlaylistWidget::scrollContentsBy(int dx, int dy)
{
	//this->viewport->scroll(dx, dy);
	this->repaint();
}

void MusicPlaylistWidget::wheelEvent(QWheelEvent * event)
{
	if (event->orientation() == Qt::Orientation::Vertical) {
		scrollContentsBy(0, event->delta());
	}
}

void MusicPlaylistWidget::mouseReleaseEvent(QMouseEvent * event)
{
}

void MusicPlaylistWidget::mouseMoveEvent(QMouseEvent * event)
{
}

void MusicPlaylistWidget::paintEvent(QPaintEvent * event)
{
	QFontMetrics font_metrics = this->fontMetrics();

	this->vertical_scrollbar->setMinimum(0);
	this->vertical_scrollbar->setMaximum(font_metrics.height() + model->rowCount() * font_metrics.height());

	//QPainter painter(viewport);
	
	//painter.fillRect(QRect(QPoint(0,0),this->size()), QWidget::palette().color(QWidget::backgroundRole()));

	for (int i = 0; i < model->rowCount(); i++) {
	//	painter.drawText(QPoint(0, font_metrics.height() + i * font_metrics.height() - viewport->y()), model->musicName(i));
	}
	
}

QPoint MusicPlaylistWidget::scrollPoint()
{
	//return this->viewport->pos();
	return QPoint();
}

void MusicPlaylistWidget::setScrollPoint(const QPoint & point)
{
	//this->viewport->move(point);
}
