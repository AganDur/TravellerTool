#ifndef SECTORMAP_MAINWINDOW_H
#define SECTORMAP_MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class SectorMap_MainWindow;
}

class SectorMap_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SectorMap_MainWindow(QWidget *parent = nullptr);
    ~SectorMap_MainWindow();

private:
    Ui::SectorMap_MainWindow *ui;
};

#endif // SECTORMAP_MAINWINDOW_H
