#include "Hexagon.h"
#include "Data/System.h"
#include "Data/Sector.h"

#include <iostream>
#include <stdlib.h>

#include <QPen>
#include <QPainter>

#define PI 3.14159265

Hexagon::Hexagon(float radius, QPoint center, System *system, int category){
    this->radius = radius;
    this->center = center;
    this->hexSystem = system;
    this->hexSystem->setHexagon(this);

    QTransform transformMatrix;
    transformMatrix.translate(center.x(), center.y());
    this->setTransform(transformMatrix);

    this->nameOffset = radius*3/12;
    this->nameSecondaryOffset = radius*2/5;
    this->uwpOffset = radius*3/5;
    this->tradeHorOffset = radius*1/5;
    this->tradeVertOffset = 0;
    this->hexOffset = -radius*4/5;

    /*-------------------------*
     *     SETUP SUB ITEMS     *
     *-------------------------*/
    if(!system->getName().empty()){
        nameText = new QGraphicsTextItem(QString::fromStdString(getName()), this);
        nameText->setFont(QFont("Helvetica",20));
        centerText(nameText, 0, nameSecondaryOffset);

        uwpText = new QGraphicsTextItem(QString::fromStdString(getUWP()),this);
        uwpText->setFont(QFont("Arial",10));
        centerText(uwpText, 0, uwpOffset);

        hexCodeText = new QGraphicsTextItem(QString::fromStdString(getHexCode()),this);
        hexCodeText->setFont(QFont("Arial",20));
        centerText(hexCodeText, 0, hexOffset);

        tradeCodeText = new QGraphicsTextItem(QString::fromStdString(getTradeCode()),this);
        tradeCodeText->setFont(QFont("Arial",8));
        tradeCodeText->setDefaultTextColor(Qt::red);
        centerText(tradeCodeText, tradeHorOffset, tradeVertOffset, false);

        this->createSystemSymbol(category);
    }
    this->showLimitedInfo();
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

std::string Hexagon::getTradeCode(){
    return this->hexSystem->getTradeCode();
}

void Hexagon::createSystemSymbol(int category){
    QPen pen;
    switch(category){
        case 0:
            systemSymbol = new QGraphicsEllipseItem(QRectF(-20, -20, 40, 40), this);
            pen.setWidth(2);
            ((QGraphicsEllipseItem*)systemSymbol)->setPen(pen);
            ((QGraphicsEllipseItem*)systemSymbol)->setBrush(Qt::darkGray);
            break;
        case 1:
            systemSymbol = new QGraphicsEllipseItem(QRectF(-20, -20, 40, 40), this);
            pen.setWidth(2);
            ((QGraphicsEllipseItem*)systemSymbol)->setPen(pen);
            ((QGraphicsEllipseItem*)systemSymbol)->setBrush(Qt::blue);
            break;
        default:
            systemSymbol = new QGraphicsEllipseItem(QRectF(-20, -20, 40, 40), this);
            pen.setWidth(2);
            ((QGraphicsEllipseItem*)systemSymbol)->setPen(pen);
            ((QGraphicsEllipseItem*)systemSymbol)->setBrush(Qt::black);
    }
}

void Hexagon::showLimitedInfo() {
    if(!this->getName().empty()) {
        this->getHexCodeText()->show();
        QFont updatedFont = this->getHexCodeText()->font();
        updatedFont.setPointSize(27);
        this->getHexCodeText()->setFont(updatedFont);

        this->getNameText()->show();
        updatedFont = this->getNameText()->font();
        updatedFont.setPointSize(27);
        this->getNameText()->setFont(updatedFont);

        this->getTradeCodeText()->hide();
        this->getUwpText()->hide();

        centerText(this->getHexCodeText(), 0, this->hexOffset);
        centerText(this->getNameText(), 0, this->nameSecondaryOffset);
        centerText(this->getUwpText(), 0, this->uwpOffset);
        centerText(this->getTradeCodeText(), this->tradeHorOffset, this->tradeVertOffset, false);
    }
}

void Hexagon::showFullInfo() {
    if(!this->getName().empty()) {
        this->getHexCodeText()->show();
        QFont updatedFont = this->getHexCodeText()->font();
        updatedFont.setPointSize(20);
        this->getHexCodeText()->setFont(updatedFont);

        this->getNameText()->show();
        updatedFont = this->getNameText()->font();
        updatedFont.setPointSize(20);
        this->getNameText()->setFont(updatedFont);

        this->getTradeCodeText()->show();
        this->getUwpText()->show();

        centerText(this->getHexCodeText(), 0, this->hexOffset);
        centerText(this->getNameText(), 0, this->nameOffset);
        centerText(this->getUwpText(), 0, this->uwpOffset);
        centerText(this->getTradeCodeText(), this->tradeHorOffset, this->tradeVertOffset, false);
    }
}

void Hexagon::centerText(QGraphicsTextItem *textItem, float horizontalOffset, float verticalOffset, bool offsetCenter){
    QTransform textTransform;
    float nameWidth = textItem->boundingRect().width();
    float horizontal = horizontalOffset;
    if(offsetCenter) horizontal -= nameWidth/2;

    textTransform.translate(horizontal, verticalOffset);
    textItem->setTransform(textTransform);
}
