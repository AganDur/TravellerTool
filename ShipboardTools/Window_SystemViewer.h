#ifndef WINDOW_SYSTEMVIEWER_H
#define WINDOW_SYSTEMVIEWER_H

#include <QMainWindow>

namespace Ui {
class Window_SystemViewer;
}

class GL_SystemViewerWidget;

class Window_SystemViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window_SystemViewer(std::string system, QWidget *parent = nullptr);
    ~Window_SystemViewer();

    void startGL();

    void reloadData(std::string system);

private:
    Ui::Window_SystemViewer *ui;
    GL_SystemViewerWidget *gl;
};

#endif // WINDOW_SYSTEMVIEWER_H
