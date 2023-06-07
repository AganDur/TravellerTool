#ifndef WINDOW_SYSTEMVIEWER_H
#define WINDOW_SYSTEMVIEWER_H

#include <QMainWindow>

namespace Ui {
class Window_SystemViewer;
}

class Window_SystemViewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window_SystemViewer(QWidget *parent = nullptr);
    ~Window_SystemViewer();

private:
    Ui::Window_SystemViewer *ui;
};

#endif // WINDOW_SYSTEMVIEWER_H
