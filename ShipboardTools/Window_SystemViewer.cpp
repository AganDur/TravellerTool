#include "Window_SystemViewer.h"
#include "ui_Window_SystemViewer.h"
#include "OpenGL/GL_SystemViewerWidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QSurfaceFormat>

Window_SystemViewer::Window_SystemViewer(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Window_SystemViewer)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setSamples(8);
    QSurfaceFormat::setDefaultFormat(format);


    ui->setupUi(this);
    setWindowTitle(tr("TEST2"));

    gl = new GL_SystemViewerWidget(this, "Acrid");

    ui->horizontalLayout->insertWidget(0, gl);
    startGL();

    this->setMouseTracking(true);
}

Window_SystemViewer::~Window_SystemViewer(){
    delete ui;
}

void Window_SystemViewer::startGL(){
    QTimer *timer = new QTimer(gl);
    connect(timer, SIGNAL(timeout()), gl, SLOT(update()));
    timer->start(1000/60);
}

void Window_SystemViewer::reloadData(std::string system){
    gl->updateData(system);
}
