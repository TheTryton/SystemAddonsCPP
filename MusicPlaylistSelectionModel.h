#pragma once

#include <QItemSelection>
#include <QModelIndex>
#include "MusicPlaylistModel.h"

class MusicPlaylistSelectionModel : public QItemSelectionModel
{
	Q_OBJECT

public:
	MusicPlaylistSelectionModel(QAbstractItemModel* model = Q_NULLPTR) = delete;
	MusicPlaylistSelectionModel(QAbstractItemModel* model, QObject* parent) = delete;
	MusicPlaylistSelectionModel(MusicPlaylistModel* model);
public:
	void setModel(QAbstractItemModel* model) = delete;
private:
	QTimer* delay_timer = NULL;
};
