#include "Window_SectorMap.h"
#include "ui_Window_SectorMap.h"
#include "Globals.h"

#include "Graphics/Hexagon.h"

#include "Data/System.h"
#include "Data/Sector.h"
#include "Data/Subsector.h"

#include <QJsonObject>
#include <QJsonArray>

#include <QGraphicsRectItem>

#define PI 3.14159265

float hexRadius = 100;

Window_SectorMap::Window_SectorMap(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window_SectorMap) {
    ui->setupUi(this);

    ui->mapView->setWindow(this);

    scene = new QGraphicsScene();
    ui->mapView->setScene(scene);

    ui->groupBox->setVisible(false);
    ui->hexEdit->setDisabled(true);

    std::vector<std::string> sectorFileNames = global::getAllJSONFiles(global::path()+"Sectors/");
    for(std::string sector: sectorFileNames){
        this->loadSector(global::openJSON(QString::fromStdString(global::path()+"Sectors/"+sector+".json")));
    }
}

Window_SectorMap::~Window_SectorMap(){
    delete ui;
}

void Window_SectorMap::setDetails(Hexagon *hexagon){
    ui->groupBox->setVisible(true);
    ui->hexEdit->setText(QString::fromStdString(hexagon->getHexCode()));
    ui->nameEdit->setText(QString::fromStdString(hexagon->getName()));
    ui->uwpEdit->setText(QString::fromStdString(hexagon->getUWP()));
    ui->sectorEdit->setText(QString::fromStdString(hexagon->getSectorName()));
}

void Window_SectorMap::setSystemMapButtonDisabled(bool disable){
    ui->systemMapButton->setDisabled(disable);
}

void Window_SectorMap::loadSector(QJsonObject root){
    QJsonValue sectorPos = root.value("sector_position");
    auto sectorX = sectorPos.toArray().at(0).toInt(0);
    auto sectorY = sectorPos.toArray().at(1).toInt(0);
    auto sectorName = root.value("sector_name").toString();

    Sector *sec = new Sector(sectorName.toStdString(), sectorX, sectorY);

    QJsonValue subsectorsRoot = root.value("subsectors");
    for(QJsonValue sub: subsectorsRoot.toArray()){
        QString subsectorName = sub.toObject().value("subsector_name").toString();
        int subsectorIndex = sub.toObject().value("subsector_index").toInt();

        Subsector *subsector = new Subsector(subsectorName.toStdString(), subsectorIndex);
        sec->setSubsector(subsector);
    }

    std::map<std::array<int,2>, class System*> map;
    QJsonValue systemsRoot = root.value("systems");
    for(QJsonValue s: systemsRoot.toArray()){
        QString nS = s.toObject().value("system_name").toString();
        QString uwpS = s.toObject().value("system_uwp").toString();

        int sX = s.toObject().value("system_position").toArray().at(0).toInt(0);
        int sY = s.toObject().value("system_position").toArray().at(1).toInt(0);

        std::string psX = "";
        if (sX<10) psX = "0";
        std::string psY = "";
        if (sY<10) psY = "0";
        std::string pS = psX+std::to_string(sX)+psY+std::to_string(sY);

        System *sys = new System(nS.toStdString(), uwpS.toStdString(), pS);
        std::array<int, 2> k = {sX, sY};

        map.insert({k, sys});
    }
    sec->setSystems(map);

    this->setupSector(sec);
}

void Window_SectorMap::setupSector(Sector *s){//, std::map<std::array<int,2>, class hexSystem*> map){
    float offsetX = hexRadius * (1 + sin(30*PI/180));
    float offsetY = hexRadius * (cos(30*PI/180)) - 0.6;

    float w = 32 * offsetX;
    float h = 40 * offsetY*2;

    float sectorX = s->getX() * w ;
    float sectorY = s->getY() * h ;

    /*---------------------*
     *     SECTOR MARK     *
     *---------------------*/
    QPen p;
    p.setCosmetic(true);
    p.setWidth(2);
    QGraphicsRectItem *r = new QGraphicsRectItem(QRectF(0, 0, w, h));
    r->setPen(p);
    QTransform rectT;
    rectT.translate(sectorX-hexRadius, sectorY-offsetY);
    r->setTransform(rectT);

    /*---------------------*
     *     SECTOR TEXT     *
     *---------------------*/
    QGraphicsTextItem *sT = new QGraphicsTextItem(QString::fromStdString(s->getName()),r);
    QFont f;
    f.setPointSize(500);
    sT->setFont(f);
    sT->setDefaultTextColor(Qt::red);

    // CALCULATE CORRECT POSITION WITH ROTATION
    QPointF center = sT->boundingRect().center();
    QPointF sectorCenter = r->boundingRect().center();
    QPointF centerDiff = sectorCenter - center;
    float width=sT->boundingRect().width();
    float height = sT->boundingRect().height();

    QTransform textPos;
    textPos.translate(centerDiff.x()+width/2, centerDiff.y()+height/2);
    textPos.rotate(-45);
    textPos.translate(-width/2, -height/2);
    sT->setTransform(textPos);
    sT->setVisible(false);

    scene->addItem(r);


    /*-----------------*
     *     SYSTEMS     *
     *-----------------*/
    for(int i=1;i<=32;i++){
        for(int j=1;j<=40;j++){
            float offsetYColumn = 0;
            if(i%2==0) offsetYColumn = offsetY;

            float positionX = (i-1) * offsetX;
            float positionY = (j-1) * 2 * offsetY + offsetYColumn; // offsetY * (2j - 1) = 2 * j * (hW - 0.1) - (hW - 0.1) = 2j*hW - 0.2j - hW + 0.1

            System *sys = s->getSystem(i, j);
            if (sys == nullptr) {
                std::string hexCode = "";
                if(i < 10) hexCode += "0";
                hexCode += std::to_string(i);
                if(j<10) hexCode += "0";
                hexCode += std::to_string(j);

                sys=new System("", "", hexCode);
            }
            sys->setSector(s);
            Hexagon *hex = new Hexagon(hexRadius, QPoint(sectorX + positionX,sectorY + positionY), sys);
            scene->addItem(hex);
        }
    }
}
