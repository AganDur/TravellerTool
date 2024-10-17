#ifndef SECTORRECTANGLE_H
#define SECTORRECTANGLE_H

#include <QGraphicsRectItem>

class Hexagon;

class SectorRectangle : public QGraphicsRectItem{
public:
    SectorRectangle(QRectF rectangle, std::string name, bool subsector = false);

    void showText();
    void hideText();

    bool isSubsector() { return subsector; }

    void changePenScale(float modifier);

private:
    std::string name;

    bool subsector = false;

    QGraphicsTextItem* sectorNameText;
};

#endif // SECTORRECTANGLE_H
