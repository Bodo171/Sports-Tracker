#pragma once
#include <qlistwidget.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qformlayout.h>
#include <qmessagebox.h>
#include <string>
#include <qfile.h>
#include "service.h"
using std::string;
using std::to_string;
class SportWindow : public QWidget {
	Q_OBJECT
private:
	Service* Manager;
	string sportName;
	QListWidget* eventList;
	QPushButton * addEventButton, * removeEventButton, * updateEventButton;
	QLineEdit *yearEdit,*monthEdit,*dayEdit;
	QLineEdit* nameEdit, *descriptionEdit;
	vector<Event> events;
	void selectedItemChanged();
public:
	SportWindow(string _sportName,Service* Manager,QWidget* parent = Q_NULLPTR);

	void buildSportWindow();
	void populateEventList();
	void connectSignalsAndSlots();

	void addEventButtonHandler();
	void removeEventButtonHandler();
	void updateEventButtonHandler();
	void displayError(Error& handledError);
	void readStyleSheets();

	~SportWindow();
signals:
	void eventListChanged();
};