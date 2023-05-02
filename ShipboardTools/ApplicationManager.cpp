#include "ApplicationManager.h"
#include "Launcher.h"

ApplicationManager::ApplicationManager(){
}

void ApplicationManager::showLauncher(){
    if(this->launcherWindow != nullptr) delete(launcherWindow);

    this->launcherWindow = new Launcher();
    this->launcherWindow->show();
}
