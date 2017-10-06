#include "BookmarksManager.h"

#include "NetworkManager.h"
#include "DataManager.h"
#include "InternetNameSelectionDialog.h"

#include "SystemAddonsPopup.h"

#include <QColorDialog>
#include <QApplication>
#include <QMouseEvent>
#include <QtMath>
#include <QDropEvent>
#include <QMimeData>
#include <QInputDialog>
#include <QFileInfo>
#include <QFileDialog>
#include <QDesktopServices>
#include <QDrag>
#include <QPainter>
#include <QMessageBox>

BookmarksManager* BookmarksManager::instance = NULL;

BookmarksManager::BookmarksManager(QWidget * parent) : QWidget(parent) {
	//DATA MANAGER INITIALIZATION
	{
		data_manager = DataManager::getInstance();
	}
	//WIDGET INITIALIZATION
	{
		this->setAcceptDrops(true);
		QPalette palette = this->palette();
		palette.setBrush(QPalette::Window, QBrush(data_manager->getBackgroundColor()));
		this->setAutoFillBackground(true);
		this->setPalette(palette);
	}
	//RIGHT CLICK MENU INITIALIZATION
	{
		right_button_context_menu = new QMenu(this);
		//HIDE POPUP
		QAction* hide = new QAction(u8"Hide and lock popup", this);
		QObject::connect(hide, &QAction::triggered, [&](bool checked) {
			emit shouldLock();
		});
		right_button_context_menu->addAction(hide);

		right_button_context_menu->addSeparator();

		//BACKGROUND COLOR
		QMenu* background_color_menu = new QMenu("Background color", this);
		{
			//CHANGE COLOR
			QAction* change_background_color = new QAction(u8"Change background color", this);
			QObject::connect(change_background_color, &QAction::triggered, [&](bool checked) {
				QColorDialog dialog(this);

				QColor final_color = data_manager->getDefaultBackgroundColor();

				QObject::connect(&dialog, &QColorDialog::currentColorChanged, this, [&](const QColor & color) {
					data_manager->setBackgroundColor(QColor(color.red(), color.green(), color.blue(), 180));
					emit changedColor();
				});
				QObject::connect(&dialog, &QColorDialog::colorSelected, this, [&](const QColor & color) {
					final_color = QColor(color.red(), color.green(), color.blue(), 180);
				});
				dialog.exec();

				data_manager->setBackgroundColor(QColor(final_color.red(), final_color.green(), final_color.blue(), 180));
				emit changedColor();
				data_manager->saveData();
			});
			background_color_menu->addAction(change_background_color);

			//RESTORE DEFAULT COLOR
			QAction* restore_default_background_color = new QAction(u8"Restore default background color", this);
			QObject::connect(restore_default_background_color, &QAction::triggered, [&](bool checked) {
				data_manager->setBackgroundColor(data_manager->getDefaultBackgroundColor());
				emit changedColor();
			});
			background_color_menu->addAction(restore_default_background_color);
		}
		right_button_context_menu->addMenu(background_color_menu);

		//RESIZE BAR COLOR
		QMenu* resize_bar_color_menu = new QMenu("Resize bar color", this);
		{
			QAction* change_resize_bar_color = new QAction(u8"Change resize bar color", this);
			QObject::connect(change_resize_bar_color, &QAction::triggered, [&](bool checked) {
				QColorDialog dialog(this);
				
				QColor final_color = data_manager->getDefaultResizeBarColor();

				QObject::connect(&dialog, &QColorDialog::currentColorChanged, this, [&](const QColor & color) {
					data_manager->setResizeBarColor(QColor(color.red(), color.green(), color.blue(), 180));
					emit changedColor();
				});
				QObject::connect(&dialog, &QColorDialog::colorSelected, this, [&](const QColor & color) {
					final_color = QColor(color.red(), color.green(), color.blue(), 180);
				});
				dialog.exec();

				data_manager->setResizeBarColor(QColor(final_color.red(), final_color.green(), final_color.blue(), 180));
				emit changedColor();
				data_manager->saveData();
			});
			resize_bar_color_menu->addAction(change_resize_bar_color);

			QAction* restore_default_resize_bar_color = new QAction(u8"Restore default resize bar color", this);
			QObject::connect(restore_default_resize_bar_color, &QAction::triggered, [&](bool checked) {
				data_manager->setResizeBarColor(data_manager->getDefaultResizeBarColor());
				emit changedColor();
			});
			resize_bar_color_menu->addAction(restore_default_resize_bar_color);
		}
		right_button_context_menu->addMenu(resize_bar_color_menu);

		right_button_context_menu->addSeparator();

		//EXIT
		QAction* exit = new QAction(u8"Exit", this);
		QObject::connect(exit, &QAction::triggered, [&](bool checked) {
			data_manager->saveData();
			QApplication::exit();
		});
		right_button_context_menu->addAction(exit);

		//UNLOCK
		QObject::connect(right_button_context_menu, &QMenu::aboutToHide, [=]() {
			SystemAddonsPopup::getInstance()->freezePopup(false);
		});
	}
	//SYNC IMAGE INITIALIZATION
	{
		sync_img = QImage("sync.png");
	}
}

BookmarksManager* BookmarksManager::getInstance()
{
	if (BookmarksManager::instance == NULL) BookmarksManager::instance = new BookmarksManager();
	return BookmarksManager::instance;
}

BookmarksManager::~BookmarksManager() {
	if (instance != NULL)delete instance;
}

void BookmarksManager::dropEvent(QDropEvent * event)
{
	for (int k = 0; k < event->mimeData()->urls().size(); k++) {
		data_manager->addBookmark(event->mimeData()->urls()[k].toLocalFile());
		data_manager->saveData();
	}
	this->repaint();
}

void BookmarksManager::mousePressEvent(QMouseEvent * event)
{
	QSize item_size = data_manager->getPreferredBookmarkSize();
	QSize item_spacing = data_manager->getSpacingBetweenBookmarks();
	int item_count_horz = qRound((float)(this->size().width() - item_spacing.width()) / (float)(item_size.width() + item_spacing.width()));
	int item_count_vert = qCeil((float)(this->size().height() - item_spacing.height()) / (float)(item_size.height() + item_spacing.height()));
	QSize item_grid_size = QSize(item_count_horz, item_count_vert);
	QList<BookmarkItem>* bookmark_items = data_manager->getBookmarkItems();

	//SELECT
	if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
		if (!(event->pos().x() % (item_size.width() + item_spacing.width()) < item_spacing.width()) &&
			!(event->pos().y() % (item_size.height() + item_spacing.height()) < item_spacing.height())) {
			int x_item = event->pos().x() / (item_size.width() + item_spacing.width());
			int y_item = event->pos().y() / (item_size.height() + item_spacing.height());

			int index = y_item*item_grid_size.width() + x_item;

			if (x_item < item_grid_size.width() && y_item < item_grid_size.height() && index < bookmark_items->size()) {
				selected_item = QPoint(x_item, y_item);
				this->repaint();
			}
			else {
				selected_item = QPoint(-1, -1);
				this->repaint();
			}
		}
		else {
			selected_item = QPoint(-1, -1);
			this->repaint();
		}

		drag_start_position = event->pos();
	}
	//CONTEXT MENU
	if (event->button() == Qt::RightButton) {
		if (event->pos().x() % (item_size.width() + item_spacing.width()) < item_spacing.width() ||
			event->pos().y() % (item_size.height() + item_spacing.height()) < item_spacing.height()) {
			SystemAddonsPopup::getInstance()->freezePopup(true);
			right_button_context_menu->exec(mapToGlobal(event->pos()));
		}
		else {
			int x_item = event->pos().x() / (item_size.width() + item_spacing.width());
			int y_item = event->pos().y() / (item_size.height() + item_spacing.height());

			int index = y_item*item_grid_size.width() + x_item;
			if(x_item >= item_grid_size.width())right_button_context_menu->exec(mapToGlobal(event->pos()));
			else if(y_item >= item_grid_size.height())right_button_context_menu->exec(mapToGlobal(event->pos()));
			else if(index >= bookmark_items->size())right_button_context_menu->exec(mapToGlobal(event->pos()));
			else {
				QMenu item_menu(this);

				QAction* remove = new QAction(u8"Remove", this);
				QObject::connect(remove, &QAction::triggered, [=](bool checked) {
					data_manager->removeBookmark(index);
					data_manager->saveData();
					selected_item = QPoint(-1, -1);
					this->repaint();
				});
				item_menu.addAction(remove);
				
				QMenu name_menu("Name");
				{
					QAction* change_name = new QAction(u8"Change name", this);
					QObject::connect(change_name, &QAction::triggered, [=](bool checked) {
						bool ok = false;
						QString text = QInputDialog::getText(this, u8"Change name", u8"", QLineEdit::Normal, (*bookmark_items)[index].getVisibleName(), &ok);
						if (ok) {
							(*bookmark_items)[index].setVisibleName(text);
							data_manager->saveData();
							this->repaint();
						}
					});
					name_menu.addAction(change_name);

					QAction* restore_default_name = new QAction(u8"Restore default name", this);
					QObject::connect(restore_default_name, &QAction::triggered, [=](bool checked) {
						QFileInfo file_info((*bookmark_items)[index].getLocalFilename());
						if (file_info.isFile()) (*bookmark_items)[index].setVisibleName(file_info.baseName().mid(0, file_info.fileName().lastIndexOf('.')));
						else if (file_info.isDir()) (*bookmark_items)[index].setVisibleName(file_info.fileName());
						data_manager->saveData();
						this->repaint();
					});
					name_menu.addAction(restore_default_name);
				}
				item_menu.addMenu(&name_menu);

				QMenu icon_menu("Icon");
				{
					QAction* change_icon = new QAction(u8"Change icon", this);
					QObject::connect(change_icon, &QAction::triggered, [=](bool checked) {
						QString file_name = QFileDialog::getOpenFileName(this, u8"Change icon", u8"", u8"Image Files (*.png *.jpg *.jpeg *.bmp *.ico)");
						if (file_name != "") {
							(*bookmark_items)[index].setVisibleImageFilename(file_name, data_manager->getPreferredBookmarkImageSize());
							data_manager->saveData();
							this->repaint();
						}
					});
					icon_menu.addAction(change_icon);

					QAction* restore_default_icon = new QAction(u8"Restore default icon", this);
					QObject::connect(restore_default_icon, &QAction::triggered, [=](bool checked) {
						(*bookmark_items)[index].setVisibleImageAsDefaultFileIcon(data_manager->getPreferredBookmarkImageSize());
						data_manager->saveData();
						this->repaint();
					});
					icon_menu.addAction(restore_default_icon);
				}
				item_menu.addMenu(&icon_menu);

				/*
				QMenu network_menu("Network");
				{
					QAction* sync_over_internet = new QAction(u8"Synchronize over internet?", this);
					sync_over_internet->setCheckable(true);
					sync_over_internet->setChecked((*bookmark_items)[index].getSynchronizeOverInternet());
					QObject::connect(sync_over_internet, &QAction::triggered, [=](bool checked) {
						if (!(*bookmark_items)[index].getSynchronizeOverInternet()) {
							if (QMessageBox::question(this, "Synchronization", "Do you want to synchronize this file/directory with other devices?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
								InternetNameSelectionDialog* dialog = new InternetNameSelectionDialog(this);
								dialog->exec();
								if (dialog->getNameChosen() != "") {
									(*bookmark_items)[index].setSynchronizeOverInternet(true);
									(*bookmark_items)[index].setInternetName(dialog->getNameChosen());
									data_manager->saveData();
								}
							}
						}
						else {
							if (QMessageBox::question(this, "Synchronization", "Turn off synchronization?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
								data_manager->unregisterInternetName((*bookmark_items)[index].getInternetName());
								(*bookmark_items)[index].setSynchronizeOverInternet(false);
								(*bookmark_items)[index].setInternetName("");
								data_manager->saveData();
							}
						}
					});
					network_menu.addAction(sync_over_internet);

					if ((*bookmark_items)[index].getSynchronizeOverInternet()) {
						QAction* change_internet_name = new QAction(u8"Change internet name", this);
						QObject::connect(change_internet_name, &QAction::triggered, [=](bool checked) {
							InternetNameSelectionDialog* dialog = new InternetNameSelectionDialog(this);
							dialog->exec();
							if (dialog->getNameChosen() != "") {
								data_manager->unregisterInternetName((*bookmark_items)[index].getInternetName());
								(*bookmark_items)[index].setSynchronizeOverInternet(true);
								(*bookmark_items)[index].setInternetName(dialog->getNameChosen());
								data_manager->saveData();
							}
						});
						network_menu.addAction(change_internet_name);
					}
				}
				item_menu.addMenu(&network_menu);
				*/

				QAction* open_file_location = new QAction(u8"Open file location", this);
				QObject::connect(open_file_location, &QAction::triggered, [=](bool checked) {
					QFileInfo file_info((*bookmark_items)[index].getLocalFilename());
					QDesktopServices::openUrl(QUrl::fromLocalFile(file_info.dir().absolutePath()));
				});
				item_menu.addAction(open_file_location);

				SystemAddonsPopup::getInstance()->freezePopup(true);

				QObject::connect(&item_menu, &QMenu::aboutToHide, [=]() {
					SystemAddonsPopup::getInstance()->freezePopup(false);
				});
				item_menu.exec(event->pos());
			}
		}
	}
}

void BookmarksManager::mouseMoveEvent(QMouseEvent * event)
{
	QSize item_size = data_manager->getPreferredBookmarkSize();
	QSize item_spacing = data_manager->getSpacingBetweenBookmarks();
	int item_count_horz = qRound((float)(this->size().width() - item_spacing.width()) / (float)(item_size.width() + item_spacing.width()));
	int item_count_vert = qCeil((float)(this->size().height() - item_spacing.height()) / (float)(item_size.height() + item_spacing.height()));
	QSize item_grid_size = QSize(item_count_horz, item_count_vert);
	QList<BookmarkItem>* bookmark_items = data_manager->getBookmarkItems();

	//DRAG
	if (event->buttons() == Qt::LeftButton) {
		if (selected_item.x() != -1 && selected_item.y() != -1) {
			if ((event->pos() - drag_start_position).manhattanLength() >= QApplication::startDragDistance()) {
				QDrag *drag = new QDrag(this);

				QMimeData* mimeData = new QMimeData;
				int index = selected_item.y()*item_grid_size.width() + selected_item.x();
				mimeData->setUrls(QList<QUrl>() << QUrl::fromLocalFile((*bookmark_items)[index].getLocalFilename()));

				drag->setMimeData(mimeData);

				Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction); 
			}
		}
	}
}

void BookmarksManager::mouseDoubleClickEvent(QMouseEvent * event)
{
	QSize item_size = data_manager->getPreferredBookmarkSize();
	QSize item_spacing = data_manager->getSpacingBetweenBookmarks();
	int item_count_horz = qRound((float)(this->size().width() - item_spacing.width()) / (float)(item_size.width() + item_spacing.width()));
	int item_count_vert = qCeil((float)(this->size().height() - item_spacing.height()) / (float)(item_size.height() + item_spacing.height()));
	QSize item_grid_size = QSize(item_count_horz, item_count_vert);
	QList<BookmarkItem>* bookmark_items = data_manager->getBookmarkItems();

	//SELECT EXEC
	if (event->button() == Qt::LeftButton) {
		if (!(event->pos().x() % (item_size.width() + item_spacing.width()) < item_spacing.width()) &&
			!(event->pos().y() % (item_size.height() + item_spacing.height()) < item_spacing.height())) {
			int x_item = event->pos().x() / (item_size.width() + item_spacing.width());
			int y_item = event->pos().y() / (item_size.height() + item_spacing.height());

			int index = y_item*item_grid_size.width() + x_item;

			if (x_item < item_grid_size.width() && y_item < item_grid_size.height() && index < bookmark_items->size()) {
				QFileInfo file_info((*bookmark_items)[index].getLocalFilename());
				QDesktopServices::openUrl(QUrl::fromLocalFile(file_info.absoluteFilePath()));
			}
		}
	}
}

void BookmarksManager::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);

	QSize item_size = data_manager->getPreferredBookmarkSize();
	QSize item_spacing = data_manager->getSpacingBetweenBookmarks();
	int item_count_horz = qRound((float)(this->size().width() - item_spacing.width()) / (float)(item_size.width() + item_spacing.width()));
	int item_count_vert = qCeil((float)(this->size().height() - item_spacing.height()) / (float)(item_size.height() + item_spacing.height()));
	QSize item_grid_size = QSize(item_count_horz, item_count_vert);
	QList<BookmarkItem>* bookmark_items = data_manager->getBookmarkItems();

	if (sync_img.size().width() != item_size.width() / 5) sync_img = sync_img.scaled(QSize(item_size.width() / 5, item_size.width() / 5), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

	if (selected_item.x() != -1 && selected_item.y() != -1) {
		painter.setPen(Qt::PenStyle::NoPen);
		QColor background_color = data_manager->getBackgroundColor();
		painter.setBrush(QBrush(QColor((background_color.red() + 192) / 2, (background_color.green() + 192) / 2, (background_color.blue() + 192) / 2, background_color.alpha()*0.9)));
		painter.drawRect(selected_item.x()*(item_size.width() + item_spacing.width()) + item_spacing.width(), selected_item.y()*(item_size.height() + item_spacing.height()) + item_spacing.height(), item_size.width(), item_size.height());
	}

	int real_size = (item_grid_size.width()*item_grid_size.height() > bookmark_items->size()) ? bookmark_items->size() : item_grid_size.width()*item_grid_size.height();

	for (int i = 0; i < real_size; i++) {
		painter.setOpacity(data_manager->getBackgroundColor().alpha() / 255.0*1.25);

		int y_pos = i / item_grid_size.width();
		int x_pos = i % item_grid_size.width();
		QPoint item_position = QPoint(item_spacing.width() + x_pos*(item_size.width() + item_spacing.width()), item_spacing.height() + y_pos*(item_size.height() + item_spacing.height()));
		QImage* img = (QImage*)(*bookmark_items)[i].getVisibleImage();

		painter.drawImage(QRectF(QPoint(item_position.x() + (item_size.width() - img->width()) / 2, item_position.y() + (item_size.height() / 2 - img->height()) / 2), QSize(img->width(), img->height())), *img);
		//if((*bookmark_items)[i].getSynchronizeOverInternet())painter.drawImage(QRectF(QPoint(item_position.x(), item_position.y()), QSize(sync_img.width(), sync_img.height())), sync_img);
		painter.setPen(QColor(255, 255, 255));
		painter.drawText(QRectF(QPoint(item_position.x(), item_position.y() + item_size.height() / 2), QSize(item_size.width(), item_size.height() / 2)), Qt::AlignTop | Qt::AlignCenter | Qt::TextWordWrap, (*bookmark_items)[i].getVisibleName());
		painter.drawImage(QRectF(QPoint(item_position.x() + (item_size.width() - img->width()) / 2, item_position.y() + (item_size.height() / 2 - img->height()) / 2), QSize(img->width(), img->height())), *img);
	}
}

void BookmarksManager::dragEnterEvent(QDragEnterEvent * event)
{
	if(event->mimeData()->hasUrls())event->acceptProposedAction();
}
