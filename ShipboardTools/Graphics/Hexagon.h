#ifndef HEXAGON_H
#define HEXAGON_H

#include <QGraphicsItem>

class System;

class Hexagon : public QGraphicsItem {
public:
    Hexagon(float radius, QPoint center, System *system);

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    std::string getName();
    std::string getHexCode();
    std::string getUWP();
    std::string getSectorName();

private:
    float radius;
    QPoint center;
    System *hexSystem;
};

#endif // HEXAGON_H
