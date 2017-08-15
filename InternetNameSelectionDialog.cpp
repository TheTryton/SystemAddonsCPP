#include "InternetNameSelectionDialog.h"

#include "NetworkManager.h"
#include "BookmarksManager.h"

#include <QPushButton>
#include <QMessageBox>

InternetNameSelectionDialog::InternetNameSelectionDialog(QWidget *parent)
	: QDialog(parent)
{
	this->data_manager = DataManager::getInstance();

	this->setWindowTitle("Internet name");

	this->root_layout = new QVBoxLayout(this);

	this->create_new_name_layout = new QVBoxLayout(this);

	this->create_cancel_layout = new QHBoxLayout(this);

	this->registered_names_layout = new QVBoxLayout(this);

	this->registered_internet_names_gb = new QGroupBox(this);
	this->registered_internet_names_gb->setLayout(registered_names_layout);

	this->registered_internet_names = new QTreeWidget(this);
	this->registered_internet_names->setColumnCount(2);
	this->registered_internet_names->setFixedHeight(100);
	QList<InternetName>* internet_names = data_manager->getInternetNames();
	for (int i = 0; i < internet_names->size(); i++) {
		QTreeWidgetItem* item = new QTreeWidgetItem();
		item->setText(0, (*internet_names)[i].getInternetName());
		item->setText(1, ("Registered on " + QString::number((*internet_names)[i].getIPAddressesList()->size()) + " devices" + (((*internet_names)[i].getIPAddressesList()->contains(data_manager->getLocalhostAddress())) ? "(including this device)": "")));
		this->registered_internet_names->addTopLevelItem(item);
	}
	this->selection_description = new QLabel("Choose an internet name to sync files between files with the same internet name on other devices");
	this->selection_description->setWordWrap(true);
	this->bind_to_internet_name = new QPushButton("Choose selected");
	QObject::connect(bind_to_internet_name, &QPushButton::released, [=]() {
		if (this->registered_internet_names->topLevelItemCount() == 0) {
			QMessageBox::warning(this, "Wrong selection", "You didn't select any item");
			return;
		}
		QList<InternetName>* internet_names = data_manager->getInternetNames();
		this->name_chosen = this->registered_internet_names->currentItem()->text(0);
		for (int i = 0; i < internet_names->size(); i++) {
			if ((*internet_names)[i].getInternetName() == this->name_chosen) {
				if ((*internet_names)[i].getIPAddressesList()->contains(data_manager->getLocalhostAddress())) {
					QMessageBox::warning(this, "Cannot select this name", "This internet name already exists on this device. Please select different internet name!");
					return;
				}
				break;
			}
		}
		this->close();
	});

	this->create_new_name_gb = new QGroupBox;
	this->create_new_name_gb->setLayout(create_new_name_layout);
	this->new_name_ta = new QPlainTextEdit;
	this->new_name_ta->setFixedHeight(this->fontMetrics().height() + 12);
	this->new_name_ta->setPlaceholderText("Enter internet name");
	this->create_internet_name = new QPushButton("Create internet name");
	QObject::connect(create_internet_name, &QPushButton::released, [=]() {
		if(data_manager->registerInternetName(new_name_ta->toPlainText()))this->name_chosen = new_name_ta->toPlainText();
		else {
			QMessageBox::warning(this, "Wrong name", "Incorrect internet name (must contains some characters and can't be a duplicate of an existing one on this device)!");
			return;
		}
		QMessageBox::information(this, "Successfully set internet name", "Successfully set internet name! This file will be synced with other file of that name on other devices.");
		this->close();
	});
	this->creation_description = new QLabel("Create an internet name to sync files between files with the same internet name on other devices");
	this->creation_description->setWordWrap(true);

	this->cancel = new QPushButton("Cancel");
	QObject::connect(cancel, &QPushButton::released, [=]() {
		this->name_chosen = "";
		this->close();
	});

	this->create_new_name_layout->addWidget(creation_description);
	this->create_new_name_layout->addWidget(new_name_ta);
	this->create_cancel_layout->addWidget(create_internet_name);
	this->create_cancel_layout->addWidget(cancel);
	this->create_new_name_layout->addLayout(create_cancel_layout);

	this->registered_names_layout->addWidget(selection_description);
	this->registered_names_layout->addWidget(registered_internet_names);
	this->registered_names_layout->addWidget(bind_to_internet_name);

	this->root_layout->addWidget(registered_internet_names_gb);
	this->root_layout->addWidget(create_new_name_gb);

	this->setLayout(root_layout);
}

InternetNameSelectionDialog::~InternetNameSelectionDialog()
{
}

QString InternetNameSelectionDialog::getNameChosen()
{
	return name_chosen;
}
