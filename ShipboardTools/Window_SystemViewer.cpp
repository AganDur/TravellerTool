#include "Window_SystemViewer.h"
#include "ui_Window_SystemViewer.h"

#include "OpenGL/GL_Widget.h"
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

    GL_Widget *gl = new GL_Widget(this);

    ui->horizontalLayout->insertWidget(0, gl);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, gl, &GL_Widget::animate);
    timer -> start(50);
}

Window_SystemViewer::~Window_SystemViewer()
{
    delete ui;
}
