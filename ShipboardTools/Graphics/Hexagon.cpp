#include "Hexagon.h"
#include "Data/System.h"
#include "Data/Sector.h"

#include <QPen>
#include <QPainter>

#define PI 3.14159265

Hexagon::Hexagon(float radius, QPoint center, System *system){
    this->radius = radius;
    this->center = center;
    this->hexSystem = system;

    QTransform transformMatrix;
    transformMatrix.translate(center.x(), center.y());
    this->setTransform(transformMatrix);

    /*-------------------------*
     *     SETUP SUB ITEMS     *
     *-------------------------*/
    QFont font;
    font.setPointSize(20);

    if(!system->getName().empty()){
        QGraphicsTextItem *nameText = new QGraphicsTextItem(QString::fromStdString(system->getName()), this);
        nameText->setFont(font);
        QTransform nameTransform;
        float nameWidth = nameText->boundingRect().width();
        nameTransform.translate(-nameWidth/2, radius*1/3);
        nameText->setTransform(nameTransform);

        QGraphicsTextItem *hexText = new QGraphicsTextItem(QString::fromStdString(system->getHex()),this);
        hexText->setFont(font);
        QTransform hexTransform;
        float hexWidth = hexText->boundingRect().width();
        hexTransform.translate(-hexWidth/2, -radius*4/5);
        hexText->setTransform(hexTransform);

        QGraphicsEllipseItem *planetSymbol = new QGraphicsEllipseItem(QRectF(-20, -20, 40, 40), this);
        QPen pen;
        pen.setWidth(2);
        planetSymbol->setPen(pen);
        planetSymbol->setBrush(Qt::blue);
    }
}

QRectF Hexagon::boundingRect() const{
    float y = radius * sin(60*PI/180);
    return QRectF(-radius, -y, 2*radius, 2*y);
}

QPainterPath Hexagon::shape() const{
    float vX = radius * cos(60*PI/180);
    float vY = radius * sin(60*PI/180);

    QPoint A1 = QPoint(-radius, 0);
    QPoint A2 = QPoint(-vX, -vY);
    QPoint A3 = QPoint(vX, -vY);
    QPoint A4 = QPoint(radius, 0);
    QPoint A5 = QPoint(vX, vY);
    QPoint A6 = QPoint(-vX, vY);

    QPainterPath path(A1);
    path.lineTo(A2);
    path.lineTo(A3);
    path.lineTo(A4);
    path.lineTo(A5);
    path.lineTo(A6);
    path.lineTo(A1);

    return path;
}

void Hexagon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPen pen(Qt::black, 1);
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->drawPath(shape());
}

std::string Hexagon::getName(){
    return this->hexSystem->getName();
}

std::string Hexagon::getHexCode(){
    return this->hexSystem->getHex();
}

std::string Hexagon::getUWP(){
    return this->hexSystem->getUWP();
}

std::string Hexagon::getSectorName(){
    return this->hexSystem->getSector()->getName();
}
