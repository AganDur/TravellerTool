#ifndef WINDOW_SYSTEMVIEWER_H
#define WINDOW_SYSTEMVIEWER_H

#include <QMainWindow>

namespace Ui {
class Window_SystemViewer;
}

class GL_Widget;

class Window_SystemViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window_SystemViewer(QWidget *parent = nullptr);
    ~Window_SystemViewer();

    void startGL();

private:
    Ui::Window_SystemViewer *ui;
    GL_Widget *gl;
};

#endif // WINDOW_SYSTEMVIEWER_H
