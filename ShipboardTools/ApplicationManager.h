#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

class Launcher;
class Window_SystemViewer;

class ApplicationManager{
public:
    ApplicationManager();

private:
    Launcher *launcherWindow = nullptr;
    Window_SystemViewer *systemViewerWindow = nullptr;

public:
    void showLauncher();

    void showSystemViewer();
};

#endif // APPLICATIONMANAGER_H
