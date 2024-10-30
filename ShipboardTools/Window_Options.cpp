#include "Window_Options.h"
#include "ui_Window_Options.h"
#include "Globals.h"
#include "Options_FolderLine.h"

#include <QRadioButton>

Window_Options::Window_Options(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window_Options) {
    ui->setupUi(this);

    qDebug() << global::dataPaths().size();

    // Setup GM Mode
    ui->gmModeSelector->setChecked(global::isGM());

    // Setup Data Location List
    for(auto location : global::dataPaths()){
        Options_FolderLine *folder = new Options_FolderLine(location, location.compare(global::path())!=0, location.compare(global::dataPath())==0);
        folder->setWindow(this);
        buttonGroup.addButton(folder->getRadio());

        if(location.compare(global::path())!=0){
            ui->dataLocationBox->addWidget(folder);
        }
        else {
            ui->dataLocationBox->insertWidget(0, folder);
        }
    }
}

Window_Options::~Window_Options() {
    delete ui;
}

void Window_Options::on_saveButton_clicked(){
    bool mode = ui->gmModeSelector->isChecked();
    bool dark = ui->darkModeSelector->isChecked();
    std::string selectedLocation = buttonGroup.checkedButton()->text().toStdString();

    global::setGM(mode);
    global::setPath(selectedLocation.empty() ? global::path() : selectedLocation);
    global::setDarkMode(dark);

    global::saveSettingsFile();

    this->close();
}


void Window_Options::on_cancelButton_clicked(){
    this->close();
}


void Window_Options::on_newFolderButton_clicked(){
    QString newFolder = ui->newFolderText->text();

    if(newFolder.isEmpty()) return;

    newFolder.replace("\\","/");
    if(!newFolder.endsWith("/")) newFolder.append("/");

    Options_FolderLine *folder = new Options_FolderLine(newFolder.toStdString(), true, false);
    buttonGroup.addButton(folder->getRadio());
    ui->dataLocationBox->addWidget(folder);

    global::addPath(newFolder.toStdString());
}

void Window_Options::deleteFolder(Options_FolderLine *folder) {
    if(!folder->isDeletable()) return;

    // Remove location from list
    std::string removedFolder = folder->getLocation();
    global::removePath(removedFolder);

    // Check if removed location was selected, then set current location to default
    if(removedFolder.compare(global::dataPath())==0) {
        Options_FolderLine *newFolder = dynamic_cast<Options_FolderLine*>(ui->dataLocationBox->itemAt(0)->widget());
        newFolder->setChecked(true);
        global::setPath(global::path());
    }
}

