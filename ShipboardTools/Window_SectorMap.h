#ifndef WINDOW_SECTORMAP_H
#define WINDOW_SECTORMAP_H

#include <QMainWindow>

namespace Ui {
class Window_SectorMap;
}

class Window_SectorMap : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window_SectorMap(QWidget *parent = nullptr);
    ~Window_SectorMap();

private:
    Ui::Window_SectorMap *ui;
};

#endif // WINDOW_SECTORMAP_H
