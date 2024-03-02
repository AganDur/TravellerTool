#ifndef WINDOW_SECTORMAP_H
#define WINDOW_SECTORMAP_H

#include <QMainWindow>

namespace Ui {
    class Window_SectorMap;
}

class Hexagon;
class Sector;
class QGraphicsScene;
class ApplicationManager;

class Window_SectorMap : public QMainWindow{
    Q_OBJECT

public:
    explicit Window_SectorMap(QWidget *parent = nullptr);
    ~Window_SectorMap();

    void setApplication(ApplicationManager *a);

    void setDetails(Hexagon *hexagon);

    void setSystemMapButtonDisabled(bool disable);

    void loadSector(std::string filename);
    void fillSector(Sector *s);
    void setupLimitedSector(Sector *s);
    void setupSector(Sector *s);//, std::map<std::array<int,2>, class hexSystem*> map);

    void updateViewPosition(QPointF topLeft, QPointF bottomRight);
    void updateShownData(bool hideSystems, QPointF topLeft, QPointF bottomRight);

    void showSystemDetails(QPointF topLeft, QPointF bottomRight);
    void hideSystemDetails(QPointF topLeft, QPointF bottomRight);

    void saveData();
    void backToLauncher();

private slots:
    void on_systemMapButton_clicked();

    void on_saveSystemButton_clicked();

private:
    ApplicationManager *app = nullptr;

    std::vector<Sector*> sectors;

    std::string selectedSystem;

    Ui::Window_SectorMap *ui = nullptr;

    QGraphicsScene *scene = nullptr;
};

#endif // WINDOW_SECTORMAP_H
