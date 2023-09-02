#include "Dialog_SystemSelection.h"
#include "ui_Dialog_SystemSelection.h"

#include "Globals.h"
#include "ApplicationManager.h"

Dialog_SystemSelection::Dialog_SystemSelection(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog_SystemSelection) {
    ui->setupUi(this);
    loadSystems();
}

Dialog_SystemSelection::~Dialog_SystemSelection(){
    delete ui;
}

void Dialog_SystemSelection::setApplication(ApplicationManager *a){
    this->app = a;
}

void Dialog_SystemSelection::loadSystems(){
    // Get all System names from files
    std::string systemFilesPath = global::path() + "Systems";
    std::vector<std::string> systemNames = global::getAllJSONFiles(systemFilesPath);

    // Clear the combo box
    ui->selectorBox->clear();

    // Fill the combo box again
    for(std::string name : systemNames){
        ui->selectorBox->addItem(QString::fromStdString(name));
    }
}

void Dialog_SystemSelection::on_selectorBox_currentIndexChanged(int index){
    std::string selectedSystem = ui->selectorBox->currentText().toStdString();
    QString filePath =QString::fromStdString(global::path() + "Systems\\" + selectedSystem + ".json");

    QJsonObject root = global::openJSON(filePath);

    ui->detailTextBox->clear();
    // Go through the file and extract the necessary data
    if (root.isEmpty()){
        ui->detailTextBox->appendPlainText("SYSTEM NOT KNOWN");
        ui->acceptButton->setDisabled(true);
    }
    else {
        ui->acceptButton->setDisabled(false);
        QString systemName = root.value("system").toString();
        QString systemSector = root.value("sector").toString();
        QString systemSubSector = root.value("subsector").toString();
        QString systemHex = root.value("hex").toString();
        ui->detailTextBox->appendPlainText("System details:");
        ui->detailTextBox->appendPlainText("Name: "+systemName);
        ui->detailTextBox->appendPlainText("Sector: "+systemSector);
        ui->detailTextBox->appendPlainText("Subsector: "+systemSubSector);
        ui->detailTextBox->appendPlainText("Hex: "+systemHex);
    }
}


void Dialog_SystemSelection::on_acceptButton_clicked(){
    std::string selectedSystem = ui->selectorBox->currentText().toStdString();
    app->updateSelectedSystem(selectedSystem);
    this->close();
}


void Dialog_SystemSelection::on_cancelButton_clicked(){
    this->close();
}

