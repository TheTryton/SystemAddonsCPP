#pragma once

#include <QtWidgets>

class DocumentsManagerItem : public QObject {
	Q_OBJECT

public:
	friend class BookmarksManager;
	friend class OptionsManager;
	DocumentsManagerItem( QObject * parent = Q_NULLPTR);
	DocumentsManagerItem(const DocumentsManagerItem&);
	~DocumentsManagerItem();

	void setVisibleName(QString visible_name);
	QString getVisibleName();
	QString getFileName();
	void setSyncOverInternet(bool sync);
	bool getSyncOverInternet();
	void setInternetName(QString name);
	QString getInternetName();
	QString getImgFileName();
	void setImage(QImage& image);
	QImage& getImage();
	void setPos(QPoint pos);
	QPoint getPos();
	void setSize(QSize size);
	QSize getSize();
private:
	QString visible_name;
	QString file_name;
	QString img_file_name;
	QImage img;
	QSize total_size;
	QPoint item_display_position;
	bool sync_over_internet = false;
	QString internet_name;
};
