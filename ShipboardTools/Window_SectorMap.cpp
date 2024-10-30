#include "Window_SectorMap.h"
#include "ui_Window_SectorMap.h"
#include "Globals.h"

#include "Graphics/Hexagon.h"
#include "Graphics/SectorRectangle.h"

#include "Data/System.h"
#include "Data/Sector.h"
#include "Data/Subsector.h"

#include "ApplicationManager.h"

#include <QJsonObject>
#include <QJsonArray>

#include <QGraphicsRectItem>

#define PI 3.14159265

float hexRadius = 100;

Window_SectorMap::Window_SectorMap(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window_SectorMap) {
    ui->setupUi(this);
    this->setWindowTitle("Shipboard Tools - Galaxy Map");

    ui->mapView->setWindow(this);

    scene = new QGraphicsScene();
    ui->mapView->setScene(scene);
    scene->setBackgroundBrush(QBrush(Qt::black));

    ui->groupBox->setVisible(false);
    ui->saveSystemButton->setDisabled(true);

    std::vector<std::string> sectorFileNames = global::getAllJSONFiles(global::dataPath()+"Sectors/");
    for(std::string sector: sectorFileNames){
        this->loadSector(sector);
    }

    QMenu *viewMenu = new QMenu("View");
    QAction *modeAction = new QAction("Dark Mode On/Off");
    viewMenu->addAction(modeAction);

    QMenu *launcherMenu = new QMenu("Launcher");
    QAction *launcherAction = new QAction("Back to Launcher");
    launcherMenu->addAction(launcherAction);

    QMenu *dataMenu = new QMenu("Data");
    QAction *dataAction = new QAction("Export Data");
    dataMenu->addAction(dataAction);

    ui->menuBar->addMenu(launcherMenu);
    //ui->menuBar->addMenu(viewMenu);
    ui->menuBar->addMenu(dataMenu);

    connect(dataAction, &QAction::triggered, this, &Window_SectorMap::saveData);
    connect(launcherAction, &QAction::triggered, this, &Window_SectorMap::backToLauncher);
    connect(modeAction, &QAction::triggered, this, &Window_SectorMap::switchMode);
}

Window_SectorMap::~Window_SectorMap(){
    // Cleanup scene
    ui->mapView->scene()->clear();
}

void Window_SectorMap::setApplication(ApplicationManager *a){
    app = a;
}

void Window_SectorMap::setDetails(Hexagon *hexagon){
    ui->groupBox->setVisible(true);
    ui->hexEdit->setText(QString::fromStdString(hexagon->getHexCode()));
    ui->nameEdit->setText(QString::fromStdString(hexagon->getName()));
    ui->uwpEdit->setText(QString::fromStdString(hexagon->getUWP()));
    ui->sectorEdit->setText(QString::fromStdString(hexagon->getSectorName()));
    ui->tradeEdit->setText(QString::fromStdString(hexagon->getTradeCode()));
    this->selectedSystem = hexagon->getName();

    // Check if system exists
    std::vector<std::string> systems = global::getAllJSONFiles(global::dataPath()+"/Systems");
    bool foundSystem = false;
    for(std::string sys : systems){
        if(sys.compare(this->selectedSystem) == 0){
            foundSystem = true;
            break;
        }
    }
    ui->systemMapButton->setEnabled(foundSystem);
}

void Window_SectorMap::setSystemMapButtonDisabled(bool disable){
    ui->systemMapButton->setDisabled(disable);
}

void Window_SectorMap::loadSector(std::string filename){
    QJsonObject root = global::openJSON(QString::fromStdString(global::dataPath()+"Sectors/"+filename+".json"));

    QJsonValue sectorPos = root.value("sector_position");
    auto sectorX = sectorPos.toArray().at(0).toInt(0);
    auto sectorY = sectorPos.toArray().at(1).toInt(0);
    auto sectorName = root.value("sector_name").toString();

    Sector *sec = new Sector(filename, sectorName.toStdString(), sectorX, sectorY);

    QJsonValue subsectorsRoot = root.value("subsectors");
    for(QJsonValue sub: subsectorsRoot.toArray()){
        QString subsectorName = sub.toObject().value("subsector_name").toString();
        int subsectorIndex = sub.toObject().value("subsector_index").toInt();

        Subsector *subsector = new Subsector(subsectorName.toStdString(), subsectorIndex);
        sec->setSubsector(subsector);
    }

    this->sectors.push_back(sec);
    this->setupLimitedSector(sec);
}

void Window_SectorMap::fillSector(Sector *sector) {
    std::string sectorName = sector->getFileName();

    QJsonObject root = global::openJSON(QString::fromStdString(global::dataPath()+"/Sectors/"+sectorName+".json"));

    std::map<std::array<int,2>, class System*> map;
    QJsonValue systemsRoot = root.value("systems");

    for(QJsonValue s: systemsRoot.toArray()){
        QJsonObject systemObject = s.toObject();
        QString systemName = !systemObject.value("system_name").isUndefined()? systemObject.value("system_name").toString() : "";
        QString systemUWP = !systemObject.value("system_uwp").isUndefined()? systemObject.value("system_uwp").toString() : "";
        QString systemTrade = !systemObject.value("system_trade_code").isUndefined()? systemObject.value("system_trade_code").toString() : "";
        QString systemCategory = !systemObject.value("system_category").isUndefined()? systemObject.value("system_category").toString() : "";
        QString systemZone = !systemObject.value("system_zone").isUndefined()? systemObject.value("system_zone").toString() : "";
        QJsonValue systemInterests = !systemObject.value("system_interests").isUndefined()? systemObject.value("system_interests") : QJsonValue::Null;
        std::vector<std::string> interests;
        if(!systemInterests.isNull()){
            QJsonArray interestArray = systemInterests.toArray();
            for(QJsonValue val: interestArray){
                QString v = val.toString();
                interests.push_back(v.toStdString());
            }
        }

        int systemX = systemObject.value("system_position").toArray().at(0).toInt(0);
        int systemY = systemObject.value("system_position").toArray().at(1).toInt(0);

        std::string psX = "";
        if (systemX<10) psX = "0";
        std::string psY = "";
        if (systemY<10) psY = "0";
        std::string systemHexCode = psX+std::to_string(systemX)+psY+std::to_string(systemY);

        System *sys = new System(systemName.toStdString(), systemHexCode, interests, systemUWP.toStdString(), systemTrade.toStdString(), systemCategory.toStdString(), systemZone.toStdString());
        std::array<int, 2> k = {systemX, systemY};

        map.insert({k, sys});
    }
    sector->setSystems(map);
    sector->setLoaded(true);
    this->setupSector(sector);
}

void Window_SectorMap::setupLimitedSector(Sector *s) {
    float offsetX = hexRadius * (1 + sin(30*PI/180));
    float offsetY = hexRadius * (cos(30*PI/180)) - 0.6;

    float w = 32 * offsetX;
    float h = 40 * offsetY*2;

    float sectorX = s->getX() * w ;
    float sectorY = s->getY() * h ;

    /*---------------------*
     *     SECTOR MARK     *
     *---------------------*/
    SectorRectangle *sectorRec = new SectorRectangle(QRectF(0, 0, w, h), s->getName());
    QTransform rectT;
    rectT.translate(sectorX-hexRadius, sectorY-offsetY);
    sectorRec->setTransform(rectT);

    scene->addItem(sectorRec);

    /*------------------------*
     *     SUBSECTOR MARK     *
     *------------------------*/
    for(Subsector* subsector : s->getSubsectors()){
        int index = subsector->getIndex() - 1;
        int x = index%4;
        int y = index/4;

        SectorRectangle *subsectorRec = new SectorRectangle(QRectF(0, 0, w/4, h/4), subsector->getName(), true);
        QTransform rectSubT;
        rectSubT.translate(sectorX-hexRadius + w*x/4, sectorY-offsetY + h*y/4);
        subsectorRec->setTransform(rectSubT);

        scene->addItem(subsectorRec);
    }
}

void Window_SectorMap::setupSector(Sector *sector){
    float offsetX = hexRadius * (1 + sin(30*PI/180));
    float offsetY = hexRadius * (cos(30*PI/180)) - 0.6;

    float w = 32 * offsetX;
    float h = 40 * offsetY*2;

    float sectorX = sector->getX() * w ;
    float sectorY = sector->getY() * h ;

    /*-----------------*
     *     SYSTEMS     *
     *-----------------*/
    for(int i=1;i<=32;i++){
        for(int j=1;j<=40;j++){
            float offsetYColumn = 0;
            if(i%2==0) offsetYColumn = offsetY;

            float positionX = (i-1) * offsetX;
            float positionY = (j-1) * 2 * offsetY + offsetYColumn; // offsetY * (2j - 1) = 2 * j * (hW - 0.1) - (hW - 0.1) = 2j*hW - 0.2j - hW + 0.1

            System *system = sector->getSystem(i, j);
            if (system == nullptr) {
                std::string hexCode = "";
                if(i < 10) hexCode += "0";
                hexCode += std::to_string(i);
                if(j<10) hexCode += "0";
                hexCode += std::to_string(j);

                system=new System("", "", std::vector<std::string>(),hexCode, "", "");
            }
            system->setSector(sector);
            Hexagon *hex = new Hexagon(hexRadius, QPoint(sectorX + positionX,sectorY + positionY), system);
            scene->addItem(hex);
        }
    }
}

void Window_SectorMap::updateViewPosition(QPointF topLeft, QPointF bottomRight){
    float offsetX = hexRadius * (1 + sin(30*PI/180));
    float offsetY = hexRadius * (cos(30*PI/180)) - 0.6;

    float w = 32 * offsetX;
    float h = 40 * offsetY*2;

    int topLeftSectorX = floor(topLeft.x()  / w);
    int bottomRightSectorX = floor(bottomRight.x() / w);
    int topLeftSectorY = floor(topLeft.y() / h);
    int bottomRightSectorY = floor(bottomRight.y() / h);

    for(Sector *s : this->sectors){
        if(s->getX() > bottomRightSectorX || s->getX() < topLeftSectorX || s->getY() > bottomRightSectorY || s->getY() < topLeftSectorY){
            if(!s->getHidden()) s->setHidden(true);
        }
        else {
            if(!s->getLoaded()) this->fillSector(s);
            else s->setHidden(false);
        }
    }

}

void Window_SectorMap::updateShownData(bool hideSystems, QPointF topLeft, QPointF bottomRight){
    float offsetX = hexRadius * (1 + sin(30*PI/180));
    float offsetY = hexRadius * (cos(30*PI/180)) - 0.6;

    float w = 32 * offsetX;
    float h = 40 * offsetY*2;

    int topLeftSectorX = floor(topLeft.x()  / w);
    int bottomRightSectorX = floor(bottomRight.x() / w);
    int topLeftSectorY = floor(topLeft.y() / h);
    int bottomRightSectorY = floor(bottomRight.y() / h);

    for (Sector *s : this->sectors){
        if(hideSystems && !s->getHidden()) s->setHidden(true);
        else {
            if(s->getX() <= bottomRightSectorX && s->getX() >= topLeftSectorX && s->getY() <= bottomRightSectorY && s->getY() >= topLeftSectorY) s->setHidden(false);
        }
    }
}

void Window_SectorMap::showSystemDetails(QPointF topLeft, QPointF bottomRight){
    //GET CURRENT COORDINATES
    float offsetX = hexRadius * (1 + sin(30*PI/180));
    float offsetY = hexRadius * (cos(30*PI/180)) - 0.6;

    float w = 32 * offsetX;
    float h = 40 * offsetY*2;

    int topLeftSectorX = floor(topLeft.x()  / w);
    int bottomRightSectorX = floor(bottomRight.x() / w);
    int topLeftSectorY = floor(topLeft.y() / h);
    int bottomRightSectorY = floor(bottomRight.y() / h);

    for (Sector *s : this->sectors){
        if(!(s->getX() > bottomRightSectorX || s->getX() < topLeftSectorX || s->getY() > bottomRightSectorY || s->getY() < topLeftSectorY)){
            if(!s->getLoaded()) this->fillSector(s);
            //else s->showSystemDetails();
        }
    }
}

void Window_SectorMap::saveData(){
    // TODO
}

void Window_SectorMap::backToLauncher(){
    this->app->showLauncher();

    // Clean up data from this window


    this->close();
}

void Window_SectorMap::switchMode(){
    bool newMode = !global::getDarkMode();
    global::setDarkMode(newMode);
    if(newMode){
        ui->mapView->scene()->setBackgroundBrush(QBrush(Qt::white));
    }
    else{
        ui->mapView->scene()->setBackgroundBrush(QBrush(Qt::black));
    }
}


void Window_SectorMap::on_systemMapButton_clicked(){
    this->app->changeSystem(this->selectedSystem);
    this->app->showSystemViewer();
}


void Window_SectorMap::on_saveSystemButton_clicked(){

}

