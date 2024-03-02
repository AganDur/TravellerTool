#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

#include "Launcher.h"
#include "Window_SystemViewer.h"

#include <QApplication>

class Window_SectorMap;

class ApplicationManager: public QApplication {
public:
    ApplicationManager(int argc, char *argv[]);

private:
    Launcher launcherWindow;
    Window_SystemViewer *systemViewerWindow;
    Window_SectorMap *sectorMapWindow;

    std::string currentSystem;
    std::string currentSelectedSystem;

public:
    void showLauncher();
    void showSystemViewer();
    void showSectorMap();

    void openDialog_SystemSelection();

    void changeSystem(std::string newSystem);

};

#endif // APPLICATIONMANAGER_H
