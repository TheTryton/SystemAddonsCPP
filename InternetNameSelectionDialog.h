#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTreeWidget>
#include <QLabel>
#include <QPlainTextEdit>

#include "DataManager.h"

class InternetNameSelectionDialog : public QDialog
{
	Q_OBJECT
public:
	QString getNameChosen();
private:
	//DISPLAY
	QVBoxLayout* root_layout = NULL;
	QVBoxLayout* registered_names_layout = NULL;
	QVBoxLayout* create_new_name_layout = NULL;
	QHBoxLayout* create_cancel_layout = NULL;

	QGroupBox* registered_internet_names_gb = NULL;
	QTreeWidget* registered_internet_names = NULL;
	QLabel* selection_description = NULL;
	QPushButton* bind_to_internet_name = NULL;

	QGroupBox* create_new_name_gb = NULL;
	QPlainTextEdit* new_name_ta = NULL;
	QPushButton* create_internet_name = NULL;
	QLabel* creation_description = NULL;

	QPushButton* cancel = NULL;
	//NAME CHOSEN
	QString name_chosen = "";
	//DATA MANAGER POINTER
	DataManager* data_manager;
public:
	InternetNameSelectionDialog(QWidget *parent = Q_NULLPTR);
	~InternetNameSelectionDialog();
};
