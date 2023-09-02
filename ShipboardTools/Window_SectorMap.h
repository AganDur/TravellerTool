#ifndef WINDOW_SECTORMAP_H
#define WINDOW_SECTORMAP_H

#include <QMainWindow>

namespace Ui {
    class Window_SectorMap;
}

class Hexagon;
class Sector;
class QGraphicsScene;

class Window_SectorMap : public QMainWindow{
    Q_OBJECT

public:
    explicit Window_SectorMap(QWidget *parent = nullptr);
    ~Window_SectorMap();

    void setDetails(Hexagon *hexagon);

    void setSystemMapButtonDisabled(bool disable);

    void loadSector(QJsonObject root);
    void setupSector(Sector *s);//, std::map<std::array<int,2>, class hexSystem*> map);

private:
    Ui::Window_SectorMap *ui;

    QGraphicsScene *scene;
};

#endif // WINDOW_SECTORMAP_H
