#ifndef GL_WIDGET_H
#define GL_WIDGET_H

#include <QWidget>
#include <QOpenGLWidget>

class GL_Widget : public QOpenGLWidget{
    Q_OBJECT

public:
    explicit GL_Widget(QWidget *parent = nullptr);

public slots:
    void animate();

private:
    int elapsed_time;

    QPaintEvent *event;

};

#endif // GL_WIDGET_H
