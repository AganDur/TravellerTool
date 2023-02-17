#include "SectorMap_MainWindow.h"
#include "ui_SectorMap_MainWindow.h"

SectorMap_MainWindow::SectorMap_MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SectorMap_MainWindow)
{
    ui->setupUi(this);
}

SectorMap_MainWindow::~SectorMap_MainWindow()
{
    delete ui;
}
