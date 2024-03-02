#include "Launcher.h"
#include "ui_Launcher.h"
#include "ApplicationManager.h"

Launcher::Launcher(QWidget *parent): QMainWindow(parent), ui(new Ui::Launcher) {
    ui->setupUi(this);
    this->setWindowTitle("Shipboard Tools - Launcher");
}

Launcher::~Launcher(){
    delete ui;
}

void Launcher::setApplicationManager(ApplicationManager *a){
    this->app = a;
}

void Launcher::on_SectorMapButton_clicked(){
    this->app->showSectorMap();
    this->close();
}


