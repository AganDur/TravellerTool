#include "ApplicationManager.h"
#include "Launcher.h"
#include "Window_SystemViewer.h"

ApplicationManager::ApplicationManager(){
}

void ApplicationManager::showLauncher(){
    if(this->launcherWindow != nullptr) delete(launcherWindow);

    this->launcherWindow = new Launcher();
    this->launcherWindow->show();
}

void ApplicationManager::showSystemViewer(){
    if(this->systemViewerWindow != nullptr) delete(systemViewerWindow);

    this->systemViewerWindow = new Window_SystemViewer();
    this->systemViewerWindow->show();
}
