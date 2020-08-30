#include "SportManager.h"

SportManager::SportManager(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    readStyleSheets();
    buildGUI();
    connectSignalsAndSlots();
    populateSportsList();
}

void SportManager::readStyleSheets() {
    QFile styleSheetInput("Styles/widget.qss");
    styleSheetInput.open(QFile::ReadOnly);
    QString styleSheet = styleSheetInput.readAll();
    this->setStyleSheet(styleSheet);
}

void SportManager::buildGUI() {
    this->centralWidget = new QWidget(this);
    QVBoxLayout* globalLayout = new QVBoxLayout(centralWidget);
    this->sportList = new QListWidget(this);
    this->sportList->setSelectionMode(QAbstractItemView::SingleSelection);
    this->currentSport = new QLineEdit(this);
    this->loadSportButton = new QPushButton("Load sport",this);
    this->addSportButton = new QPushButton("Add sport", this);
    this->removeSportButton = new QPushButton("Remove sport", this);
    globalLayout->addWidget(sportList);
    globalLayout->addWidget(currentSport);
    globalLayout->addWidget(loadSportButton);
    globalLayout->addWidget(addSportButton);
    globalLayout->addWidget(removeSportButton);
    this->setCentralWidget(this->centralWidget);
}

void SportManager::connectSignalsAndSlots() {
    QObject::connect(this->loadSportButton,&QPushButton::clicked,this,&SportManager::loadSportButtonHandler);
    QObject::connect(this->addSportButton, &QPushButton::clicked, this, &SportManager::addSportButtonHandler);
    QObject::connect(this->removeSportButton, &QPushButton::clicked, this, &SportManager::removeSportButtonHandler);
    QObject::connect(this->sportList, &QListWidget::itemSelectionChanged, this, &SportManager::selectedItemChanged);
    QObject::connect(this, &SportManager::sportListChanged, this, &SportManager::populateSportsList);
}

void SportManager::addSportButtonHandler() {
    try {
        string newSport = this->currentSport->text().toStdString();
        Manager.addSport(newSport);
        emit sportListChanged();
    }
    catch(Error & handledError) {
        displayError(handledError);
    }
}

void SportManager::removeSportButtonHandler() {
    try {
        string oldSport = this->currentSport->text().toStdString();
        Manager.removeSport(oldSport);
        emit sportListChanged();
    }
    catch (Error & handledError) {
        displayError(handledError);
    }
}

void SportManager::selectedItemChanged() {
    if (this->sportList->count() == 0)
        return;
    QModelIndexList indexes = this->sportList->selectionModel()->selectedIndexes();
    if (indexes.size() == 0) {
        this->currentSport->clear();
        return;
    }
    int index = indexes.at(0).row();
    if (index >= this->sports.size())
        return;
    string sport = this->sports[index];
    this->currentSport->setText(QString::fromStdString(sport));
}

void SportManager::displayError(Error& handledError) {
    QMessageBox messageBox(this);
    messageBox.critical(0, "Error", handledError.getErrorMessage().c_str());
    messageBox.open();
}

void SportManager::loadSportButtonHandler() {
    if (this->sportList->selectedItems().size() == 0) {
        Error myError("No sport selected");
        displayError(myError);
        return;
    }
    string sportName = (this->sportList->selectedItems().at(0)->text()).toStdString();
    SportWindow* newWindow = new SportWindow(sportName,&(this->Manager));
    newWindow->show();
}
void SportManager::populateSportsList() {
    this->sportList->clear();
    sports=Manager.getSports();
    for (auto sport : sports) {
        this->sportList->addItem(QString::fromStdString(sport));
    }
}