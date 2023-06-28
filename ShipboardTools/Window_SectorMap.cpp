#include "Window_SectorMap.h"
#include "ui_Window_SectorMap.h"

Window_SectorMap::Window_SectorMap(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window_SectorMap)
{
    ui->setupUi(this);
}

Window_SectorMap::~Window_SectorMap()
{
    delete ui;
}
