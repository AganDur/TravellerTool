#include "Window_ShipViewer.h"
#include "OpenGL/GL_ShipViewerWidget.h"

#include "ui_Window_ShipViewer.h"

#include <iostream>
#include <QTimer>
#include <QCheckBox>
#include <QSurfaceFormat>

Window_ShipViewer::Window_ShipViewer(std::string ship, QWidget *parent) : QMainWindow(parent), ui(new Ui::Window_ShipViewer) {
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setSamples(8);
    QSurfaceFormat::setDefaultFormat(format);

    ui->setupUi(this);

    this->setWindowTitle(QString::fromStdString("Shipboard Tools - Ship Viewer - "+ship));

    gl = new GL_ShipViewerWidget(this, ship);
    gl->setWindow(this);

    ui->horizontalLayout->insertWidget(0, gl, 2);
    startGL();

    this->setMouseTracking(true);
}

Window_ShipViewer::~Window_ShipViewer() {
    delete ui;
    delete this->gl;
}

void Window_ShipViewer::startGL(){
    QTimer *timer = new QTimer(gl);
    connect(timer, SIGNAL(timeout()), gl, SLOT(update()));
    timer->start(1000/60);
}

void Window_ShipViewer::changeWindowData(std::vector<std::string> components, std::string ship){
    auto layout = ui->componentChoiceLayout;

    for(std::string component: components){
        QCheckBox *box = new QCheckBox(QString::fromStdString(component));
        box->setChecked(false);

        connect(box, &QCheckBox::stateChanged, [this, box]{
           this->selectComponent(box->isChecked(), box->text().toStdString());
        });

        layout->addWidget(box);
    }

    ui->shipNameTitle->setText(QString::fromStdString(ship));
}

void Window_ShipViewer::selectComponent(bool selected, std::string ship) {
    gl->changeComponentActivation(ship, selected);
}
