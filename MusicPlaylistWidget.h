#pragma once

#include <QAbstractItemView>
#include <QWheelEvent>
#include <QPropertyAnimation>
#include <QBoxLayout>

#include "MusicPlaylistModel.h"

class MusicPlaylistWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(QPoint scrollPoint READ scrollPoint WRITE setScrollPoint)
public:
	MusicPlaylistWidget(QWidget *parent = Q_NULLPTR);
public:
	void setSmoothScrolling(bool smooth = false);
	bool smoothScrolling() const;

	QModelIndex indexAt(const QPoint & point) const;
	void scrollTo(const QModelIndex & index);
	QRect visualRect(const QModelIndex & index) const;
protected:
	virtual bool isIndexHidden(const QModelIndex & index) const;
	virtual int horizontalOffset() const;
	virtual int verticalOffset() const;
	virtual void setSelection(const QRect & rect, QItemSelectionModel::SelectionFlags flags);
	virtual QRegion visualRegionForSelection(const QItemSelection & selection) const;
	virtual void scrollContentsBy(int dx, int dy);

	virtual void wheelEvent(QWheelEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event) override;
	virtual void paintEvent(QPaintEvent* event) override;
private:
	MusicPlaylistModel* model = NULL;
	QItemSelectionModel* selection_model = NULL;
	QScrollBar* vertical_scrollbar = NULL;
	QHBoxLayout* root_layout = NULL;

	QPoint scrollPoint();
	void setScrollPoint(const QPoint& point);

	bool m_ScrollSmoothly = false;

	QPropertyAnimation* m_SmoothVerticalScrollingAnimation = NULL;
	QPropertyAnimation* m_SmoothHorizontalScrollingAnimation = NULL;
};