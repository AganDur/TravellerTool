#include "Gl_Widget.h"

#include <QTimer>
#include <QPainter>
#include <QPaintEvent>

GL_Widget::GL_Widget(QWidget *parent) : QOpenGLWidget{parent} {
    elapsed_time = 0;
}

void GL_Widget::animate(){
    update();
}
