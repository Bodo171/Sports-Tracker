#include "sportwindow.h"

SportWindow::SportWindow(string _sportName,Service* _Manager,QWidget* parent) : QWidget(parent) {
	sportName = _sportName;
	this->setWindowTitle(QString::fromStdString(sportName));
	this->Manager = _Manager;
	readStyleSheets();
	buildSportWindow();
	populateEventList();
	connectSignalsAndSlots();

}

void SportWindow::buildSportWindow(){
	QHBoxLayout* globalLayout = new QHBoxLayout(this);
	this->eventList = new QListWidget(this);

	QWidget* userConsole = new QWidget(this);
	QVBoxLayout* userConsoleLayout = new QVBoxLayout(userConsole);

	QWidget* formWidget = new QWidget(this);
	QFormLayout* formLayout = new QFormLayout(formWidget);

	QLabel* nameLabel, * descriptionLabel;
	nameLabel = new QLabel("Name:", this);
	this->nameEdit = new QLineEdit(this);
	nameLabel->setBuddy(this->nameEdit);

	descriptionLabel = new QLabel("Description:", this);
	this->descriptionEdit = new QLineEdit(this);
	descriptionLabel->setBuddy(this->descriptionEdit);

	QLabel* yearLabel,*monthLabel,*dayLabel;

	yearLabel = new QLabel("Year:");
	this->yearEdit=new QLineEdit(this);
	yearLabel->setBuddy(this->yearEdit);

	monthLabel = new QLabel("Month:");
	this->monthEdit = new QLineEdit(this);
	monthLabel->setBuddy(this->monthEdit);

	dayLabel = new QLabel("Day:");
	this->dayEdit = new QLineEdit(this);
	dayLabel->setBuddy(this->dayEdit);

	//formLayout->addRow()
	formLayout->addRow(nameLabel, nameEdit);
	formLayout->addRow(descriptionLabel, descriptionEdit);
	formLayout->addRow(yearLabel, yearEdit);
	formLayout->addRow(monthLabel, monthEdit);
	formLayout->addRow(dayLabel, dayEdit);

	userConsoleLayout->addWidget(formWidget);

	QWidget* buttonsWidget = new QWidget(this);
	QHBoxLayout* buttonsLayout = new QHBoxLayout(buttonsWidget);
	this->addEventButton = new QPushButton("Add event");
	this->removeEventButton = new QPushButton("Remove event");
	this->updateEventButton = new QPushButton("Update description");
	buttonsLayout->addWidget(this->addEventButton);
	buttonsLayout->addWidget(this->removeEventButton);
	buttonsLayout->addWidget(this->updateEventButton);
	
	userConsoleLayout->addWidget(buttonsWidget);

	///building
	globalLayout->addWidget(this->eventList);
	globalLayout->addWidget(userConsole);
}


void SportWindow::connectSignalsAndSlots() {
	QObject::connect(this->eventList, &QListWidget::itemSelectionChanged, this, &SportWindow::selectedItemChanged);
	QObject::connect(this->addEventButton, &QPushButton::clicked, this, &SportWindow::addEventButtonHandler);
	QObject::connect(this->removeEventButton, &QPushButton::clicked, this, &SportWindow::removeEventButtonHandler);
	QObject::connect(this->updateEventButton, &QPushButton::clicked, this, &SportWindow::updateEventButtonHandler);
	QObject::connect(this, &SportWindow::eventListChanged, this, &SportWindow::populateEventList);
}


void SportWindow::populateEventList() {
	this->events = Manager->getEvents(this->sportName);
	this->eventList->clear();
	for (auto currentEvent : events) {
		QString name = QString::fromStdString(currentEvent.getName());
		this->eventList->addItem(name);
	}
}

void SportWindow::displayError(Error& handledError) {
	QMessageBox messageBox(this);
	messageBox.critical(0, "Error", handledError.getErrorMessage().c_str());
	messageBox.open();
}

void SportWindow::addEventButtonHandler() {
	string name=nameEdit->text().toStdString();
	string description=descriptionEdit->text().toStdString();
	int year = yearEdit->text().toInt();
	int month = monthEdit->text().toInt();
	int day = dayEdit->text().toInt();
	try {
		Manager->addEvent(name, description, this->sportName, year, month, day);
		emit eventListChanged();
	}
	catch (Error& handledError) {
		displayError(handledError);
	}
}

void SportWindow::updateEventButtonHandler() {
	string name = nameEdit->text().toStdString();
	string description = descriptionEdit->text().toStdString();
	int year = yearEdit->text().toInt();
	int month = monthEdit->text().toInt();
	int day = dayEdit->text().toInt();
	try {
		Manager->updateEvent(name, description, this->sportName, year, month, day);
		emit eventListChanged();
	}
	catch (Error & handledError) {
		displayError(handledError);
	}
}

void SportWindow::readStyleSheets() {
	QFile styleSheetInput("Styles/widget.qss");
	styleSheetInput.open(QFile::ReadOnly);
	QString styleSheet = styleSheetInput.readAll();
	this->setStyleSheet(styleSheet);
}

void SportWindow::selectedItemChanged() {
	if (this->eventList->count() == 0)
		return;
	QModelIndexList indexes = this->eventList->selectionModel()->selectedIndexes();
	if (indexes.size() == 0) {
		this->nameEdit->clear();
		this->descriptionEdit->clear();
		this->yearEdit->clear();
		this->monthEdit->clear();
		this->dayEdit->clear();
		return;
	}
	int index = indexes.at(0).row();
	if (index >= this->events.size())
		return;
	string name, description, month, day, year;
	name = this->events[index].getName();
	description = this->events[index].getDescription();
	year = to_string(this->events[index].getYear());
	month = to_string(this->events[index].getMonth());
	day = to_string(this->events[index].getDay());

	this->nameEdit->setText(QString::fromStdString(name));
	this->descriptionEdit->setText(QString::fromStdString(description));
	this->yearEdit->setText(QString::fromStdString(year));
	this->monthEdit->setText(QString::fromStdString(month));
	this->dayEdit->setText(QString::fromStdString(day));
}

void SportWindow::removeEventButtonHandler() {
	string name = nameEdit->text().toStdString();
	string description = descriptionEdit->text().toStdString();
	int year = yearEdit->text().toInt();
	int month = monthEdit->text().toInt();
	int day = dayEdit->text().toInt();
	try {
		Manager->removeEvent(name, this->sportName, year, month, day);
		emit eventListChanged();
	}
	catch (Error & handledError) {
		displayError(handledError);
	}
}

SportWindow::~SportWindow() {

}