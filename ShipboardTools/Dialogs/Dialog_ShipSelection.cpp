#include "Dialog_ShipSelection.h"
#include "ui_Dialog_ShipSelection.h"

#include "Globals.h"
#include "ApplicationManager.h"

#include <QButtonGroup>
#include <QRadioButton>

Dialog_ShipSelection::Dialog_ShipSelection(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog_ShipSelection) {
    ui->setupUi(this);
    group = new QButtonGroup();

    std::string filePath = global::dataPath()+"Ships";
    std::vector<std::string> shipFileNames = global::getAllJSONFiles(filePath);

    int shipsFound = 0;

    for(std::string file : shipFileNames){
        std::string ship = getShipNameFromFile(filePath+"/"+file+".json");
        if(!ship.empty()){
            QRadioButton *radio = new QRadioButton(QString::fromStdString(ship));
            radio->setObjectName(file);
            ui->verticalGroupBox->layout()->addWidget(radio);
            group->addButton(radio);
            radio->setChecked(true);
            shipsFound++;
        }
    }

    if(shipsFound==0) ui->buttonBox->buttons().at(0)->setDisabled(true);
}

Dialog_ShipSelection::~Dialog_ShipSelection(){
    delete ui;
}

void Dialog_ShipSelection::setApplication(ApplicationManager *a) {
    this->app = a;
}

std::string Dialog_ShipSelection::getShipNameFromFile(std::string file){
    QJsonObject root = global::openJSON(QString::fromStdString(file));
    if(root.isEmpty()) return "";
    return root.value("shipName").toString().toStdString();
}

void Dialog_ShipSelection::on_buttonBox_accepted(){
    std::string ship = group->checkedButton()->objectName().toStdString();
    app->showShipViewer(ship);
    this->close();
}


void Dialog_ShipSelection::on_buttonBox_rejected(){
    this->close();
}

