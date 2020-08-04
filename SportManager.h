#pragma once

#include <QtWidgets/QMainWindow>
#include <qlistwidget.h>
#include <qmessagebox.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qfile.h>
#include "service.h"
#include "sportwindow.h"
#include "ui_SportManager.h"

class SportManager : public QMainWindow
{
    Q_OBJECT

public:
    SportManager(QWidget *parent = Q_NULLPTR);
private:
    void displayError(Error& handledError);
    Service Manager;
    void buildGUI();
    void connectSignalsAndSlots();
    void populateSportsList();
    void loadSportButtonHandler();
    void readStyleSheets();
    void addSportButtonHandler();
    void removeSportButtonHandler();
    void selectedItemChanged();

    vector <string> sports;
    QWidget* centralWidget;
    QListWidget* sportList;
    QPushButton* loadSportButton;
    QPushButton* addSportButton;
    QPushButton* removeSportButton;
    QLineEdit* currentSport;
    Ui::SportManagerClass ui;
signals:
    void sportListChanged();
};
