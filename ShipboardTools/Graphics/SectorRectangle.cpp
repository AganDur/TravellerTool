#include "SectorRectangle.h"

#include <QPen>
#include <QFont>

SectorRectangle::SectorRectangle(QRectF rectangle, std::string name, bool subsector): QGraphicsRectItem(rectangle){
    this->name = name;

    this->sectorNameText = new QGraphicsTextItem(QString::fromStdString(name), this);

    // Set text font
    QFont f;
    if(subsector) f.setPointSize(100);
    else f.setPointSize(500);
    sectorNameText->setFont(f);
    sectorNameText->setDefaultTextColor(Qt::red);

    // CALCULATE CORRECT POSITION WITH ROTATION
    QPointF center = sectorNameText->boundingRect().center();
    QPointF sectorCenter = this->boundingRect().center();
    QPointF centerDiff = sectorCenter - center;
    float width=sectorNameText->boundingRect().width();
    float height = sectorNameText->boundingRect().height();

    QTransform textPos;
    textPos.translate(centerDiff.x()+width/2, centerDiff.y()+height/2);
    textPos.rotate(-45);
    textPos.translate(-width/2, -height/2);
    sectorNameText->setTransform(textPos);
    sectorNameText->setVisible(false);

    sectorNameText->hide();

    this->subsector = subsector;

    QPen pen;
    if(subsector){
        pen.setWidth(2);
        pen.setStyle(Qt::DashLine);
    }
    else {
        pen.setWidth(4);
    }
    this->setPen(pen);
}

void SectorRectangle::showText(){
    sectorNameText->show();
}

void SectorRectangle::hideText(){
    sectorNameText->hide();
}

void SectorRectangle::changePenScale(float modifier){
    QPen pen = this->pen();
    int size = pen.width() * modifier;
    pen.setWidth(size);
    this->setPen(pen);
}
