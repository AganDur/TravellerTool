#include "Window_SystemViewer.h"
#include "ui_Window_SystemViewer.h"

#include "OpenGL/GL_SystemViewerWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTimer>

Window_SystemViewer::Window_SystemViewer(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::Window_SystemViewer)
{
    ui->setupUi(this);
    setWindowTitle(tr("TEST2"));

    gl = new GL_SystemViewerWidget(this, "Acrid");

    ui->horizontalLayout->insertWidget(0, gl);
    startGL();
}

Window_SystemViewer::~Window_SystemViewer(){
    delete ui;
}

void Window_SystemViewer::startGL(){
    QSurfaceFormat format;
    format.setSamples(16);
    format.setDepthBufferSize(24);
    gl->setFormat(format);

}
