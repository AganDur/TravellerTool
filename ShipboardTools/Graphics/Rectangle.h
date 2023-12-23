#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QGraphicsRectItem>

class Hexagon;

class Rectangle : public QGraphicsRectItem
{
public:
    Rectangle(std::string name);

    void addHex(Hexagon *hex);

private:
    std::vector<Hexagon*> hexes;
    std::string name;
};

#endif // RECTANGLE_H
