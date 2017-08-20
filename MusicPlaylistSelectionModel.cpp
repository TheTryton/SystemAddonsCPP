#include "MusicPlaylistSelectionModel.h"

MusicPlaylistSelectionModel::MusicPlaylistSelectionModel(MusicPlaylistModel* model):
	QItemSelectionModel(model)
{
	QObject::connect(this, &QItemSelectionModel::currentRowChanged, [=](const QModelIndex &current, const QModelIndex &previous) {
		//if(model->setCurrentIndex())model->setCurrentIndex(current.row());
	});

	QObject::connect(this, &QItemSelectionModel::selectionChanged, [=](const QItemSelection &selected, const QItemSelection &deselected) {
		/*if (selected.size()) {
			if (selected[0].indexes.size()) {
				model->setCurrentIndex(selected[0].indexes[0]);
			}
		}*/
	});

	QObject::connect(model, &MusicPlaylistModel::currentIndexChanged, [=](int position) {
		QItemSelection new_selection;
		new_selection.select(model->currentIndex(), model->currentIndex());

		this->select(selection(), QItemSelectionModel::SelectionFlag::Deselect);
		this->select(new_selection, QItemSelectionModel::SelectionFlag::Select);
	});

	QObject::connect(model, &MusicPlaylistModel::failedToLoadMusic, [=](int row) {
		QItemSelection new_selection;
		new_selection.select(model->currentIndex(), model->currentIndex());

		this->select(selection(), QItemSelectionModel::SelectionFlag::Deselect);
		this->select(new_selection, QItemSelectionModel::SelectionFlag::Select);
	});
/*

	delay_timer = new QTimer;
	delay_timer->setSingleShot(2500);

	void failedToLoadMusic(int row);

	void mutedChanged(bool muted);
	void volumeChanged(int volume);
	void stateChanged(MusicState state);
	void durationChanged(uint duration);

	void musicAdded(int row);
	void musicRemoved(const QString &musicName);
	void musicDataChanged();*/
}
