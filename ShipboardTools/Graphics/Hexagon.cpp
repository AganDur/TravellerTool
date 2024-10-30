#include "Hexagon.h"
#include "Data/System.h"
#include "Data/Sector.h"

#include <iostream>
#include <stdlib.h>

#include <QPen>
#include <QPainter>

#include "Globals.h"

#define PI 3.14159265

Hexagon::Hexagon(float radius, QPoint center, System *system){
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
        this->createSystemSymbol(system->getCategory());;
        for(std::string interest: system->getInterests()){
            this->createSystemInterest(interest);
        }

        nameText = new QGraphicsTextItem(QString::fromStdString(getName()), this);
        QFont nameFont = QFont("Helvetica",20);
        nameFont.setBold(true);
        nameText->setFont(nameFont);
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
    }
    this->showLimitedInfo();
}

QRectF Hexagon::boundingRect() const{
    float y = radius * sin(60*PI/180);
    return QRectF(-radius, -y, 2*radius, 2*y);
}

QPainterPath Hexagon::shape(float radius) const{
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
    painter->drawPath(shape(this->radius));

    if(this->hexSystem->getZone().compare("A")==0){
        QPen pen(Qt::yellow, 3);
        pen.setCosmetic(true);
        painter->setPen(pen);
        painter->drawPath(shape(this->radius * 0.9));
    }
    else if(this->hexSystem->getZone().compare("R")==0){
        QPen pen(Qt::red, 3);
        pen.setCosmetic(true);
        painter->setPen(pen);
        painter->drawPath(shape(this->radius * 0.9));
    }
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

inline constexpr auto hash_djb2a(const std::string_view sv){
    unsigned long hash{ 5381 };
    for(unsigned char c: sv){
        hash = ((hash << 5) + hash) ^ c;
    }
    return hash;
}

inline constexpr auto operator"" _sh(const char *str, size_t len){
    return hash_djb2a(std::string_view{str, len});
}

void Hexagon::createSystemSymbol(std::string category){
    QString symbolPath = QString::fromStdString(global::path()+"Assets/Sectors/");
    QPixmap image;
    QGraphicsPixmapItem *symbol;
    switch(hash_djb2a(category)){
        case "Wet"_sh:
            image.load(symbolPath+"WorldWet.png");
            symbol = new QGraphicsPixmapItem(image, this);
            symbol->setPos(-50,-50);
            systemSymbols.push_back(symbol);
            break;
        case "Dry"_sh:
            image.load(symbolPath+"WorldDry.png");
            symbol = new QGraphicsPixmapItem(image, this);
            symbol->setPos(-50,-50);
            systemSymbols.push_back(symbol);
            break;
        case "Asteroid"_sh:
            image.load(symbolPath+"NoWorld.png");
            symbol = new QGraphicsPixmapItem(image, this);
            symbol->setPos(-50,-50);
            systemSymbols.push_back(symbol);
            break;
        case "Interest"_sh:
            image.load(symbolPath+"PointOfInterest.png");
            symbol = new QGraphicsPixmapItem(image, this);
            symbol->setPos(-50,-50);
            symbol->setScale(.5);
            systemSymbols.push_back(symbol);
            break;
        default:
            break;
    }
}

void Hexagon::createSystemInterest(std::string interest){
    QString symbolPath = QString::fromStdString(global::path()+"Assets/Sectors/");
    QPixmap image;
    QGraphicsPixmapItem *symbol;
    QPoint bottomLeft(-80,-5), topLeft(-75,-65), topRight(30,-50), middleLeft(-100,-25);

    switch(hash_djb2a(interest)){
        case "Gas"_sh:
            image.load(symbolPath+"GasGiant.png");
            symbol = new QGraphicsPixmapItem(image, this);
            symbol->setPos(topRight);
            symbol->setScale(.5);
            systemSymbols.push_back(symbol);
            break;
        case "Naval"_sh:
            image.load(symbolPath+"NavalBase.png");
            symbol = new QGraphicsPixmapItem(image, this);
            symbol->setPos(topLeft);
            systemSymbols.push_back(symbol);
            break;
        case "IISSBase"_sh:
            image.load(symbolPath+"IISSBase.png");
            symbol = new QGraphicsPixmapItem(image, this);
            symbol->setPos(bottomLeft);
            systemSymbols.push_back(symbol);
            break;
        case "IISSWay"_sh:
            image.load(symbolPath+"IISSWaystation.png");
            symbol = new QGraphicsPixmapItem(image, this);
            symbol->setPos(bottomLeft);
            systemSymbols.push_back(symbol);
            break;
        case "Depot"_sh:
            image.load(symbolPath+"NavalDepot.png");
            symbol = new QGraphicsPixmapItem(image, this);
            symbol->setPos(middleLeft);
            systemSymbols.push_back(symbol);
            break;
        case "Research"_sh:
            image.load(symbolPath+"ResearchStation.png");
            symbol = new QGraphicsPixmapItem(image, this);
            symbol->setPos(middleLeft);
            systemSymbols.push_back(symbol);
            break;
        default:
            break;
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
