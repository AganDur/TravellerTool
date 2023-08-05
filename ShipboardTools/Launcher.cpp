#include "Launcher.h"
#include "ui_Launcher.h"
#include "ApplicationManager.h"

Launcher::Launcher(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Launcher)
{
    ui->setupUi(this);
    updateTargetSystem("");
    updateCurrentSystem("");
}

Launcher::~Launcher()
{
    delete ui;
}

void Launcher::setApplicationManager(ApplicationManager *a){
    this->app = a;
}

void Launcher::updateTargetSystem(std::string target){
    ui->targetSystemTitle->setText(QString("Selected System = ") + QString::fromStdString(target));
}

void Launcher::updateCurrentSystem(std::string current){
    ui->currentSystemTitle->setText(QString("Current System = ") + QString::fromStdString(current));
}

void Launcher::on_SystemMapButton_clicked(){
    this->app->showSystemViewer();
    this->close();
}


void Launcher::on_LocationButton_clicked(){
    // Open Modal Window to Select System
    this->app->openDialog_SystemSelection();
}

