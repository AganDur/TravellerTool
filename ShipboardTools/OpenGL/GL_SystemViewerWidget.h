#ifndef GL_SYSTEMVIEWERWIDGET_H
#define GL_SYSTEMVIEWERWIDGET_H

#include "Gl_Widget.h"

#include <QMatrix4x4>
#include <QElapsedTimer>
#include <QTimer>

class ApplicationManager;
class GL_Camera;
class GL_Object;

class GL_SystemViewerWidget : public GL_Widget {

public:
    GL_SystemViewerWidget(std::string systemName);

    void setApp(ApplicationManager *a){ this->application = a;} //
    void initialize(); //
    void initSphere(); //

    //void paintEvent(QPaintEvent *event) override;
    void render();

    void keyPress();
    void mouseMoveEvent(QMouseEvent *e) override;

    void updateData(std::string file);

private:
    int m_frame = 0;
    std::string system;

    QMatrix4x4 view;
    QMatrix4x4 projection;

    GL_Camera *camera;
    float orbitingSpeed = 0.01;

    std::vector<GL_Object*> models;

    QVector3D ambientLight = QVector3D(1.0f, 1.0f, 1.0f);
    float ambientIntensity = 0.3f;

    std::vector<GLfloat> planetVertices;
    std::vector<GLfloat> starVertices;
    std::vector<unsigned int> sphereIndices;

    qint64 currentFrame = 0;
    qint64 lastFrame = 0;
    QElapsedTimer elapsedTimer;
    QTimer timer;

    ApplicationManager *application;

    QPointF lastMousePosition;
    bool firstMouse = true;
};

#endif // GL_SYSTEMVIEWERWIDGET_H
