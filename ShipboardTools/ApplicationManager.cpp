#include "ApplicationManager.h"
#include "Launcher.h"
#include "Window_SystemViewer.h"
#include "Window_SectorMap.h"
#include "Dialogs/Dialog_SystemSelection.h"

ApplicationManager::ApplicationManager(int argc, char *argv[]): QApplication{argc, argv}, launcherWindow{Launcher()}, systemViewerWindow{Window_SystemViewer()}{
    launcherWindow.setApplicationManager(this);
}

void ApplicationManager::changeSystem(std::string newSystem){
    this->currentSystem = newSystem;
}

void ApplicationManager::showLauncher(){
    this->launcherWindow.show();
}

void ApplicationManager::showSystemViewer(){
    this->systemViewerWindow.show();
}

void ApplicationManager::showSectorMap(){
    this->sectorMapWindow = new Window_SectorMap();
    this->sectorMapWindow->show();
}

void ApplicationManager::openDialog_SystemSelection(){
    Dialog_SystemSelection *dialog = new Dialog_SystemSelection();
    dialog->setApplication(this);
    dialog->setModal(true);
    dialog->show();
}

void ApplicationManager::updateSelectedSystem(std::string newSystem){
    this->currentSelectedSystem = newSystem;
    this->launcherWindow.updateTargetSystem(newSystem);
}
