#ifndef WINDOW_SHIPVIEWER_H
#define WINDOW_SHIPVIEWER_H

#include <QMainWindow>

namespace Ui {
class Window_ShipViewer;
}

class GL_ShipViewerWidget;

class Window_ShipViewer : public QMainWindow {
    Q_OBJECT

public:
    explicit Window_ShipViewer(std::string ship, QWidget *parent = nullptr);
    ~Window_ShipViewer();

    void startGL();

    void changeWindowData(std::vector<std::string> components, std::string ship);

    //void closeEvent(QCloseEvent *event);

    void selectComponent(bool selected, std::string ship);

private:
    Ui::Window_ShipViewer *ui;
    GL_ShipViewerWidget *gl;
};

#endif // WINDOW_SHIPVIEWER_H
