#ifndef HEXAGON_H
#define HEXAGON_H

#include <QGraphicsItem>

class System;

class Hexagon : public QGraphicsItem {
public:
    Hexagon(float radius, QPoint center, System *system, int category=1);

    QRectF boundingRect() const;
    QPainterPath shape() const;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    std::string getName();
    std::string getHexCode();
    std::string getUWP();
    std::string getSectorName();
    std::string getTradeCode();

    void createSystemSymbol(int category);

    QGraphicsTextItem* getNameText() { return this->nameText; };
    QGraphicsTextItem* getHexCodeText() { return this->hexCodeText; };
    QGraphicsTextItem* getUwpText() { return this->uwpText; };
    QGraphicsTextItem* getTradeCodeText() { return this->tradeCodeText; };

    void showLimitedInfo();
    void showFullInfo();

    void centerText(QGraphicsTextItem* textItem, float horizontalOffset, float verticalOffset, bool offsetCenter = true);

private:
    float radius;
    QPoint center;
    System *hexSystem;

    bool isEmptySystem;

    QGraphicsTextItem *nameText, *hexCodeText, *uwpText, *tradeCodeText;

    QGraphicsItem *systemSymbol;

    float nameOffset, nameSecondaryOffset, hexOffset, uwpOffset, tradeVertOffset, tradeHorOffset;

    // TODO:
    // ADD GRAPHIC ITEM FOR SYSTEM OPTIONS AND ZONE
};

#endif // HEXAGON_H
