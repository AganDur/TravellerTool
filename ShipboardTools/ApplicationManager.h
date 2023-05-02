#ifndef APPLICATIONMANAGER_H
#define APPLICATIONMANAGER_H

class Launcher;

class ApplicationManager{
public:
    ApplicationManager();

private:
    Launcher *launcherWindow;

public:
    void showLauncher();
};

#endif // APPLICATIONMANAGER_H
