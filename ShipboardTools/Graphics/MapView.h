#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QGraphicsView>

class Window_SectorMap;

class MapView : public QGraphicsView{
public:
    MapView();
    MapView(QWidget *parent);

    void setWindow(Window_SectorMap *w);

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

    void initialize();

    bool findSystem(std::string name);

    void viewMoved();

private:
    Window_SectorMap *window;
    float zoomFactor = 1;
    bool hideHexes = false;

    std::vector<std::string> systems;
};

#endif // MAPVIEW_H
